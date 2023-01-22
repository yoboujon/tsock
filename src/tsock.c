#include "../header/tsock.h"

int testProtocol(void)
{
    char * msg,*msg2;
    msg=formatTextParam(0,7, 8, 64, 1);
    printf("%s\n",msg);
    msg2=formatTextMessage("aaaaaa",6);
    printf("%s\n",msg2);
    //recuperationParam(msg);
    return 0;
}

void setNbMessage(int * nb, int source)
{
	if((*nb == -1) && (source))
	{
		*nb = NBMESSAGE_DEFAULT;
	}
}

void printInfo(int source, int isTCP, int nbMessage, int taille, int portNumber, char ipAddress[])
{
	if(source)
	{
		printf("tsock lance en mode source, nombre de messages à envoyer : %d\nTaille des messages : %d\nPort : %d\t Adresse IP : %s\n",nbMessage,taille,portNumber,ipAddress);
        isTCP==1 ? printf("Mode de transmission : TCP\n") : printf("Mode de transmission : UDP\n");
	}
	else
	{
		printf("tsock lance en mode puit, nombre de messages à recevoir :");
		nbMessage != -1 ? printf("%d\n", nbMessage) : printf("infini\n");
        printf("Taille des messages : %d\nPort : %d\t Adresse IP : %s\n",taille,portNumber,ipAddress);
        isTCP==1 ? printf("Mode de transmission : TCP\n") : printf("Mode de transmission : UDP\n");
	}
}

void initStructSocket(struct sockaddr_in *socketTempStruct, int source, int port, char * ipAddress)
{   
    memset(socketTempStruct, 0, sizeof(*socketTempStruct));
    socketTempStruct->sin_family=AF_INET;
    socketTempStruct->sin_port=htons(port);
    if(source)
    {   
        struct hostent *hp;
        if((hp = gethostbyname(ipAddress)) == NULL)
        {
            printf("erreur gethostbyname\n");
            exit(EXIT_FAILURE);
        }
        memcpy((char*)&(socketTempStruct->sin_addr.s_addr),hp->h_addr_list[0],hp->h_length);
    }
    else
    {
        socketTempStruct->sin_addr.s_addr=INADDR_ANY;
    }
}

void getNonOtpArgs(char ** argv, int argc, int * portNumber, char ** ipAddress)
{
    *portNumber = atoi(argv[argc-2]);
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
    if(var>tailleMax){
        printf("-l doit être <1500 \n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

char * formatTextParam(int modeParam, int numEmetteur, int numRecepteur, int tailleMessage, int nbMessage)
{
    char * actualMessage = malloc(sizeof(char)*16);
    actualMessage[0]=modeParam+0x30;
    gestionOffset(actualMessage, 4,1,numEmetteur);
    gestionOffset(actualMessage, 8,5,numRecepteur);
    gestionOffset(actualMessage, 12,9,tailleMessage);
    gestionOffset(actualMessage, 16,13,nbMessage);
    return actualMessage;
}

char * formatTextMessage(char * message, int tailleMessage)
{
    char * actualMessage = malloc(sizeof(char)*(tailleMessage+1));
    actualMessage[0]='0';
    for(int i=1,j=0;i<tailleMessage+1;i++,j++)
    {
        actualMessage[i]=message[j];
    }
    return actualMessage;
}

int gestionOffset(char *actualMessage,int encadrementHaut,int encadrementBas,int nbr)
{
    int taillechaine=0;
    char numbuffer[30];
    sprintf(numbuffer, "%d", (nbr)%10000);
    taillechaine=strlen(numbuffer);
    for(int i=encadrementBas;i<encadrementHaut-taillechaine+1;i++)
    {
        actualMessage[i]=0x20;
        
    }
    for(int i=encadrementHaut-taillechaine+1,j=0;i<encadrementHaut+1;i++,j++)
    {
        actualMessage[i]=numbuffer[j];
        
    }
    return encadrementHaut;
}

int recuperationParam(char * msgParam, int * messageOrPram, int * numEmetteurParam, int * numRecepeteurParam, int * numTailleMessageParam, int * nbMessageParam)
{   
    *messageOrPram=msgParam[0]-0x30;
    *numEmetteurParam =protocol2int(msgParam,1);
    *numRecepeteurParam=protocol2int(msgParam,MAX_MESSAGE+1);
    *numTailleMessageParam=protocol2int(msgParam,(2*MAX_MESSAGE)+1);
    *nbMessageParam=protocol2int(msgParam,(3*MAX_MESSAGE)+1);
    return 0;
}

int protocol2int(char * data, int offset)
{
    char buff[MAX_MESSAGE+1];
    for(int i=offset,j=0;i<MAX_MESSAGE+offset;i++,j++)
    {
        buff[j]=data[i];
    }
    buff[MAX_MESSAGE+1]='\0';
    return atoi(buff)%10000;
}