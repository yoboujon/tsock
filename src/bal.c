#include <stdio.h>                                  
#include <stdlib.h>                                 
#include <string.h>                                 
#include <stdbool.h> 

typedef struct{
    char *data;
    int tailleData;
    int idEmeteur;
}messageBAL;

struct elementMessage{
    messageBAL * messageBALActuel;
    struct messageBAL * suiv;
};

struct listeMessage{
    struct elementMessage * debut;
    struct elementMessage * courant;
    struct elementMessage * fin;
};

messageBAL * creeMessage(char *data,int idEmeteur);
struct elementMessage * initElement(void);
struct listeMessage initListe(void);

int main(void){
    initElement();
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

struct elementMessage * initElement(void)
{
    struct elementMessage * returnElement = malloc(sizeof(struct elementMessage));
    returnElement->messageBALActuel = creeMessage("",0);
    returnElement->suiv = NULL;
    return returnElement;
}

struct listeMessage initListe(void)
{
    struct listeMessage l;
    l.debut=initElement();
    l.fin=initElement();
    l.courant=initElement();
    return l;
}