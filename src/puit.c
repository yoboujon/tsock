#include "../header/puit.h"

int launchPuit(int nombreMessage,int tailleMessage)
{
    int sock;
    struct sockaddr_in socketPuit;

    if((sock=socket(AF_INET,SOCK_DGRAM,0)) == -1)
    {
        perror("[tsock] : fonction socket() : echec creation du socket\n");
        exit(EXIT_FAILURE);
    }
    initStructSocket(&socketPuit,0);
	if (bind(sock, (const struct sockaddr *)&socketPuit, sizeof(socketPuit)) < 0 )
	{
		perror("[tsock] : fonction bind() : echec du lien avec socket serveur.\n");
		exit(EXIT_FAILURE);
	}
    receiveMultipleData(nombreMessage,tailleMessage,sock,socketPuit);
    close(sock);
    return 0;
}

int receiveMultipleData(int nombreMessages, int tailleMessage, int sock, struct sockaddr_in socketStruct)
{
    char messageRecu[tailleMessage+1];
    int n, longueurRecu = sizeof(socketStruct);
    if(nombreMessages < 0)
    {
        int i=1;
        while(1)
        {
            n = recvfrom(sock, (char *)messageRecu, tailleMessage, 0, (struct sockaddr*) &socketStruct,(socklen_t *__restrict__)&longueurRecu);
            messageRecu[n] = '\0';
            printf("Puit\tReception n°%d (%d) :\t[%s]\n",i,tailleMessage,messageRecu);
            i++;
        }
    }
    else{
        for(int i=0;i<nombreMessages;i++)
        {
            n = recvfrom(sock, (char *)messageRecu, tailleMessage, 0, (struct sockaddr*) &socketStruct,(socklen_t *__restrict__)&longueurRecu);
            messageRecu[n] = '\0';
            printf("Puit\tReception n°%d (%d) :\t[%s]\n",i+1,tailleMessage,messageRecu);
        }
    }
    return 0;
}

int exitMax(int var,int tailleMax){
    if(var>1500){
        printf("-l doit être <1500 \n");
        exit(EXIT_FAILURE);
    }
    return 0;
} 