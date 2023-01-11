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