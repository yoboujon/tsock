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
struct sockaddr_in socketClient,socketServer;

int main(void)
{
    if((sock=socket(AF_INET,SOCK_DGRAM,0)) == -1)
    {
        printf("échec création du socket\n");
        exit(1);
    }
    memset(&socketClient, 0, sizeof(socketClient));
    memset(&socketServer, 0, sizeof(socketServer));

    initSocket();


	if (bind(sock, (const struct sockaddr *)&socketServer, sizeof(socketServer)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

    int n;
    unsigned int lg_socketClient = sizeof(socketClient);

    n = recvfrom(sock, (char *)buffer, 1024, 0, (struct sockaddr*) &socketClient,&lg_socketClient);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
    close(sock);
    return 0;
}

void initSocket()
{
    socketServer.sin_family=AF_INET;
    socketServer.sin_port=htons(PORT_NUM);
    if((hp = gethostbyname("localhost")) == NULL)
    {
        printf("erreur gethostbyname\n");
        exit(1);
    }
    memcpy((char*)&(socketServer.sin_addr.s_addr),hp->h_addr_list[0],hp->h_length);
}