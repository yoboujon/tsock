#ifndef HEADER_TSOCK
#define HEADER_TSOCK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "bal.h"

#define NBMESSAGE_DEFAULT   10
#define MAX_MESSAGE         4
#define MODE_PARAMETRE      0
#define MODE_RECEPTEUR      1
#define MODE_EMIS           2

/**
 * @brief Permet de gérer le nombre de message envoyés s'ils ne sont pas précisés
 * par l'utilisateur (uniquement en mode source).
 * Ici le nombre par défaut est définie par NBMESSAGE_DEFAULT.
 * A noter que pour le puit, ce nombre est laissé à -1 car le nombre de message recu
 * est infini.
 * @author Yohan Boujon
 * 
 * @param nb        int *, pointeur sur l'entier à modifier
 * @param source    source, vérifie si nous sommes bien en mode source
 */
void setNbMessage(int * nb, int source);

/**
 * @brief Affiche les informations principales rentrées par l'utilisateur, notamment : le mode, le nombre de messages,
 * la taille des messages, le port, l'adresse IP, le mode (TCP/UDP).
 * @author Yohan Boujon
 * 
 * @param source        int, source ou puit
 * @param isTCP         int, TCP ou UDP
 * @param nbMessage     int, le nombre de message à envoyer/à recevoir (-1 en reception est lu comme infini)
 * @param taille        int, la taille de chaque message
 * @param portNumber    int, numéro du port
 * @param ipAddress     char*, l'adresse IP sous chaîne de caractère
 */
void printInfo(int source, int isTCP, int nbMessage, int taille, int portNumber, char ipAddress[]);

/**
 * @brief Initialise la structure du socket pour avoir le port et l'ip. Si le mode choisi est reception : l'ip est ignorée.
 * Utilise la fonction gethostbyname pour récupérer l'IPv4 à partir d'une chaîne de caractère quelconque.
 * @author Yohan Boujon
 * 
 * @param socketTempStruct  struct sockaddr_in*, pointeur sur la structure (doit être initialisée au préalable).
 * @param source            int, source ou puit -> si à 0 alors ipAddress sera ignoré et défini par INADDR_ANY.
 * @param port              int, le port du socket.
 * @param ipAddress         char *, l'Adresse IP du socket.
 */
void initStructSocket(struct sockaddr_in *socketTempStruct, int source, int port, char * ipAddress);

/**
 * @brief Récupère toutes les informations qui n'utilisent pas getopt,
 * notamment le port ainsi que l'ip.
 * @author Yohan Boujon
 * 
 * @param argv          char **, liste de chaîne de caractère des arguments
 * @param argc          int, nombre d'arguments (IP -> argc-1 et Port -> argc-2)
 * @param portNumber    int *, numéro du port retourné
 * @param ipAddress     char **, pointeur faire une chaîne de caractère de l'adresse ip retournée
 */
void getNonOtpArgs(char ** argv, int argc, int * portNumber, char * ipAddress[]);

/**
 * @brief [utile pour source.c] à partir d'un numéro, d'un message et d'une taille
 * Créer une trame avec 5 caractères pour le numéro du message, et le reste pour le message
 * @author Yohan Boujon
 * 
 * @param actualMessage char *, Doit être initialisé. Message modifié.
 * @param num           int, numéro du message, ne doit pas dépasser 9999.
 * @param tailleMessage int, taille du message final.
 * @param messageChar   char, caractère du message, sera répété pour 4-tailleMessage fois.
 */
void formatText(char * actualMessage, int num, int tailleMessage, char messageChar);

/**
 * @brief Permet, pour une taille max donnée. De quitter le programme si cette valeur est dépassée.
 * @author Simon Paris
 * 
 * @param var       int, variable à tester.
 * @param tailleMax int, le test.
 * @return int retourne 0 si cela s'est bien executé.
 */
int exitMax(int var,int tailleMax);

/**
 * @brief Converti plusieurs paramètres en une chaîne de caractère. Couche protocolaire de l'application.
 * Sous la forme suivante : [messageType[1],emetteur/recepteur[4],tailleMessage[4],nbMessage[4]]
 * @author Simon Paris
 * @author Yohan Boujon
 * 
 * @param modeParam         int, MODE_PARAMETRE pour un paramètre pure, MODE_RECEPTEUR -> -r ##, MODE_EMIS -> -e ##.
 * @param emeteurRecepteur  int, numéro de l'émetteur (-e ##, ou idEmetteur) ou du recepteur (-r ##, ou idRecepteur).
 * @param tailleMessage     int, taille du message à envoyer.
 * @param nbMessage         int, nombre de message à envoyer [inutilisé].
 * @return char* chaîne de caractère à envoyer via TCP.
 */
char * formatTextParam(int modeParam, int emeteurRecepteur, int tailleMessage, int nbMessage);

/**
 * @brief Ajoute un numéro au début du message à envoyer.
 * @author Simon Paris
 * 
 * @param message       char *, chaîne de caractère du message originel.
 * @param tailleMessage int, taille du message "message".
 * @return char* renvoi la chaîne modifiée.
 */
char * formatTextMessage(char * message, int tailleMessage);

/**
 * @brief Converti un nombre en chaîne de caractre et le place dans la chaîne actualMessage.
 * La taille de ce dernier doit être connu au préalable
 * @author Simon Paris
 * 
 * @param actualMessage     char *, message à modifier.
 * @param encadrementHaut   int, offset du début du nombre.
 * @param encadrementBas    int, offset de la fin du nombre.
 * @param nbr               int, nombre à convertir en chaîne de caractère, ne doit pas dépasser 9999.
 * @return int retourne encadrementHaut.
 */
int gestionOffset(char *actualMessage,int encadrementHaut,int encadrementBas,int nbr);

/**
 * @brief Teste les différentes fonctions permettant de gérer le protocole,
 * autant en lecture qu'écriture
 * @author Simon Paris
 * 
 * @return int 0 si réussi
 */
int testProtocol(void);

/**
 * @brief Récupération de chaque paramètres grâce à la trame précédente.
 * @author Simon Paris
 * @author Yohan Boujon
 * 
 * @param msgParam              char *, chaîne reçue avant le message, couche protocolaire.
 * @param messageOrPram         int *, renvoi MODE_PARAM,MODE_SOURCE ou MODE_EMIS.
 * @param numEmetteurRecepteur  int *, renvoi le numéro de l'émetteur/recepteur. 
 * @param numTailleMessageParam int *, renvoi la taille du message émis.
 * @param nbMessageParam        int *, renvoi le nombre de message a recevoir [Inutilisé]
 * @return int 
 */
int recuperationParam(char * msgParam, int * messageOrPram, int * numEmetteurRecepteur, int * numTailleMessageParam, int * nbMessageParam);

/**
 * @brief converti une chaîne de caractère spécifique (protocolaire) en entiers avec une gestion d'offset.
 * La taille lue entre chaque offset est définie par MAX_MESSAGE.
 * @author Simon Paris
 * @author Yohan Boujon
 * 
 * @param data      char *, la chaîne de caractère à lire.
 * @param offset    int, offset : décalage de n caractère sur la chaîne data.
 * @return int nombre récupéré entre 0 et 9999.
 */
int protocol2int(char * data, int offset);

/**
 * @brief Fonction simplifiée pour le connect() du mode TCP.
 * @author Yohan Boujon
 * 
 * @param sock          int, le socket créé par avance
 * @param socketStruct  struct sockaddr_in, structure du socket
 * @param tailleSocket  int, sizeof(socketStruct)
 */
int connectTCP(int sock, struct sockaddr_in socketStruct, int tailleSocket);

/**
 * @brief Récupère la longueur émise par la fonction write() (TCP) ou sendto() (UDP)
 * Si elle est égale à -1 : ferme le programme car l'envoi n'a pas pu être effectué.
 * Sinon affiche les divers paramètres avec un compteur de message (count).
 * @author Yohan Boujon
 * 
 * @param sendingMessage    char *, le message à envoyer 
 * @param tailleMessage     int, la taille du message théorique
 * @param longueurEmis      int, la taille du message à envoyer (-1 -> Erreur)
 * @param count             int, compteur
 */
void printAndVerif(char * sendingMessage,int tailleMessage,int longueurEmis, int count);

/**
 * @brief Permet l'initialisation avec la primitive socket() ainsi qu'initStructSocket() à l'aide d'un port et d'une adresse IP.
 * Fonction bind() est ensuite réalisée pour se connecter au serveur. Qu'on soit en mode UDP/TCP.
 * @author Yohan Boujon
 * 
 * @param socketType    SOCK_STREAM pour TCP ou SOCK_DGRAM pour UDP
 * @param socketStruct  struct sockaddr_in *, la structure du socket sous forme de pointeur
 * @param port          int, numéro du port
 * @param ipAddress     char *, adresse IP   
 * @return int, renvoi le socket crée
 */
int initSocket(int socketType, struct sockaddr_in * socketStruct, int port, char * ipAddress);

/**
 * @brief Ouvre un socket à l'aide d'un socketType
 * 
 * @param socketType    SOCK_STREAM pour TCP ou SOCK_DGRAM pour UDP
 * @return int le socket créé
 */
int openSocket(int socketType);

/**
 * @brief utilise la fonction listen et accept de TCP pour créer un nouveau socket.
 * 
 * @param sock              int, le socket pour lancer la connexion.
 * @param socketStruct      struct sockaddr_in*, la structure du socket sous forme de pointeur.
 * @param sizeSocketStruct  int, sizeof(*socketStruct)
 * @param closeSocket       bool, 1-> ferme le socket sock.
 * @return int, le socket crée par accept().
 */
int listenAndAccept(int sock, struct sockaddr_in * socketStruct, int * sizeSocketStruct, bool closeSocket);

#endif