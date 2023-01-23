#ifndef HEADER_BAL
#define HEADER_BAL

#include "tsock.h"

/**
 * @brief Fonction de test pour les différentes primitive de bal.h
 * Inutilisée sur le programme final.
 * 
 * @return int -> 0 si réussite
 */
int bal(void);

/**
 * @struct messageBAL
 * @brief definition de la structure d'un message BAL
 * 
 * @var messageBAL::data
 * Messgae sous forme d'un tableau de caractère
 * @var messageBAL::tailleData
 * Taille du message
 * @var messageBAL::idEmetteur
 * Numéro de l'émetteur qui a envoyé le message
 */
typedef struct{
    char *data;
    int tailleData;
    int idEmetteur;
}messageBAL;

/**
 * @struct elementMessage
 * @brief Element dans une liste de Messages
 * 
 * @var elementMessage::messageBALActuel
 * Pointeur vers le message de l'élément
 * @var elementMessage::suiv
 * Pointeur vers le prochain élément
 */
struct elementMessage{
    messageBAL * messageBALActuel;
    struct elementMessage * suiv;
};

/**
 * @struct listeMessage
 * @brief Liste d'éléments messages
 * 
 * @var listeMessage::debut
 * Pointeur vers le premier élément
 * @var listeMessage::courant
 * Pointeur vers l'élément sélectionné
 * @var listeMessage::fin
 * Pointeur vers l'élément final
 */
struct listeMessage{
    struct elementMessage * debut;
    struct elementMessage * courant;
    struct elementMessage * fin;
};

/**
 * @struct BAL
 * @brief definition de la structure d'une Boite aux Lettres
 * 
 * @var BAL::idRecepteur
 * Numéro du recepteur ayant reçu les messages
 * @var BAL::actualMessages
 * Liste pointant sur les messages reçus
 */
typedef struct{
    int idRecepteur;
    struct listeMessage * actualMessages;
}BAL;

/**
 * @struct elementBAL
 * @brief Element dans une liste de Messages
 * 
 * @var elementBAL::BALActuel
 * Pointeur vers la boite aux lettres de l'élément
 * @var elementBAL::suiv
 * Pointeur vers le prochain élément
 */
struct elementBAL{
    BAL * BALActuel;
    struct elementBAL * suiv;
};

/**
 * @struct listeBAL
 * @brief Liste d'éléments BAL
 * 
 * @var listeBAL::debut
 * Pointeur vers le premier élément
 * @var listeBAL::courant
 * Pointeur vers l'élément sélectionné
 * @var listeBAL::fin
 * Pointeur vers l'élément final
 */
struct listeBAL{
    struct elementBAL * debut;
    struct elementBAL * courant;
    struct elementBAL * fin;
};

/**
 * @brief Permet l'initialisation d'une struture messageBAL avec un message et un idEmetteur donné.
 * 
 * @param data          char*, chaîne de caractère de la donnée.
 * @param idEmetteur    int, numéro de l'émetteur du message.
 * @return messageBAL* message initialisé avec les paramètres donnés.
 */
messageBAL * creeMessage(char *data,int idEmetteur);

/**
 * @brief Initialise la structure elementMessage avec un malloc.
 * L'élément crée renvoi vers une adresse NULL.
 * 
 * @return struct elementMessage* element initialisé
 */
struct elementMessage * initElementMessage(void);

/**
 * @brief Initialise plusieurs éléments (debut,courant et fin) avec initElementMessage().
 * 
 * @return struct listeMessage* liste de message NULL mais alloué.
 */
struct listeMessage * initListeMessage(void);

/**
 * @brief Ajoute un message dans la liste de message :
 * Mets à jour le pointeur courant ainsi que debut.
 * 
 * @param listeActuel   struct listeMessage *,la liste à modifier.
 * @param leMessage     messageBAL*, pointeur sur le message à ajouter à la liste.
 */
void ajoutListeMessage(struct listeMessage * listeActuel,messageBAL * leMessage);

/**
 * @brief Affiche l'intégralité des Messages pour tous les Emetteurs.
 * 
 * @param listeActuel   struct listeMessage, liste à afficher.
 */
void afficheListeMessage(struct listeMessage listeActuel);

/**
 * @brief Permet l'initialisation d'une struture BAL avec un idRecepteur et un messageRecepteur donné.
 * 
 * @param idRecepteur       int, numéro du recepteur.
 * @param messageRecepteur  struct listeMessage*, liste des messages du recepteur.
 * @return BAL* boite aux lettres initialisée avec les paramètres donnés.
 */
BAL * creerBAL(int idRecepteur, struct listeMessage * messageRecepteur);

/**
 * @brief Initialise la structure elementBAL avec un malloc.
 * L'élément crée renvoi vers une adresse NULL.
 * 
 * @return struct elementBAL* element initialisé
 */
struct elementBAL * initElementBAL(void);

/**
 * @brief Initialise plusieurs éléments (debut,courant et fin) avec initElementBAL().
 * 
 * @return struct listeBAL liste de Boite aux lettres NULLes mais allouées.
 */
struct listeBAL initListeBAL(void);

/**
 * @brief Ajoute une boite aux letres dans la liste de BAL :
 * Mets à jour le pointeur courant ainsi que debut.
 * 
 * @param listeActuel   struct listeBAL *,la liste à modifier.
 * @param leMessage     BAL*, pointeur sur la boite aux lettres à ajouter à la liste.
 */
void ajoutListeBAL(struct listeBAL * listeActuel,BAL * laBoiteAuxLettres);

/**
 * @brief Affiche l'intégralité de la Boite Aux Lettres pour tous les Récepteurs.
 * Utilisation de la fonction afficheListeMessage
 * 
 * @param listeActuel   struct listeBAL, liste à afficher.
 */
void afficheListeBAL(struct listeBAL listeActuel);

/**
 * @brief Permet de vérifier si un idRecepteur existe dans une liste de Boite Aux Lettres donnée
 * Ne modifie pas le pointeur courant mais parcours toute la liste. Modifie le boolRetour pour savoir si c'est vrai ou non.
 * Renvoi l'élément correspondant si c'est le cas. Renvoi un élément vide sinon.
 * 
 * @param listeActuel   struct listeBAL, la liste à vérifier
 * @param idRecepteur   int, idRecepteur à vérifier.
 * @param boolRetour    bool*, 1->Element retourné trouvé dans la liste, 0->Element NULL, non trouvé dans la liste
 * @return struct elementBAL*, element trouvé si dans la liste, NULL sinon.
 */
struct elementBAL * existInListBAL(struct listeBAL listeActuel, int idRecepteur, bool * boolRetour);

/**
 * @brief Crée un nouveau message dans la liste de Boite Aux Lettres.
 * Utilisation de la fonction existInListBAL() -> Créer une nouvelle BAL si le recepteur n'existe pas.
 * 
 * @param b             struct listeBAL*, la liste à modifier.
 * @param idEmetteur    int, le numéro de l'émetteur qui a envoyé le message.
 * @param idRecepteur   int, le numéro du recepteur qui va recevoir ce message.
 * @param data          char*, le message reçu.
 */
void nouveauMessage(struct listeBAL * b,int idEmetteur,int idRecepteur,char *data);

/**
 * @brief Récupère la liste de message d'un recepteur précis
 * Attention de vérifier si la liste est vide -> si c'est le cas,
 * alors le recepteur n'existe pas.
 * 
 * @param b liste de BoîteAuxLettres
 * @param idRecepteur 
 * @return struct listeMessage* 
 */
struct listeMessage * getMessages(struct listeBAL b, int idRecepteur);

/**
 * @brief [WIP] Permet de renvoyer les trames de chaque messages présentent dans la boîte aux lettres
 * suivant le protocole de l'application.
 * 
 * @param l struct listeMessage, la liste à envoye via TCP.
 */
void formatListMessage(struct listeMessage l);

#endif