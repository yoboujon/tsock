#include "../header/puit.h"

int launchPuit(int nombreMessage,int tailleMessage,int isTCP,int port,char * ipAddress,int isBAL)
{
    int sock,socketType;
    struct sockaddr_in socketPuit;
    socketType = (isTCP) ? SOCK_STREAM : SOCK_DGRAM;
    if(isBAL)
    {
        printf("Mode Boîte aux Lettres\n");
        modeBoiteAuxLettres(socketPuit,socketType,port,ipAddress);
        return 0;
    }
    sock = initSocket(socketType,&socketPuit,port,ipAddress);
    receiveMultipleData(nombreMessage,tailleMessage,sock,socketPuit,isTCP);
    close(sock);
    return 0;
}

int initSocket(int socketType, struct sockaddr_in * socketStruct, int port, char * ipAddress)
{
    int sockReturn;
    if((sockReturn=socket(AF_INET,socketType,0)) == -1)
    {
        perror("[tsock] : fonction socket() : echec creation du socket\n");
        exit(EXIT_FAILURE);
    }
    initStructSocket(socketStruct,0,port,ipAddress);
	if (bind(sockReturn, (struct sockaddr *)socketStruct, sizeof(*socketStruct)) < 0 )
	{
		perror("[tsock] : fonction bind() : echec du lien avec socket serveur.\n");
		exit(EXIT_FAILURE);
	}
    return sockReturn;
}

int modeBoiteAuxLettres(struct sockaddr_in socketStruct, int socketType, int port, char * ipAddress)
{
    char messageRecu[30+1];
    int n, i=1, longueurRecu = sizeof(socketStruct),sock,oldSock;
    while(1)
    {
        n=1;
        oldSock = initSocket(socketType,&socketStruct,port,ipAddress);
        listen(oldSock,5);
        sock = accept(oldSock,(struct sockaddr *)&socketStruct,(socklen_t * restrict)&longueurRecu);
        while(n>0)
        {
            n = read(sock,messageRecu,30);
            messageRecu[n] = '\0';
            if(n>0)
            {
                printf("Puit\tReception n°%d (%d) :\t[%s]\n",i,n,messageRecu);
                i++;
            }
        }
        close(sock);
        close(oldSock);
    }
}

int receiveMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in socketStruct, int isTCP)
{
    char messageRecu[tailleMessage+1];
    int n=1, longueurRecu = sizeof(socketStruct);
    if(isTCP)
    {
        listen(sock,5);
        sock = accept(sock,(struct sockaddr *)&socketStruct,(socklen_t * restrict)&longueurRecu);
    }
    if(nombreMessages < 0)
    {
        int i=1;
        while(n>0)
        {
            if(isTCP)
            {
                n = read(sock,messageRecu,tailleMessage);
            }
            else
            {
                n = recvfrom(sock, (char *)messageRecu, tailleMessage, 0, (struct sockaddr*) &socketStruct,(socklen_t *__restrict__)&longueurRecu);
            }
            messageRecu[n] = '\0';
            printf("Puit\tReception n°%d (%d) :\t[%s]\n",i,n,messageRecu);
            i++;
        }
    }
    else{
        for(int i=0;i<nombreMessages;i++)
        {
            if(isTCP)
            {
                n = read(sock,messageRecu,tailleMessage);
            }
            else
            {
                n = recvfrom(sock, (char *)messageRecu, tailleMessage, 0, (struct sockaddr*) &socketStruct,(socklen_t *__restrict__)&longueurRecu);
            }
            messageRecu[n] = '\0';
            printf("Puit\tReception n°%d (%d) :\t[%s]\n",i+1,tailleMessage,messageRecu);
        }
    }
    return 0;
}