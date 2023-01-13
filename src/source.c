#include "../header/source.h"

int launchSource(int nombreMessage, int isTCP)
{
    int sock;
    struct sockaddr_in socketSource;

    if((sock=socket(AF_INET,SOCK_DGRAM,0)) == -1)
    {
        perror("[tsock] : fonction socket() : echec creation du socket\n");
        exit(EXIT_FAILURE);
    }
    initStructSocket(&socketSource,1);
    sendMultipleData(nombreMessage,30,sock,socketSource);
    close(sock);
    return 0;
}

int sendMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in socketStruct)
{
    int longueurEmis;
    char messageChar='a';
    char sendingMessage[tailleMessage];
    for(int i=0;i<nombreMessages;i++)
    {
        memset(sendingMessage, messageChar, tailleMessage*sizeof(char));
        longueurEmis=sendto(sock, sendingMessage, tailleMessage, 0, (struct sockaddr*)&socketStruct, sizeof(socketStruct));
        printf("Source\tEnvoi n°%d (%d) :\t[%s]\n",i+1,longueurEmis,sendingMessage);
        messageChar++;
    }
    return 0;
}