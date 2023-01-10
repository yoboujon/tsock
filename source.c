#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>

#define PORT_NUM    9000

void initSocket();

int sock;
int lg_emis;
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
    lg_emis=sendto(sock, "aaaaa", 6, 0, (struct sockaddr*)&socketServer, sizeof(socketServer));
    printf("lgemis = %d\n",lg_emis);
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