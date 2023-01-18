#include "../header/tsock.h"
#include "../header/puit.h"
#include "../header/source.h"
#include "../header/bal.h"

int main (int argc, char **argv)
{
	char usageChar[100]="usage: cmd [-p|-s]|[-u][-u|-r ##|-e ##|-b][-n ##][-l ##] port ipAdress\n";
	testProtocol();
	bal();
	char *ipAddress;
	extern char *optarg;
	extern int optind;
	int source = -1, nb_message = -1, c, tcp=1, port=-1, tailleMessage=30, emetteur=-1, recepteur=-1, isBAL=0;
	while ((c = getopt(argc, argv, "pn:sul:e:r:b")) != -1) {
		switch (c) {
		case 'p':
			if (source != -1) {
				printf("%s",usageChar);
				exit(EXIT_FAILURE);
			}
			source = 0;
			break;
		case 's':
			if (source != -1) {
				printf("%s",usageChar);
				exit(EXIT_FAILURE);
			}
			source = 1;
			break;
		case 'l':
			tailleMessage =atoi(optarg);
			exitMax(tailleMessage,1500);
			break;
		case 'n':
			nb_message = atoi(optarg);
			break;
		case 'u':
			tcp=0;
			break;
		case 'e':
			if(recepteur !=-1 || tcp !=1 || isBAL!=0 || source != -1)
			{
				printf("%s",usageChar);
				exit(EXIT_FAILURE);
			}
			source = 1;
			emetteur = atoi(optarg);
			break;
		case 'r':
			if(emetteur!=-1 || tcp !=1 || isBAL!=0 || source != -1)
			{
				printf("%s",usageChar);
				exit(EXIT_FAILURE);
			}
			source = 1;
			recepteur = atoi(optarg);
			break;
		case 'b':
			if(emetteur!=-1 || recepteur !=-1 || tcp !=1)
			{
				printf("%s",usageChar);
				exit(EXIT_FAILURE);
			}
			source = 0;
			isBAL=1;
			break;
		default:
			printf("%s",usageChar);
			exit(EXIT_FAILURE);
			break;
		}
	}
	if (source == -1) {
		printf("-p|-s non present !\n");
		printf("%s",usageChar);
		exit(EXIT_FAILURE);
	}
	if(argc != optind+2)
	{
		printf("ip ou port non present !\n");
		printf("%s",usageChar);
		exit(EXIT_FAILURE);
	}

	if(tailleMessage == -1)
	{
		tailleMessage = 30;
	}
	getNonOtpArgs(argv, argc, &port, &ipAddress);
	setNbMessage(&nb_message,source);
	printInfo(source,tcp,nb_message,tailleMessage,port,ipAddress);

	if(source)
	{
		//printf("Source : %d\n",nb_message);
		launchSource(nb_message,tailleMessage,tcp,port,ipAddress);
	}
	else
	{
		//printf("Puit : %d\n",nb_message);
		launchPuit(nb_message,tailleMessage,tcp,port,ipAddress,isBAL);
	}
	return(EXIT_SUCCESS);
}