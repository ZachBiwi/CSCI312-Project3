#include "Server.h"

int main(int argc, char *argv[]) {
    int  cSocket[2];                    //Socket descriptors of two clients
    cSocket[0] = atoi(argv[1]);         //Place client socket descriptors onto int array
    cSocket[1] = atoi(argv[2]);
    char buf1[BUFLEN], buf2[BUFLEN], buf3[BUFLEN];    //Strings for client input
    int numberOfWins[] {0, 0};
    bool done = false;
    int n, m, i;                           //Best n out of m
    int choicesN[] = {2, 3, 4, 5};
    int choicesM[] = {3, 5, 7, 9};
    srand(time());
    i = choices[rand() % 3];            //Choose randomly for number of games to play
    n = choicesN[i];
    m = choicesM[i];
    sprintf(buf3, "There will be %c games of rock, paper, scissor played\n
    Please enter r, p, or s to play\n", m); //Send number of games to be played to clients, as well as instructions
    err = send(cSocket[0], buf3, strlen(buf3) + 1, 0);
    if (err = -1) {
        printf("Error on message sent to client 1");
        exit(1);
    }
    err = send(cSocket[1], buf3, strlen(buf3) + 1, 0);
    if (err = -1) {
        printf("Error on message sent to client 2");
        exit(2);
    }
    for (i = 0; i < m; i++) {
        err = recv(cSocket[0], buf1, BUFLEN, 0);        //Rece
        if (err = -1) {
        printf("Error on message received from client 1");
        exit(3);
        }
        err = recv(cSocket[1], buf2, BUFLEN, 0);
        if (err = -1) {
        printf("Error on message recieved from client 2");
        exit(4);
        }
        if (Buf)
    }
    
}