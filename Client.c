#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "Server.h"

int main(int argc, char *argv[]){
    int err;
    int cSocket;
    bool done = false;
    struct sockaddr_in sAddr;
    struct sockaddr_in cAddr;
    int cSocLen;
    char buf[BUFLEN];
    char input[BUFLEN];

    memset (&cAddr, 0, sizeof (struct sockaddr_in));
    cAddr.sin_family = AF_INET;
    cAddr.sin_port = htons (SERVERPORT);
    cAddr.sin_addr.s_addr = inet_addr(SERVERIP);

    //Create socket
    cSocket = socket (AF_INET, SOCK_STREAM, 0);
    if (cSocket == -1) {
        perror ("socClient: socket creation failed");
        exit (1);
    }

    //Create connection to ServerC
    err = connect (cSocket, (struct sockaddr *)&cAddr,sizeof(struct sockaddr_in));
    if (err == -1) {
        perror ("socClient: connect failed");
        exit (2);
    }
    // Send message to server.
    err = send (cSocket, "Connection made!\n", 17, 0);
    printf ("socClient: number of bytes sent to server: %d\n", err);
    exit (0);

    while (!done) {
        err = recv(cSocket, buf, BUFLEN, 0);        //Wait for a response from server
        printf("%s", buf);                          //Print out server response
        scanf(input);                               //Wait for client response
    }



    return 0;
}
