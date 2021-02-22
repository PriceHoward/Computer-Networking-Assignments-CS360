

#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include<time.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERVER_PORT  3348
#define MAX_PENDING  5
#define MAX_LINE     256

int
main(void)
{
    struct sockaddr_in sin, cli;
    char buf[MAX_LINE];
    socklen_t addr_len;
    int buf_len;
    int s;
    int new_s;
    time_t rawTime;

    /* build address data structure */
    memset(&sin, '\0', sizeof sin);
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    /* setup passive open */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err(EXIT_FAILURE, "Daytime Server: socket");
    }

    if ((bind(s, (struct sockaddr *)&sin, sizeof(sin) )) < 0) {
        warn("Daytime Server: bind");
       // goto done;
    }

    listen(s, MAX_PENDING);

     /* wait for connection (blocking), then receive and print text */
    while(1) {
      addr_len = sizeof(cli);
      new_s = accept(s, (struct sockaddr *)&cli, &addr_len);	
      time(&rawTime);
      sprintf(buf,"%s", ctime(&rawTime));
      send(new_s, buf, strlen(buf), 0);
      close(new_s);
    }
}
