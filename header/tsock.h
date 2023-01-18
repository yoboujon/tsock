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

void setNbMessage(int * nb, int source);
void printInfo(int source, int isTCP, int nbMessage, int taille, int portNumber, char ipAddress[]);
void initStructSocket(struct sockaddr_in *socketTempStruct, int source, int port, char * ipAddress);
void getNonOtpArgs(char ** argv, int argc, int * portNumber, char * ipAddress[]);
void formatText(char * actualMessage, int num, int tailleMessage, char messageChar);
int exitMax(int var,int tailleMax);

char * formatTextParam(int numEmetteur, int numRecepteur, int tailleMessage, int nbMessage);
char * formatTextMessage(char * message, int tailleMessage);
int convertion(int nbr,char *numbuffer);
int gestionOffset(char *actualMessage,int encadrementHaut,int encadrementBas,int nbr);
int testProtocol(void);

int recuperationParam(char * msgParam, int * messageOrPram, int * numEmetteurParam, int * numRecepeteurParam, int * numTailleMessageParam, int * nbMessageParam);
int int2String(char *msgParam, int offset);
#endif