#include "../header/tsock.h"
#include "../header/puit.h"
#include "../header/source.h"

int main (int argc, char **argv)
{
	char usageChar[30]="usage: cmd [-p|-s][-n ##]\n";
	char *ipAddress;
	extern char *optarg;
	extern int optind;
	int source = -1, nb_message = -1, c, tcp=1, port=9000; /* Nb de messages à envoyer ou à recevoir, par défaut : 10 en émission, infini en réception */
	while ((c = getopt(argc, argv, "pn:su")) != -1) {
		switch (c) {
		case 'p':
			if (source != -1) {
				printf(usageChar);
				exit(1);
			}
			source = 0;
			break;
		case 's':
			if (source != -1) {
				printf(usageChar);
				exit(1) ;
			}
			source = 1;
			break;
		case 'n':
			nb_message = atoi(optarg);
			break;
		case 'u':
			tcp=0;
			break;
		default:
			printf(usageChar);
			break;
		}
	}
	if (source == -1) {
		printf("-p|-s non present !\n");
		printf(usageChar);
		exit(1);
	}

	getNonOtpArgs(argv, argc, port, &ipAddress);
	setNbMessage(&nb_message,source);
	printInfo(nb_message,source,port,ipAddress);

	if(source)
	{
		//printf("Source : %d\n",nb_message);
		launchSource(nb_message,tcp);
	}
	else
	{
		//printf("Puit : %d\n",nb_message);
		launchPuit(nb_message,tcp);
	}
}