#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "Server.h"

int main(int argc, char *argv[]){
    int err;
    int cSocket;
    //struct sockaddr_in sAddr;
    struct sockaddr_in cAddr;
    //int cSocLen;
    char buf1[BUFLEN], buf2[2];
    //char input[BUFLEN];

    cAddr.sin_family = AF_INET;
    cAddr.sin_port = htons (SERVERPORT);
    cAddr.sin_addr.s_addr = inet_addr(SERVERIP);

    //Create socket
    cSocket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (cSocket == -1) {
        perror ("socClient: socket creation failed");
        exit (1);
    }

    //Create connection to ServerC
    err = connect (cSocket, (struct sockaddr *) &cAddr, sizeof(struct sockaddr_in));
    if (err == -1) {
        perror ("socClient: connect failed");
        exit (2);
    }
    // Send message to server.
    err = send(cSocket, "Connection made!\n", BUFLEN, 0);
    printf("socClient: number of bytes sent to server: %d\n", err);


    //At this point, connection has been made to the server, and we start playing the game
    int i;
    for (;;) {                                          //infinite loop
        err = recv(cSocket, buf1, BUFLEN, 0);            //Wait for a response from server
        if (buf1[0] == '+') {            //Test for winner/loser
            printf("You have won!\n");
            break;
        } else if (buf1[0] == '-') {
            printf("You have lost\n");
            break;
        } else {
            printf("%s\n", buf1);                          //Print out server response
            
            memset(buf1, 0, sizeof(buf1));                  //Reset buffer
            memset(buf2, 0, sizeof(buf2));

            printf("\nEnter r (rock), p (paper), or s (scissors): ");
            do {
                scanf("%c", buf2);                                 //Wait for client response
            } while (buf2[0] != 'r' && buf2[0] != 'p' && buf2[0] != 's');   //error checking
            send(cSocket, buf2, sizeof(buf2), 0);
        }
    }


    close(cSocket);                                     //Close connection
    return 0;
}
