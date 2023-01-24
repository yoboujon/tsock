#ifndef HEADER_SOURCE
#define HEADER_SOURCE
#include "tsock.h"

/**
 * @brief Lance le mode source. Gère UDP comme TCP et le mode Emetteur ainsi que Recepteur en TCP uniquement.
 * Créer un socket(), un struct sockaddr_in et lance les diverses fonctions de connexion :
 * connectTCP() puis sendMultipleData() pour le mode TCP
 * sendMultipleData() uniquement pour le mode UDP
 * 
 * @param nombreMessage int, le nombre de message à envoyer.
 * @param tailleMessage int, la taille de chacun de ces messages.
 * @param isTCP         int, 1 -> TCP, 0 -> UDP         
 * @param port          int, numéro du port
 * @param ipAddress     char *, adresse IP
 * @param emetteur      int, numéro Emetteur
 * @param recepteur     int, numéro Recepteur
 * @return int 0-> si réussite, autre sinon
 */
int launchSource(int nombreMessage,int tailleMessage,int isTCP,int port,char * ipAddress,int emetteur,int recepteur);

/**
 * @brief Envoi de trame(s) en mode UDP/TCP avec un format particulier :
 * [msgID[5], caractères répétés] -> les caractères vont de a à z.
 * 
 * @param nombreMessages    int, le nombre de message à envoyer.
 * @param tailleMessage     int, la taille de chacun de ces messages.
 * @param sock              int, le socket créé par avance
 * @param socketStruct      struct sockaddr_in *, la structure du socket sous forme de pointeur
 * @param sizeSocketStruct  int, sizeof(*socketStruct). Important pour l'envoi en UDP
 * @return int 0-> si réussite, autre sinon
 */
int sendMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in * socketStruct, int sizeSocketStruct, int isTCP);

/**
 * @brief Permet d'envoyer un/des message(s) avec une certaine taille spécifiquement
 * pour la boîte au lettres. Le numéro du recepteur (nommé emetteur ici) est précisé.
 * Une trame sera tout d'abord émise suivant le protocole de l'application avec la fonction formatTestParam()
 * Ensuite une deuxième trame est émise avec formatTextMessage().
 * 
 * @param emetteur              int, numéro de l'émetteur utilisateur donc du recepteur pour le message
 * @param nombreMessage         int, nombre de message à envoyer
 * @param tailleMessage         int, la taille de ces messages
 * @param sock                  int, numéro du socket crée par avance
 * @param socketStruct          struct sockaddr_in *, pointeur sur la structure socket
 * @param tailleSocketStruct    int, sizeof(*socketStruct)
 */
void modeEmetteur(int emetteur,int nombreMessage,int tailleMessage,int sock,struct sockaddr_in * socketStruct,int tailleSocketStruct);

/**
 * @brief Permet de recevoir les messages de la boite aux lettres à l'émetteur spécifié.
 * 
 * @param recepteur             int, numéro du recepteur utilisateur donc de l'emetteur pour la boite aux lettres
 * @param sock                  int, numéro du socket crée par avance
 * @param socketStruct          struct sockaddr_in *, pointeur sur la structure socket
 * @param tailleSocketStruct    int, sizeof(*socketStruct)
 * @param port                  int, numéro du port
 * @param ipAddress             char *, adresse IP
 */
void modeRecepteur(int recepteur,int sock,struct sockaddr_in * socketStruct,int tailleSocketStruct,int port,char * ipAddress);

#endif