#include "../header/source.h"

int launchSource(int nombreMessage,int tailleMessage,int isTCP)
{
    int sock,socketType;
    struct sockaddr_in socketSource;
    socketType = (isTCP) ? SOCK_STREAM : SOCK_DGRAM;

    if((sock=socket(AF_INET,socketType,0)) == -1)
    {
        perror("[tsock] : fonction socket() : echec creation du socket\n");
        exit(EXIT_FAILURE);
    }
    initStructSocket(&socketSource,1);
    if(isTCP)
    {
        connect(sock,(struct sockaddr *)&socketSource,(socklen_t)sizeof(socketSource));
        sendMultipleData(nombreMessage,tailleMessage,sock,socketSource,isTCP);
    }
    else
    {
        sendMultipleData(nombreMessage,tailleMessage,sock,socketSource,isTCP);
    }
    close(sock);
    return 0;
}

int sendMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in socketStruct, int isTCP)
{
    int longueurEmis;
    char messageChar='a';
    char sendingMessage[tailleMessage];
    for(int i=0;i<nombreMessages;i++)
    {
        formatText(sendingMessage,i,tailleMessage,messageChar);
        if(isTCP)
        {
            longueurEmis = write(sock,sendingMessage,sizeof(sendingMessage));
        }
        else
        {
            longueurEmis = sendto(sock, sendingMessage, tailleMessage, 0, (struct sockaddr*)&socketStruct, sizeof(socketStruct));
        }
        sendingMessage[tailleMessage]='\0';
        printf("Source\tEnvoi n°%d (%d) :\t[%s]\n",i+1,longueurEmis,sendingMessage);
        messageChar>='z'?messageChar='a':messageChar++;
    }
    return 0;
}