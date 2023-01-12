#ifndef HEADER_TSOCK
#define HEADER_TSOCK

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>

void setNbMessage(int * nb, int source);
void printInfo(int nb, int source);
void initSocketAddr(struct sockaddr_in *socketServerTemp, int source);
void creationSocket(int *socketTemp, struct sockaddr_in *socketTempStruct);

#define _OE_SOCKETS
#define PORT_NUM    9000

#endif