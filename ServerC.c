#include "Server.h"

int main(int argc, char *argv[]) {
    int err, sSocket, cSocket[2], cSocLen, connections = 0;
    bool done = false;
    struct sockaddr_in sAddr;
    struct sockaddr_in cAddr;
    char buf1[BUFLEN], buf2[BUFLEN];
    sAddr.sin_family = AF_INET;
    sAddr.sin_port = htons (SERVERPORT);
    sAddr.sin_addr.s_addr = htonl (INADDR_ANY);

    sSocket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sSocket == -1) {
        perror ("socServer: socket creation failed");
        exit (1);
    }

    err = bind(sSocket, (struct sockaddr*)&sAddr,sizeof (struct sockaddr_in));
    if (err == -1) {
        perror ("socServer: bind address to socket failed");
        exit (2);
    }
    while (connections != 2) {
        err = listen (sSocket, 2);                                  //Wait for two client socket connections
        if (err == -1) {
            perror ("socServer: listen failed");
            exit (3);
        }

        cSocLen = sizeof(sAddr);
        cSocket[connections] = accept(sSocket, (struct sockaddr *)&cAddr, (socklen_t*) &cSocLen);
        if (cSocket[connections++] == -1) {
            perror ("socServer: accept failed");
            exit (4);
        }
    }

    // Read from client socket.
    err = recv (cSocket[0], buf1, BUFLEN, 0);             //Client1
    if (err == -1) {
        perror ("socServer: read failed");
        exit (5);
    }
    err = recv (cSocket[1], buf2, BUFLEN, 0);             //Client2
    if (err == -1) {
        perror ("socServer: read failed");
        exit (5);
    }
    printf ("socServer: msg from client1: %s\n", buf1);
    printf ("socServer: msg from client2: %s\n", buf2);
    err = fork();
    if (err == -1) { //error
        printf("Error on fork\n");
        exit(6);
    }
    if (err == 0) { //Child process
        printf("In child process!\n");
        char sockBuff1[20];
        char sockBuff2[20];
        sprintf(sockBuff1, "%d", cSocket[0]);
        sprintf(sockBuff2, "%d", cSocket[1]);
        printf("Executing the rps game\n");
        execl("./ServerG", "ServerG" , sockBuff1, sockBuff2, NULL);      //Exec ServerG, the rockpaperscissors game
    }                                                                            //With both client's socket descriptors
    else /*Parent process*/ {
        //while{}
        //printf("In parent process!");
        //while
    }
    
    exit (0);
}