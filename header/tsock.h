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

void setNbMessage(int * nb, int source);
void printInfo(int nb, int source, int portNumber, char ipAddress[]);
void initStructSocket(struct sockaddr_in *socketServerTemp, int source);
void getNonOtpArgs(char ** argv, int argc, int portNumber, char * ipAddress[]);
void formatText(char * actualMessage, int num, int tailleMessage, char messageChar);
int exitMax(int var,int tailleMax);

#define PORT_NUM    9000

#endif