#include "../header/tsock.h"

void setNbMessage(int * nb, int source)
{
	if((*nb == -1) && (source))
	{
		*nb = 10;
	}
}

void printInfo(int nb, int source, int portNumber, char ipAddress[])
{
	if(source)
	{
		printf("tsock lance en mode source, nombre de tampons à envoyer : %d\nPort : %d\t Adresse IP : %s\n", nb, portNumber, ipAddress);
	}
	else
	{
		printf("tsock lance en mode puit, nombre de tampons à recevoir :");
		nb != -1 ? printf("%d\n", nb) : printf("infini\n");
        printf("Port : %d\n",portNumber);
	}
}

void initStructSocket(struct sockaddr_in *socketTempStruct, int source)
{   
    memset(socketTempStruct, 0, sizeof(*socketTempStruct));
    socketTempStruct->sin_family=AF_INET;
    socketTempStruct->sin_port=htons(PORT_NUM);
    if(source)
    {   
        struct hostent *hp;
        if((hp = gethostbyname("localhost")) == NULL)
        {
            printf("erreur gethostbyname\n");
            exit(1);
        }
        memcpy((char*)&(socketTempStruct->sin_addr.s_addr),hp->h_addr_list[0],hp->h_length);
    }
    else
    {
        socketTempStruct->sin_addr.s_addr=INADDR_ANY;
    }
}

void getNonOtpArgs(char ** argv, int argc, int portNumber, char ** ipAddress)
{
    portNumber = atoi(argv[argc-2]);
    *ipAddress = NULL;
    *ipAddress = (char *)malloc(sizeof(argv[argc-1]));
    strcpy(*ipAddress,argv[argc-1]);
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

int exitMax(int var,int tailleMax){
    if(var>1500){
        printf("-l doit être <1500 \n");
        exit(EXIT_FAILURE);
    }
    return 0;
}