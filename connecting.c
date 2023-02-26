#include "server.h"

int main() {
    int err;
    int cSocket;
    struct sockaddr_in cAddr;
    char buf[BUFLEN];

    memset(&cAddr, 0, sizeof (struct sockaddr_in));
    cAddr.sin_family = AF_INET;
    cAddr.sin_port = htons (SERVERPORT);
    cAddr.sin_addr.s_addr = inet_addr(SERVERIP);

    //Create socket
    cSocket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (cSocket == -1) {
        perror ("socClient: socket creation failed");
        exit (1);
    }

    //Create connection to Server
    err = connect (cSocket, (struct sockaddr *) &cAddr, sizeof(struct sockaddr_in));
    if (err == -1) {
        perror ("socClient: connect failed");
        exit (2);
    }
    printf()

    recv(cSocket, buf, sizeof(buf), 0);
    scanf(buf);
    send(cSocket, buf, sizeof(buf), 0);
    printf("Exiting!")

}