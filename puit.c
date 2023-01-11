#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>

#define _OE_SOCKETS
#define PORT_NUM    9000

void initSocket();

int sock;
char buffer[1024];
struct hostent *hp;
struct sockaddr_in socketServer;

int main(void)
{
    if((sock=socket(AF_INET,SOCK_DGRAM,0)) == -1)
    {
        printf("échec création du socket\n");
        exit(1);
    }
    memset(&socketServer, 0, sizeof(socketServer));

    initSocket();


	if (bind(sock, (const struct sockaddr *)&socketServer, sizeof(socketServer)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

    int n;
    unsigned int lg_socketServer = sizeof(socketServer);

    n = recvfrom(sock, (char *)buffer, 1024, 0, (struct sockaddr*) &socketServer,&lg_socketServer);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
    close(sock);
    return 0;
}

void initSocket()
{
    socketServer.sin_family=AF_INET;
    socketServer.sin_port=htons(PORT_NUM);
    socketServer.sin_addr.s_addr=INADDR_ANY;
}