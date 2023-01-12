#include "puit.h"

int launchPuit(void)
{
    int sock;
    char buffer[1024];
    struct sockaddr_in socketPuit;

    creationSocket(&sock,&socketPuit);
    initSocketAddr(&socketPuit,0);

	if (bind(sock, (const struct sockaddr *)&socketPuit, sizeof(socketPuit)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

    int n;
    unsigned int lg_socketPuit = sizeof(socketPuit);

    n = recvfrom(sock, (char *)buffer, 1024, 0, (struct sockaddr*) &socketPuit,&lg_socketPuit);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
    close(sock);
    return 0;
}