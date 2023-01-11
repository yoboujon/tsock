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
struct sockaddr_in socketClient;

int main(void)
{
    if((sock=socket(AF_INET,SOCK_DGRAM,0)) == -1)
    {
        printf("échec création du socket\n");
        exit(1);
    }
    memset(&socketClient, 0, sizeof(socketClient));
    initSocket();
    lg_emis=sendto(sock, "aaaaa", 6, 0, (struct sockaddr*)&socketClient, sizeof(socketClient));
    printf("lgemis = %d\n",lg_emis);
    close(sock);
    return 0;
}

void initSocket()
{
    socketClient.sin_family=AF_INET;
    socketClient.sin_port=htons(PORT_NUM);
    if((hp = gethostbyname("localhost")) == NULL)
    {
        printf("erreur gethostbyname\n");
        exit(1);
    }
    memcpy((char*)&(socketClient.sin_addr.s_addr),hp->h_addr_list[0],hp->h_length);
}