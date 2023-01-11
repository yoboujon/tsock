#include "tsock.h"

int main (int argc, char **argv)
{
	int c;
	extern char *optarg;
	extern int optind;
	int nb_message = -1; /* Nb de messages à envoyer ou à recevoir, par défaut : 10 en émission, infini en réception */
	int source = -1 ; /* 0=puits, 1=source */
	while ((c = getopt(argc, argv, "pn:s")) != -1) {
		switch (c) {
		case 'p':
			if (source != -1) {
				printf("usage: cmd [-p|-s][-n ##]\n");
				exit(1);
			}
			source = 0;
			break;
		case 's':
			if (source != -1) {
				printf("usage: cmd [-p|-s][-n ##]\n");
				exit(1) ;
			}
			source = 1;
			break;
		case 'n':
			nb_message = atoi(optarg);
			break;
		default:
			printf("usage: cmd [-p|-s][-n ##]\n");
			break;
		}
	}

	if (source == -1) {
		printf("usage: cmd [-p|-s][-n ##]\n");
		exit(1);
	}

	setNbMessage(&nb_message,source);
	printInfo(nb_message,source);

	if(source)
	{
		printf("Source : %d\n",nb_message);
	}
	else
	{
		printf("Puit : %d\n",nb_message);
	}
}