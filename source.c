#include "source.h"

int launchSource(void)
{
    int sock;
    int lg_emis;
    struct hostent *hp;
    struct sockaddr_in socketSource;
    if((sock=socket(AF_INET,SOCK_DGRAM,0)) == -1)
    {
        printf("échec création du socket\n");
        exit(1);
    }
    memset(&socketSource, 0, sizeof(socketSource));
    initSocketAddr(&socketSource,1);
    lg_emis=sendto(sock, "aaaaa", 6, 0, (struct sockaddr*)&socketSource, sizeof(socketSource));
    printf("lgemis = %d\n",lg_emis);
    close(sock);
    return 0;
}