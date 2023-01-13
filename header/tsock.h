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
void initStructSocket(struct sockaddr_in *socketServerTemp, int source);

#define PORT_NUM    9000

#endif