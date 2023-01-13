#ifndef HEADER_PUIT
#define HEADER_PUIT

#include "tsock.h"
int launchPuit(int nombreMessage);
int receiveMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in socketStruct);

#endif