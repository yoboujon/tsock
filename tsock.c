#include "tsock.h"

void setNbMessage(int * nb, int source)
{
	if((*nb == -1) && (source))
	{
		*nb = 10;
	}
}

void printInfo(int nb, int source)
{
	if(source)
	{
		printf("tsock lance en mode source, nombre de tampons à envoyer : %d\n", nb);
	}
	else
	{
		printf("tsock lance en mode puit, nombre de tampons à recevoir :");
		nb != -1 ? printf("%d\n", nb) : printf("infini\n");
	}
}

void initSocketAddr(struct sockaddr_in *socketTempStruct, int source)
{   
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

void creationSocket(int *socketTemp, struct sockaddr_in *socketTempStruct)
{
    if((*socketTemp=socket(AF_INET,SOCK_DGRAM,0)) == -1)
    {
        printf("échec création du socket\n");
        exit(1);
    }
    memset(socketTempStruct, 0, sizeof(*socketTempStruct));
}