#include "../header/bal.h"

int main(void){
    struct listeBAL boiteAuxLettres = initListeBAL();
    nouveauMessage(&boiteAuxLettres,2,1,"Renvoi moi mon pdf asap. -Simon");
    nouveauMessage(&boiteAuxLettres,2,1,"Mon anniversaire c'est demain !");
    nouveauMessage(&boiteAuxLettres,1,2,"Ok joyeux anniv alors !");
    nouveauMessage(&boiteAuxLettres,1,2,"ok c'est fait. -Yohan");
    nouveauMessage(&boiteAuxLettres,3,1,"C'est trop, yohan me soule");
    nouveauMessage(&boiteAuxLettres,1,3,"Yoyo l'asticot");
    afficheListeBAL(boiteAuxLettres);
    return 0;
}

messageBAL * creeMessage(char *data,int idEmetteur)
{
    messageBAL * message = malloc(sizeof(messageBAL));

    message->idEmetteur=idEmetteur;
    message->tailleData=strlen(data);
    message->data=(char*)malloc(sizeof(char)*message->tailleData);
    strcpy(message->data,data);
    return message;
}

struct elementMessage * initElementMessage(void)
{
    struct elementMessage * returnElement = malloc(sizeof(struct elementMessage));
    returnElement->messageBALActuel = creeMessage("",0);
    returnElement->suiv = NULL;
    return returnElement;
}

struct listeMessage * initListeMessage(void)
{
    struct listeMessage * l=malloc(sizeof(struct listeMessage));
    l->debut=initElementMessage();
    l->fin=initElementMessage();
    l->courant=initElementMessage();
    return l;
}

void ajoutListeMessage(struct listeMessage * listeActuel,messageBAL * leMessage)                                 
{
    struct elementMessage * elementActuel = malloc(sizeof(struct elementMessage));    
    elementActuel->messageBALActuel=leMessage;                                                                                     
    elementActuel->suiv=listeActuel->courant;                                                                                        
    listeActuel->debut=elementActuel;                                                     
    listeActuel->courant=elementActuel;                                                   
}

void afficheListeMessage(struct listeMessage listeActuel)
{
    struct elementMessage * elementFinal = listeActuel.fin;
    struct elementMessage * elementCourant = listeActuel.courant;
    while(elementCourant->suiv != elementFinal->suiv)
    {
        printf("%s\n",elementCourant->messageBALActuel->data);
        elementCourant=elementCourant->suiv;
    }
}

BAL * creerBAL(int idRecepteur, struct listeMessage * messageRecepteur)
{
    BAL * boiteAuxLettres = malloc(sizeof(BAL));

    boiteAuxLettres->idRecepteur=idRecepteur;
    boiteAuxLettres->actualMessages=messageRecepteur;
    return boiteAuxLettres;
}

struct elementBAL * initElementBAL(void)
{
    struct elementBAL * returnElement = malloc(sizeof(struct elementBAL));
    struct listeMessage * lVide = initListeMessage();
    returnElement->BALActuel = creerBAL(0,lVide);
    returnElement->suiv = NULL;
    return returnElement;
}

struct listeBAL initListeBAL(void)
{
    struct listeBAL l;
    l.debut=initElementBAL();
    l.fin=initElementBAL();
    l.courant=initElementBAL();
    return l;
}

void ajoutListeBAL(struct listeBAL * listeActuel,BAL * laBoiteAuxLettres)
{
    struct elementBAL * elementActuel = malloc(sizeof(struct elementBAL));    
    elementActuel->BALActuel=laBoiteAuxLettres;                                                                                     
    elementActuel->suiv=listeActuel->courant;                                                                                        
    listeActuel->debut=elementActuel;                                                     
    listeActuel->courant=elementActuel; 
}

void afficheListeBAL(struct listeBAL listeActuel)
{
    struct elementBAL * elementFinal = listeActuel.fin;
    struct elementBAL * elementCourant = listeActuel.courant;
    while(elementCourant->suiv != elementFinal->suiv)
    {
        printf("Recepteur : %d\n",elementCourant->BALActuel->idRecepteur);
        afficheListeMessage(*(elementCourant->BALActuel->actualMessages));
        elementCourant=elementCourant->suiv;
    }
}

struct elementBAL * existInListBAL(struct listeBAL listeActuel, int idRecepteur, bool * boolRetour)
{
    struct elementBAL * elementFinal = listeActuel.fin;
    struct elementBAL * elementCourant = listeActuel.courant;
    while(elementCourant->suiv != elementFinal->suiv)
    {
        if(elementCourant->BALActuel->idRecepteur == idRecepteur)
        {
            *boolRetour = true;
            return elementCourant;
        }
        elementCourant=elementCourant->suiv;
    };
    *boolRetour = false;
    return elementFinal;
}

void nouveauMessage(struct listeBAL * b,int idEmetteur,int idRecepteur,char *data)
{
    bool testExistInList;
    struct elementBAL * elementNouveauMessage = existInListBAL(*b,idRecepteur,&testExistInList);
    printf("testExistInList = %d\n",testExistInList);
    if(testExistInList)
    {
        ajoutListeMessage(elementNouveauMessage->BALActuel->actualMessages,creeMessage(data,idEmetteur));
    }
    else
    {
        struct listeMessage * newListMessage = initListeMessage();
        ajoutListeMessage(newListMessage,creeMessage(data,idEmetteur));
        ajoutListeBAL(b,creerBAL(idRecepteur,newListMessage));
    }
}