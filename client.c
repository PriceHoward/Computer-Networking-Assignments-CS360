/*
 * Price Howard
 * 2/20/21
 * Client of the Daytime client/server.
 * CS 360
 */
#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERVER_PORT 3348
#define MAX_LINE 256

int
main(int argc, char *argv[])
{
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    char *host;
    struct hostent *hp;
    int s;
    size_t len;

    /* "get" host's name from command line */
    if (argc == 2) {
        host = argv[1];
    } else {
        err(EXIT_FAILURE, "usage: Daytime Client host\n");
    }

    /* translate host name into peer's IP address */
    hp = gethostbyname(host);
    if (hp == NULL) {
        err(EXIT_FAILURE, "Daytime Client: unknown host: %s\n", host);
    }

    /* build address data structure */
    memset(&sin, '\0', sizeof sin);
    sin.sin_family = AF_INET;
    memcpy((char *)&sin.sin_addr, hp->h_addr, hp->h_length);
    sin.sin_port = htons(SERVER_PORT);


    /* Opening of the socket*/
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err(EXIT_FAILURE, "Daytime Client: socket");
    }
    //Connecting the client to the server
    if (connect(s, (struct sockaddr *)&sin, sizeof sin) < 0) {
        warn("Daytime Client: connect");
    }


       int n =  recv(s, buf, MAX_LINE, 0);// Recieving one line of data from server
       
	
	printf("%.*s",n,  buf);// Printing using the %.*s which formats the buffer to a certain length of bytes taken from the recieve.
	close(s);

}
