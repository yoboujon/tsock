#include "../header/source.h"

int launchSource(int nombreMessage,int tailleMessage,int isTCP)
{
    int sock,socketType;
    struct sockaddr_in socketSource;
    if(isTCP)
    {
        socketType=SOCK_STREAM;
    }
    else
    {
        socketType=SOCK_DGRAM;
    }

    if((sock=socket(AF_INET,socketType,0)) == -1)
    {
        perror("[tsock] : fonction socket() : echec creation du socket\n");
        exit(EXIT_FAILURE);
    }
    initStructSocket(&socketSource,1);
    if(isTCP)
    {
        connect(sock,(struct sockaddr *)&socketSource,(socklen_t)sizeof(socketSource));
        printf("Connect successful\n");
        int isWritten = write(sock,"aaaaaa",sizeof("aaaaaa"));
        printf("on écrit : %d\n",isWritten);
    }
    else
    {
        sendMultipleData(nombreMessage,tailleMessage,sock,socketSource);
    }
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
        memset(sendingMessage, messageChar, tailleMessage*sizeof(char)+1);
        longueurEmis=sendto(sock, sendingMessage, tailleMessage, 0, (struct sockaddr*)&socketStruct, sizeof(socketStruct));
        sendingMessage[tailleMessage]='\0';
        printf("Source\tEnvoi n°%d (%d) :\t[%s]\n",i+1,longueurEmis,sendingMessage);
        messageChar++;
    }
    return 0;
}