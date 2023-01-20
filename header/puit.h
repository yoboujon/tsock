#ifndef HEADER_PUIT
#define HEADER_PUIT

#include "tsock.h"
#include "bal.h"

int launchPuit(int nombreMessage,int tailleMessage,int isTCP,int port,char * ipAddress,int isBAL);
int initSocket(int socketType, struct sockaddr_in * socketStruct, int port, char * ipAddress);
int receiveMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in socketStruct, int isTCP);
int modeBoiteAuxLettres(struct sockaddr_in socketStruct, int socketType, int port, char * ipAddress);
void receptionEmetteur(int sock, int tailleMessagePrevu, int * tailleMessageRecu, int emetteur, int recepteur, struct listeBAL *boiteAuxLettres);

#endif