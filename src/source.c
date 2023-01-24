#include "../header/source.h"

int launchSource(int nombreMessage,int tailleMessage,int isTCP,int port,char * ipAddress,int emetteur,int recepteur)
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
    if(recepteur != -1)
    {
        printf("Mode Recepteur, recois : %d\n",recepteur);
        connectTCP(sock,socketSource,sizeof(socketSource));
        modeRecepteur(recepteur,sock,&socketSource,sizeof(socketSource),port,ipAddress);
        return 0;
    }
    if(emetteur != -1)
    {
        printf("Mode Emetteur, envois : %d\n",emetteur);
        connectTCP(sock,socketSource,sizeof(socketSource));
        modeEmetteur(emetteur,nombreMessage,tailleMessage,sock,&socketSource,sizeof(socketSource));
        return 0;
    }
    if(isTCP)
    {
        connectTCP(sock,socketSource,sizeof(socketSource));
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
    char sendingMessage[tailleMessage],messageChar='a';
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
        printAndVerif(sendingMessage,tailleMessage,longueurEmis,i);
        messageChar>='z'?messageChar='a':messageChar++;
    }
    return 0;
}

void modeEmetteur(int emetteur,int nombreMessage,int tailleMessage,int sock,struct sockaddr_in * socketStruct,int tailleSocketStruct)
{
    int longueurEmis;
    char sendingMessage[tailleMessage],*paramMessage,*actualMessage,messageChar='a';
    for(int i=0;i<nombreMessage;i++)
    {
        paramMessage = formatTextParam(MODE_EMIS,emetteur,tailleMessage+1,nombreMessage);
        longueurEmis = write(sock,paramMessage,13);
        printAndVerif(paramMessage,13,longueurEmis,i);

        memset(sendingMessage, messageChar, tailleMessage);
        actualMessage = formatTextMessage(sendingMessage,tailleMessage+1);
        longueurEmis = write(sock,actualMessage,tailleMessage+1);
        printAndVerif(actualMessage,tailleMessage+1,longueurEmis,i);
        messageChar>='z'?messageChar='a':messageChar++;
    }
}

void modeRecepteur(int recepteur,int sock,struct sockaddr_in * socketStruct,int tailleSocketStruct,int port,char * ipAddress)
{
    int longueurEmis,oldSock,param,emetteurRecepteur,tailleMessage,nbMessage=2,i=0;
    char paramRecu[13];
    char *paramMessage;
    paramMessage = formatTextParam(MODE_RECEPTEUR,recepteur,0,0);
    longueurEmis = write(sock,paramMessage,13);

    close(sock);
    oldSock = initSocket(SOCK_STREAM,socketStruct,port,ipAddress);
    listen(oldSock,5);
    sock = accept(oldSock,(struct sockaddr *)&socketStruct,(socklen_t * restrict)&tailleSocketStruct);
    close(oldSock);
    while(i<nbMessage)
    {
        longueurEmis = read(sock,paramRecu,13);
        recuperationParam(paramRecu,&param,&emetteurRecepteur,&tailleMessage,&nbMessage);
        char * messageRecu = malloc(sizeof(char)*tailleMessage);
        longueurEmis = read(sock,messageRecu,tailleMessage);
        printAndVerif(messageRecu,tailleMessage,longueurEmis,i);
        i++;
    }
}