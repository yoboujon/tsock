#include "../header/puit.h"

int launchPuit(int nombreMessage,int tailleMessage,int isTCP,int port,char * ipAddress,int isBAL)
{
    int sock,socketType;
    struct sockaddr_in socketPuit;
    socketType = (isTCP) ? SOCK_STREAM : SOCK_DGRAM;
    if(isBAL)
    {
        printf("Mode Boîte aux Lettres\n");
        modeBoiteAuxLettres(socketPuit,socketType,port,ipAddress);
        return 0;
    }
    sock = initSocket(socketType,&socketPuit,port,ipAddress);
    receiveMultipleData(nombreMessage,tailleMessage,sock,socketPuit,isTCP);
    close(sock);
    return 0;
}

void modeBoiteAuxLettres(struct sockaddr_in socketStruct, int socketType, int port, char * ipAddress)
{
    struct listeBAL boiteAuxLettres = initListeBAL();
    char paramRecu[13];
    int n, longueurRecu = sizeof(socketStruct),sock,oldSock, trueTemp = 1,option=1;
    int param,emetteurRecepteur,tailleMessage,nbMessage;
    while(1)
    {
        n=1;
        oldSock = initSocket(socketType,&socketStruct,port,ipAddress);
        listen(oldSock,5);
        sock = accept(oldSock,(struct sockaddr *)&socketStruct,(socklen_t * restrict)&longueurRecu);
        close(oldSock);
        while(n>0)
        {
            n = read(sock,paramRecu,13);
            recuperationParam(paramRecu,&param,&emetteurRecepteur,&tailleMessage,&nbMessage);
            switch(param)
            {
                case MODE_RECEPTEUR:
                    close(sock);
                    if((sock=socket(AF_INET,socketType,0)) == -1)
                    {
                        perror("[tsock] : fonction socket() : echec creation du socket\n");
                        exit(EXIT_FAILURE);
                    }
                    initStructSocket(&socketStruct,1,port,ipAddress);
                    /*On attend 1 seconde pour que la source lance un listen TCP*/
                    sleep(1);
                    /*On lance une connexion TCP et on envoit à l'aide de receptionRecepteur() les données*/
                    connectTCP(sock,socketStruct,sizeof(socketStruct));
                    receptionRecepteur(sock,emetteurRecepteur,boiteAuxLettres);
                    /*Pour fermer le while on met n=-1*/
                    n=-1;
                    break;
                case MODE_EMIS:
                    receptionEmetteur(sock,tailleMessage,&n,1,emetteurRecepteur,&boiteAuxLettres);
                    break;
                default:
                    printf("Message non reconnu.\n");
                    break;
            }
        }
        if(param == MODE_EMIS)
        {
            afficheListeBAL(boiteAuxLettres);
        }
        close(sock);
    }
}

void receptionRecepteur(int sock, int recepteur, struct listeBAL boiteAuxLettres)
{
    int longueurEmis,i=1;
    char *paramMessage;
    printf("\n--- Messages à renvoyer pour %d : ---\n",recepteur);
    struct elementMessage * elementFinal = getMessages(boiteAuxLettres,recepteur)->fin;
    struct elementMessage * elementCourant = getMessages(boiteAuxLettres,recepteur)->courant;
    while(elementCourant->suiv != elementFinal->suiv)
    {
        paramMessage = formatTextParam(MODE_RECEPTEUR,recepteur,elementCourant->messageBALActuel->tailleData,getMessages(boiteAuxLettres,recepteur)->nbMessages);
        printf("paramMessage [%d] = %s\n",i,paramMessage);
        longueurEmis = write(sock,paramMessage,13);
        printAndVerif(paramMessage,13,longueurEmis,i);

        longueurEmis = write(sock,elementCourant->messageBALActuel->data,elementCourant->messageBALActuel->tailleData);
        printAndVerif(elementCourant->messageBALActuel->data,elementCourant->messageBALActuel->tailleData,longueurEmis,i);
        i++;
        elementCourant=elementCourant->suiv;
    }
}

void receptionEmetteur(int sock, int tailleMessagePrevu, int * tailleMessageRecu, int emetteur, int recepteur, struct listeBAL *boiteAuxLettres)
{
    char * messageRecu = malloc(sizeof(char)*tailleMessagePrevu);
    *tailleMessageRecu = read(sock,messageRecu,tailleMessagePrevu);
    if(*tailleMessageRecu>0)
    {
        nouveauMessage(boiteAuxLettres,emetteur,recepteur,messageRecu);
    }
}

int receiveMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in socketStruct, int isTCP)
{
    char messageRecu[tailleMessage+1];
    int n=1, longueurRecu = sizeof(socketStruct);
    if(isTCP)
    {
        listen(sock,5);
        sock = accept(sock,(struct sockaddr *)&socketStruct,(socklen_t * restrict)&longueurRecu);
    }
    if(nombreMessages < 0)
    {
        int i=1;
        while(n>0)
        {
            if(isTCP)
            {
                n = read(sock,messageRecu,tailleMessage);
            }
            else
            {
                n = recvfrom(sock, (char *)messageRecu, tailleMessage, 0, (struct sockaddr*) &socketStruct,(socklen_t *__restrict__)&longueurRecu);
            }
            messageRecu[n] = '\0';
            printf("Puit\tReception n°%d (%d) :\t[%s]\n",i,n,messageRecu);
            i++;
        }
    }
    else{
        for(int i=0;i<nombreMessages;i++)
        {
            if(isTCP)
            {
                n = read(sock,messageRecu,tailleMessage);
            }
            else
            {
                n = recvfrom(sock, (char *)messageRecu, tailleMessage, 0, (struct sockaddr*) &socketStruct,(socklen_t *__restrict__)&longueurRecu);
            }
            messageRecu[n] = '\0';
            printf("Puit\tReception n°%d (%d) :\t[%s]\n",i+1,tailleMessage,messageRecu);
        }
    }
    return 0;
}