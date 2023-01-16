#ifndef HEADER_BAL
#define HEADER_BAL

#include "tsock.h"

typedef struct{
    char *data;
    int tailleData;
    int idEmetteur;
}messageBAL;

struct elementMessage{
    messageBAL * messageBALActuel;
    struct elementMessage * suiv;
};

struct listeMessage{
    struct elementMessage * debut;
    struct elementMessage * courant;
    struct elementMessage * fin;
};

typedef struct{
    int idRecepteur;
    struct listeMessage * actualMessages;
}BAL;

struct elementBAL{
    BAL * BALActuel;
    struct elementBAL * suiv;
};

struct listeBAL{
    struct elementBAL * debut;
    struct elementBAL * courant;
    struct elementBAL * fin;
};

messageBAL * creeMessage(char *data,int idEmetteur);
struct elementMessage * initElementMessage(void);
struct listeMessage * initListeMessage(void);
void ajoutListeMessage(struct listeMessage * listeActuel,messageBAL * leMessage);
void afficheListeMessage(struct listeMessage listeActuel);

BAL * creerBAL(int idRecepteur, struct listeMessage * messageRecepteur);
struct elementBAL * initElementBAL(void);
struct listeBAL initListeBAL(void);
void ajoutListeBAL(struct listeBAL * listeActuel,BAL * laBoiteAuxLettres);
void afficheListeBAL(struct listeBAL listeActuel);

struct elementBAL * existInListBAL(struct listeBAL listeActuel, int idRecepteur, bool * boolRetour);
void nouveauMessage(struct listeBAL * b,int idEmetteur,int idRecepteur,char *data);

#endif