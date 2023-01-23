#ifndef HEADER_PUIT
#define HEADER_PUIT

#include "tsock.h"
#include "bal.h"

/**
 * @brief Fonction principale pour le puit. Peut lancer en mode TCP/UDP avec la fonction receiveMultipleData()
 * Vérifie si la variable isBAL est à 1 -> active le mode boite aux lettres avec la fonction du même nom
 * 
 * @param nombreMessage int, le nombre de message à envoyer.
 * @param tailleMessage int, la taille de chacun de ces messages.
 * @param isTCP         int, 1 -> TCP, 0 -> UDP         
 * @param port          int, numéro du port
 * @param ipAddress     char *, adresse IP
 * @param isBAL         int, 1-> Mode Boite aux Lettres
 * @return int 0-> si réussite, autre sinon
 */
int launchPuit(int nombreMessage,int tailleMessage,int isTCP,int port,char * ipAddress,int isBAL);

/**
 * @brief Permet l'initialisation avec la primitive socket() ainsi qu'initStructSocket() à l'aide d'un port et d'une adresse IP.
 * Fonction bind() est ensuite réalisée pour se connecter au serveur. Qu'on soit en mode UDP/TCP
 * 
 * @param socketType    SOCK_STREAM pour TCP ou SOCK_DGRAM pour UDP
 * @param socketStruct  struct sockaddr_in *, la structure du socket sous forme de pointeur
 * @param port          int, numéro du port
 * @param ipAddress     char *, adresse IP   
 * @return int, renvoi le socket crée
 */
int initSocket(int socketType, struct sockaddr_in * socketStruct, int port, char * ipAddress);

/**
 * @brief Pour un nombre de message donné (-1 -> infini) recevra des messages avec une taille précise.
 * à l'aide de isTCP utilise différente primitive (listen, accept et read pour TCP, recvfrom pour UDP)
 * Dans le cas d'UDP si nombreMessage = -1 (infini) écoutera à l'infini la source. Pour TCP fermera la connexion
 * une fois la connexion finie [A améliorer].
 * 
 * @param nombreMessages 
 * @param tailleMessage 
 * @param sock 
 * @param socketStruct 
 * @param isTCP 
 * @return int 
 */
int receiveMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in socketStruct, int isTCP);

/**
 * @brief Créer une structure listeBAL pour stocker les différentes lettres des emetteurs.
 * Uniquement en mode TCP lit la première couche protocolaire pour connaître le mode de la source.
 * Si MODE_RECEPTEUR alors la primitive receptionRecepteur est lancée.
 * Si MODE_EMIS alors la primitive receptionEmetteur est lancée.
 * Ferme le socket TCP une fois les messages reçues et relance la connexion avec listen() et accept(). 
 * 
 * @param socketStruct  struct sockaddr_in *, la structure du socket sous forme de pointeur
 * @param socketType    SOCK_STREAM pour TCP ou SOCK_DGRAM pour UDP
 * @param port          int, numéro du port
 * @param ipAddress     char *, adresse IP   
 */
void modeBoiteAuxLettres(struct sockaddr_in socketStruct, int socketType, int port, char * ipAddress);

/**
 * @brief à partir d'un socket, lit le message reçu et l'ajoute dans la boite aux lettre donnée en paramètre.
 * 
 * @param sock                  int, socket premettant d'utiliser la primitive read()
 * @param tailleMessagePrevu    int, taille du message prévu donné par la couche protocolaire de l'application
 * @param tailleMessageRecu     int*, taille réel donné par read()
 * @param emetteur              int, numéro de l'émetteur 
 * @param recepteur             int, numéro du recepteur
 * @param boiteAuxLettres       struct listeBAL*, pointeur visant la boite aux lettres
 */
void receptionEmetteur(int sock, int tailleMessagePrevu, int * tailleMessageRecu, int emetteur, int recepteur, struct listeBAL *boiteAuxLettres);

#endif