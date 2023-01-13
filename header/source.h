#ifndef HEADER_SOURCE
#define HEADER_SOURCE
#include "tsock.h"

int launchSource(int nombreMessage,int tailleMessage,int isTCP);
int sendMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in socketStruct);
void formatText(char * actualMessage, int num, int tailleMessage, char messageChar);

#endif