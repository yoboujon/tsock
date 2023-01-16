#ifndef HEADER_BAL
#define HEADER_BAL

#include "tsock.h"

typedef struct{
    char *data;
    int tailleData;
    int idEmeteur;
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

messageBAL * creeMessage(char *data,int idEmeteur);
struct elementMessage * initElementMessage(void);
struct listeMessage initListeMessage(void);
void ajoutListe(struct listeMessage * listeActuel,messageBAL * leMessage);
void afficheListeMessage(struct listeMessage listeActuel);

#endif