#ifndef HEADER_IPTABLE
#define HEADER_IPTABLE

#include "tsock.h"

/**
 * @brief Test la liste ipTable
 * 
 * @return int 0-> si réussite.
 */
int iptableTest();

/**
 * @struct ipTable
 * @brief definition de la structure d'une table d'IP
 * 
 * @var ipTable::ipAddress
 * Adresse IP sous forme de char*
 * @var ipTable::idEmetteur
 * Numéro de l'émetteur associé à l'ip
 */
typedef struct{
    char *ipAddress;
    int tailleipAddress;
    int idEmetteur;
}ipTable;

/**
 * @struct elementipTable
 * @brief Element dans une liste de table d'IP
 * 
 * @var elementipTable::actualIpTable
 * Pointeur vers la table d'IP de l'élément
 * @var elementipTable::suiv
 * Pointeur vers le prochain élément
 */
struct elementIpTable{
    ipTable * actualIpTable;
    struct elementIpTable * suiv;
};

/**
 * @struct listeIpTable
 * @brief Liste d'éléments table d'IP
 * 
 * @var listeIpTable::debut
 * Pointeur vers le premier élément
 * @var listeIpTable::courant
 * Pointeur vers l'élément sélectionné
 * @var listeIpTable::fin
 * Pointeur vers l'élément final
 */
struct listeIpTable{
    struct elementIpTable * debut;
    struct elementIpTable * courant;
    struct elementIpTable * fin;
    int taille;
};

/**
 * @brief Permet l'initialisation d'une struture ipTable avec une IP et un idEmetteur donné.
 * 
 * @param ipAddress     char*, Adresse IP associée à l'émétteur.
 * @param idEmetteur    int, numéro de l'émetteur du message.
 * @return ipTable* table d'IP initialisé avec les paramètres donnés.
 */
ipTable * creeIpTable(char *ipAddress,int idEmetteur);

/**
 * @brief Initialise la structure elementIpTable avec un malloc.
 * L'élément crée renvoi vers une adresse NULL.
 * 
 * @return struct elementIpTable* element initialisé
 */
struct elementIpTable * initElementIpTable(void);

/**
 * @brief Initialise plusieurs éléments (debut,courant et fin) avec initElementIpTable().
 * 
 * @return struct listeIpTable* liste de tables d'IP NULL mais alloué.
 */
struct listeIpTable * initListeIpTable(void);

/**
 * @brief Ajoute un tableau d'IP dans la liste de des tableaux d'IP :
 * Mets à jour le pointeur courant ainsi que debut.
 * 
 * @param listeActuel   struct listeIpTable *,la liste à modifier.
 * @param lipTable      ipTable*, pointeur sur le tableau d'IP à ajouter à la liste.
 */
void ajoutListeIpTable(struct listeIpTable * listeActuel,ipTable * lipTable);

/**
 * @brief Affiche l'intégralité des IP/Id Emetteurs.
 * 
 * @param listeActuel   struct listeIpTable, liste à afficher.
 */
void afficheListeIpTable(struct listeIpTable listeActuel);

/**
 * @brief Permet de vérifier si une Adresse IP existe déjà dans une liste d'IP donnée
 * Ne modifie pas le pointeur courant mais parcours toute la liste. Modifie le boolRetour pour savoir si c'est vrai ou non.
 * Renvoi l'élément correspondant si c'est le cas. Renvoi un élément vide sinon.
 * 
 * @param listeActuel   struct listeBAL, la liste à vérifier
 * @param idEmetteur    char*, Adresse IP à vérifier.
 * @param boolRetour    bool*, 1->Element retourné trouvé dans la liste, 0->Element NULL, non trouvé dans la liste
 * @return struct elementIpTable*, element trouvé si dans la liste, NULL sinon.
 */
struct elementIpTable * existInListIP(struct listeIpTable listeActuel, char* ipAdress, bool * boolRetour);

#endif