#include "../header/puit.h"

int launchPuit(int nombreMessage,int tailleMessage,int isTCP,int port,int isBAL)
{
    int sock,socketType;
    struct sockaddr_in socketPuit;
    /*socketType change de valeur en fonction de isTCP -> si isTCp alors SOCK_STREAM, sinon SOCK_DGRAM*/
    socketType = (isTCP) ? SOCK_STREAM : SOCK_DGRAM;
    /*Si le mode boîte aux lettres est activé alors on entre dans le mode BAL -> on return 0 car nous ne voulons pas
    rentrer dans le mode TCP/UDP normal.*/
    if(isBAL)
    {
        printf("Mode Boîte aux Lettres\n");
        modeBoiteAuxLettres(socketPuit,SOCK_STREAM,port,"localhost");
        return 0;
    }
    /*Sinon on initialise le socket de base et on rentre dans receiveMultipleData() -> on ferme le socket avant*/
    sock = initSocket(socketType,&socketPuit,port,"localhost");
    receiveMultipleData(nombreMessage,tailleMessage,sock,socketPuit,isTCP);
    close(sock);
    return 0;
}

void modeBoiteAuxLettres(struct sockaddr_in socketStruct, int socketType, int port, char * ipAddress)
{
    /*Init : Création de la boite aux lettres, de paramRecu pour la couche protocolaire.
    Intiialisation de la taille de socketStruct pour les différentes fonctions.
    Création des 4 variables à récupérer dans la couche protocolaire.*/
    struct listeBAL boiteAuxLettres = initListeBAL();
    struct listeIpTable * tabledIP = initListeIpTable();
    char paramRecu[13];
    int n, longueurRecu = sizeof(socketStruct),sock,oldSock;
    int param,emetteurRecepteur,tailleMessage,nbMessage;
    while(1)
    {
        /*Etat d'attente -> création d'un socket pour écouter le premier client et récupérer son IP. n=1 pour rentrer dans le while*/
        n=1;
        oldSock = initSocket(socketType,&socketStruct,port,ipAddress);
        sock = listenAndAccept(oldSock,&socketStruct,&longueurRecu,true);
        /*Tant qu'on reçoit des données, on vérifie si le client nous demande une reception ou une emission*/
        while(n>0)
        {
            n = read(sock,paramRecu,13);
            recuperationParam(paramRecu,&param,&emetteurRecepteur,&tailleMessage,&nbMessage);
            switch(param)
            {
                case MODE_RECEPTEUR:
                    /*On récupère le socket créé par receptionRecepteur pour le fermer par la suite*/
                    sock=receptionRecepteur(sock,socketType,socketStruct,port,emetteurRecepteur,boiteAuxLettres);
                    /*Pour fermer le while on met n=-1*/
                    n=-1;
                    break;
                case MODE_EMIS:
                    receptionEmetteur(sock,tailleMessage,&n,getEmetteurId(socketStruct,tabledIP),emetteurRecepteur,&boiteAuxLettres);
                    break;
                default:
                    printf("Message non reconnu.\n");
                    break;
            }
        }
        /*Si on est en mode emis, le serveur affiche les données rentrées dans la boite aux lettres*/
        if(param == MODE_EMIS)
        {
            printf("---Boîte aux Lettres actuel :---\n");
            afficheListeBAL(boiteAuxLettres);
            printf("---Liste d'IP actuel :---\n");
            afficheListeIpTable(*tabledIP);
        }
        /*On ferme le socket qu'il provienne du MODE_RECEPTEUR ou MODE_EMIS*/
        close(sock);
    }
}

int receptionRecepteur(int sock, int socketType, struct sockaddr_in socketStruct, int port, int recepteur, struct listeBAL boiteAuxLettres)
{
    /*StripAddressStruct va convertir l'adresse de socketStruct en char* car initStructSocket demande ce type de variable.
    On crée des pointeurs vers les éléments du recepteur concerné.
    inet_ntop permet de convertir une adresse in_addr en char**/
    int longueurEmis,i=1;
    char *paramMessage,StripAddressStruct[INET_ADDRSTRLEN];
    struct in_addr ipAddressStruct = ((struct sockaddr_in*)&socketStruct)->sin_addr;
    struct elementMessage *elementFinal = getMessages(boiteAuxLettres,recepteur)->fin,*elementCourant = getMessages(boiteAuxLettres,recepteur)->courant;
    inet_ntop( AF_INET, &ipAddressStruct, StripAddressStruct, INET_ADDRSTRLEN );

    /*On ferme la connexion qui était en mode listen()
      On crée un nouveau socket en initialisant la structure sockaddr_in avec l'adresse IP du client*/
    close(sock);
    sock=openSocket(socketType);
    initStructSocket(&socketStruct,1,port,StripAddressStruct);
    /*On attend 1 seconde pour que la source lance un listen TCP
      On lance une connexion TCP -> Si -1 alors on retourne le socket crée et on ferme la connexion (on retourne dans l'état d'attente)*/
    sleep(1);
    if (connectTCP(sock,socketStruct,sizeof(socketStruct)) == -1)
    {
        return sock;
    }
    printf("\n--- Messages à renvoyer pour %d : ---\n",recepteur);
    /*Tant qu'il reste des éléments dans la liste on envoi les différents paquets :
    La couche protocolaire avec MODE_RECEPTEUR, l'id de celui qui a envoyé le message, la taille et le nombre de messages
    Le message avec la taille correcte. On incrémente i pour l'affichage et on passe à l'élément suivant.*/
    while(elementCourant->suiv != elementFinal->suiv)
    {
        paramMessage = formatTextParam(MODE_RECEPTEUR,elementCourant->messageBALActuel->idEmetteur,elementCourant->messageBALActuel->tailleData,getMessages(boiteAuxLettres,recepteur)->nbMessages);
        longueurEmis = write(sock,paramMessage,13);
        printAndVerif(paramMessage,13,longueurEmis,i);

        longueurEmis = write(sock,elementCourant->messageBALActuel->data,elementCourant->messageBALActuel->tailleData);
        printAndVerif(elementCourant->messageBALActuel->data,elementCourant->messageBALActuel->tailleData,longueurEmis,i);
        i++;
        elementCourant=elementCourant->suiv;
    }
    return sock;
}

void receptionEmetteur(int sock, int tailleMessagePrevu, int * tailleMessageRecu, int emetteur, int recepteur, struct listeBAL *boiteAuxLettres)
{
    /*On créer un pointeur char car nouveauMessage utilise ce dernier pour l'associer à la boite aux lettres*/
    char * messageRecu = malloc(sizeof(char)*tailleMessagePrevu);
    /*On lit les messages reçus après chaque envoi protocolaire -> la taille est donc connue*/
    *tailleMessageRecu = read(sock,messageRecu,tailleMessagePrevu);
    /*Le nouveau message n'est mis dans la BAL que si la donnée est correcte : donc au dessus d'une taille de 0 octet*/
    if(*tailleMessageRecu>0)
    {
        nouveauMessage(boiteAuxLettres,emetteur,recepteur,messageRecu);
    }
}

int receiveMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in socketStruct, int isTCP)
{
    /*messageRecu sera affiché avec un printf. La variable count est créé au préalable pour le while, n est mis à 1 pour la même raison*/
    char messageRecu[tailleMessage+1];
    int n=1, count=0, longueurRecu = sizeof(socketStruct);
    /*Dans le cas d'une connexion TCP on lance la primitive listenAndAccept() pour établir la connexion avec la source/le client*/
    if(isTCP)
    {
        sock = listenAndAccept(sock,&socketStruct,&longueurRecu,true);
    }
    /*On reçoit des messages tant qu'ils sont vide (pour TCP uniquement)*/
    if(nombreMessages < 0)
    {
        /*Tant qu'on reçoit des messages on continue.*/
        while(n>0)
        {
            n=readRecvFrom(sock,socketStruct,longueurRecu,messageRecu,tailleMessage,isTCP,count+1);
            count++;
        }
    }
    else{
        /*On lit un certain nombre de message donné par l'utilisateur*/
        for(count=0;count<nombreMessages;count++)
        {
            n=readRecvFrom(sock,socketStruct,longueurRecu,messageRecu,tailleMessage,isTCP,count+1);
        }
    }
    return 0;
}

int readRecvFrom(int sock, struct sockaddr_in socketStruct, int longueurRecu, char * messageRecu, int tailleMessage, int isTCP, int i)
{
    int n;
    /*Pour TCP on utilise read(), pour UDP recvfrom()*/
    if(isTCP)
    {
        n = read(sock,messageRecu,tailleMessage);
    }
    else
    {
        n = recvfrom(sock, (char *)messageRecu, tailleMessage, 0, (struct sockaddr*) &socketStruct,(socklen_t *__restrict__)&longueurRecu);
    }
    /*On ajoute \0 en fin de chaîne pour l'afficher correctement sur la console.*/
    messageRecu[n] = '\0';
    printf("Puit\tReception n°%d (%d) :\t[%s]\n",i,n,messageRecu);
    return n;
}

int getEmetteurId(struct sockaddr_in socketStruct, struct listeIpTable * tabledIp)
{
    bool isInTable;
    char StripAddressStruct[INET_ADDRSTRLEN];
    struct in_addr ipAddressStruct = ((struct sockaddr_in*)&socketStruct)->sin_addr;
    inet_ntop( AF_INET, &ipAddressStruct, StripAddressStruct, INET_ADDRSTRLEN );
    struct elementIpTable * returnEmetteurId = existInListIP(*tabledIp,StripAddressStruct,&isInTable);
    if(isInTable)
    {
        printf("[trouve] : idEmetteur = %d",returnEmetteurId->actualIpTable->idEmetteur);
        return returnEmetteurId->actualIpTable->idEmetteur;
    }
    else
    {
        printf("[non trouve] : idEmetteur = %d",tabledIp->taille+1);
        ajoutListeIpTable(tabledIp,creeIpTable(StripAddressStruct,tabledIp->taille+1));
        return tabledIp->taille;
    }
}