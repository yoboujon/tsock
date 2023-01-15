#include "../header/source.h"

int launchSource(int nombreMessage,int tailleMessage,int isTCP,int port,char * ipAddress)
{
    struct sockaddr_in socketSource;
    int sock,socketType;
    socketType = (isTCP) ? SOCK_STREAM : SOCK_DGRAM;

    if((sock=socket(AF_INET,socketType,0)) == -1)
    {
        perror("[tsock] : fonction socket() : echec creation du socket\n");
        exit(EXIT_FAILURE);
    }
    initStructSocket(&socketSource,1,port,ipAddress);
    if(isTCP)
    {
        int connectStatus;
        if((connectStatus = connect(sock,(struct sockaddr *)&socketSource,(socklen_t)sizeof(socketSource))) == -1)
        {
            perror("[tsock] : fonction connect() : echec connexion\n");
            exit(EXIT_FAILURE);
        };
        sendMultipleData(nombreMessage,tailleMessage,sock,&socketSource,sizeof(socketSource),isTCP);
    }
    else
    {
        sendMultipleData(nombreMessage,tailleMessage,sock,&socketSource,sizeof(socketSource),isTCP);
    }
    close(sock);
    return 0;
}

int sendMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in * socketStruct, int sizeSocketStruct, int isTCP)
{
    int longueurEmis;
    char messageChar='a';
    char sendingMessage[tailleMessage];
    for(int i=0;i<nombreMessages;i++)
    {
        formatText(sendingMessage,i,tailleMessage,messageChar);
        if(isTCP)
        {
            longueurEmis = write(sock,sendingMessage,tailleMessage);
        }
        else
        {
            longueurEmis = sendto(sock,sendingMessage,tailleMessage,0,(struct sockaddr*)socketStruct, sizeSocketStruct);
        }

        if(longueurEmis == -1)
        {
            perror("[tsock] : fonction sendto()/write() : echec d'envoi\n");
            exit(EXIT_FAILURE);
        }
        sendingMessage[tailleMessage]='\0';
        printf("Source\tEnvoi n°%d (%d) :\t[%s]\n",i+1,longueurEmis,sendingMessage);
        messageChar>='z'?messageChar='a':messageChar++;
    }
    return 0;
}