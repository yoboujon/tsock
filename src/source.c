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
        formatText(sendingMessage,i,tailleMessage,messageChar);
        longueurEmis=sendto(sock, sendingMessage, tailleMessage, 0, (struct sockaddr*)&socketStruct, sizeof(socketStruct));
        sendingMessage[tailleMessage]='\0';
        printf("Source\tEnvoi n°%d (%d) :\t[%s]\n",i+1,longueurEmis,sendingMessage);
        messageChar>='z'?messageChar='a':messageChar++;
    }
    return 0;
}

void formatText(char * actualMessage, int num, int tailleMessage, char messageChar)
{
    char numBuffer[15];
    sprintf(numBuffer, "%d", (num+1)%10000);
    int numberLength=0;
    while(numBuffer[numberLength] != '\0')
    {
        numberLength++;
    }
    for(int i=0;i<4-numberLength;i++)
    {
        actualMessage[i]=0x20;
    }
    for(int i=4-numberLength,j=0;i<4;i++,j++)
    {
        actualMessage[i]=numBuffer[j];
    }
    memset(actualMessage+4, messageChar, tailleMessage);
}