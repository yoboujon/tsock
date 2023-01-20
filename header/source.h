#ifndef HEADER_SOURCE
#define HEADER_SOURCE
#include "tsock.h"

int launchSource(int nombreMessage,int tailleMessage,int isTCP,int port,char * ipAddress,int emetteur,int recepteur);
int sendMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in * socketStruct, int sizeSocketStruct, int isTCP);
void connectTCP(int sock, struct sockaddr_in socketStruct, int tailleSocket);
void modeEmetteur(int emetteur,int nombreMessage,int tailleMessage,int sock,struct sockaddr_in * socketStruct,int tailleSocketStruct);
void modeRecepteur(int recepteur,int sock,struct sockaddr_in * socketStruct,int tailleSocketStruct);
void printAndVerif(char * sendingMessage,int tailleMessage,int longueurEmis, int count);

#endif