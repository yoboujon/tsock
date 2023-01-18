#include "../header/bal.h"

int bal(void){
    struct listeMessage l = initListeMessage();
    messageBAL * messageBAL = creeMessage("Renvoi moi mon pdf asap. -Simon",1);
    ajoutListe(&l,messageBAL);
    afficheListeMessage(l);
    return 0;
}

messageBAL * creeMessage(char *data,int idEmeteur)
{
    messageBAL * message = malloc(sizeof(messageBAL));

    message->idEmeteur=idEmeteur;
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

struct listeMessage initListeMessage(void)
{
    struct listeMessage l;
    l.debut=initElementMessage();
    l.fin=initElementMessage();
    l.courant=initElementMessage();
    return l;
}

void ajoutListe(struct listeMessage * listeActuel,messageBAL * leMessage)                                 
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