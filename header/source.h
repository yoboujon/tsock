#ifndef HEADER_SOURCE
#define HEADER_SOURCE
#include "tsock.h"

int launchSource(int nombreMessage,int tailleMessage,int isTCP,int port,char * ipAddress);
int sendMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in * socketStruct, int sizeSocketStruct, int isTCP);

#endif