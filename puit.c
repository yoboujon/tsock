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

void initSocketAddr(struct sockaddr_in *socketServerTemp, int source);
void creationSocket(int *socketTemp);


int sock;
char buffer[1024];
struct sockaddr_in socketClient,socketServer;

int main(void)
{
    
    creationSocket(&sock);
    initSocketAddr(&socketServer,0);


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

void initSocketAddr(struct sockaddr_in *socketTempStruct, int source)
{   
    struct hostent *hp;
    socketTempStruct->sin_family=AF_INET;
    socketTempStruct->sin_port=htons(PORT_NUM);
    if(source)
    {
        if((hp = gethostbyname("localhost")) == NULL)
        {
            printf("erreur gethostbyname\n");
            exit(1);
        }
        memcpy((char*)&(socketTempStruct->sin_addr.s_addr),hp->h_addr_list[0],hp->h_length);
    }
    else
    {
        socketTempStruct->sin_addr.s_addr=INADDR_ANY;
    }

}

void creationSocket(int *socketTemp){

if((*socketTemp=socket(AF_INET,SOCK_DGRAM,0)) == -1)
    {
        printf("échec création du socket\n");
        exit(1);
    }
    memset(&socketClient, 0, sizeof(socketClient));
    memset(&socketServer, 0, sizeof(socketServer));

}