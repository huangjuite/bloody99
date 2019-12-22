#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sockop.h"

#define BUFSIZE	1024

int main(int argc, char *argv[])
{
	int connfd;	/* socket descriptor */
	int n,x;
	char bufw[BUFSIZE], bufr[BUFSIZE];
	connfd = connectsock(argv[1], argv[2], "tcp");
	while(1) {
        memset(bufr, 0, BUFSIZE);
		if ((n = read(connfd, bufr, BUFSIZE)) == -1)
			errexit("Error: read()\n");
		printf("Server Reply: %s\n", bufr);
		/* write message to server */
        scanf("%d", &x);
        sprintf(bufw, "%d", x);
		if ((n = write(connfd, bufw, strlen(bufw))) == -1)
			errexit("Error: write()\n");
		/* read message from the server and print */
		sleep(1);
	}
	/* close client socket */
	close(connfd);

	return 0;
}
