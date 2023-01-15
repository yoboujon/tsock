#ifndef HEADER_PUIT
#define HEADER_PUIT

#include "tsock.h"

int launchPuit(int nombreMessage,int tailleMessage,int isTCP,int port,char * ipAddress);
int receiveMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in socketStruct, int isTCP);

#endif