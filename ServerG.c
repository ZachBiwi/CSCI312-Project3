#include "Server.h"

int rps(char x, char y); //returns 0 for tie, 1 for x win, 2 for y win

int main(int argc, char *argv[]) {
    int  cSocket[2], err = 0;           //Socket descriptors of two clients
    int result = 0;
    cSocket[0] = atoi(argv[1]);         //Place client socket descriptors onto int array
    cSocket[1] = atoi(argv[2]);
    char buf1[2], buf2[2], buf3[BUFLEN];    //Strings for client input
    int numberOfWins[] = {0, 0};
    bool done = false;
    int n, m, i;                           //Best n out of m
    int choicesN[] = {2, 3, 4, 5};
    int choicesM[] = {3, 5, 7, 9};
    srand(time(0));
    i = rand() % 3;            //Choose randomly for number of games to play
    n = choicesN[i];
    m = choicesM[i];


    sprintf(buf3, "This game of rock, paper, scissors will be best %d out of %d\n", n, m);
    err = send(cSocket[0], buf3, BUFLEN, 0);
    err = send(cSocket[1], buf3, BUFLEN, 0);

    for (i = 0; ; i++) {                              //Infinite loop until winner
        memset(buf1, 0, 2);                     //reset three buffers
        memset(buf2, 0, 2);  
        memset(buf3, 0, BUFLEN);
          
        err = recv(cSocket[0], buf1, 2, 0);        //Recv
        err = recv(cSocket[1], buf2, 2, 0);
        result = rps(buf1[0], buf2[0]);

        if (result == 1) {
            numberOfWins[0]++;
            if (numberOfWins[0] == n) {
                err = send(cSocket[0], "+", BUFLEN, 0);
                err = send(cSocket[1], "-", BUFLEN, 0);
                break;
            }
            sprintf(buf3, "Winner of round %d\nNumber of wins: %d\n", i + 1, numberOfWins[0]);
            err = send(cSocket[0], buf3, BUFLEN, 0);
            memset(buf3, 0, BUFLEN); 
            sprintf(buf3, "Loser of round %d\nNumber of wins: %d\n", i + 1, numberOfWins[1]);
            err = send(cSocket[1], buf3, BUFLEN, 0);
        }
        else if (result == 2) {
            numberOfWins[1]++;
            if (numberOfWins[1] == n) {
                err = send(cSocket[0], "-", BUFLEN, 0);
                err = send(cSocket[1], "+", BUFLEN, 0);
                break;
            }
            sprintf(buf3, "Loser of round %d\nNumber of wins: %d\n", i + 1, numberOfWins[0]);
            err = send(cSocket[0], buf3, BUFLEN, 0);
            memset(buf3, 0, BUFLEN); 
            sprintf(buf3, "Winner of round %d\nNumber of wins: %d\n", i + 1, numberOfWins[1]);
            err = send(cSocket[1], buf3, BUFLEN, 0);
        }
        else if (result == 0) {
            sprintf(buf3, "tie on round %d\n", i + 1);
            i--;
            err = send(cSocket[0], buf3, BUFLEN, 0);
            err = send(cSocket[1], buf3, BUFLEN, 0);
        }
        else /*Something went wrong, should never be here*/ {
            i--;
            sprintf(buf3, "error\n");
            err = send(cSocket[0], buf3, BUFLEN, 0);
            err = send(cSocket[1], buf3, BUFLEN, 0);
        }
        printf("Player0 wins: %d\nPlayer1 wins: %d\n", numberOfWins[0], numberOfWins[1]);
    }


    close(cSocket[0]);
    close(cSocket[1]);
    return 0;
}


int rps(char x, char y) {
    /*Tie cases*/
    if (x == 'r' && y == 'r')
        return 0;
    if (x == 'p' && y == 'p')
        return 0;
    if (x == 's' && y == 's')
        return 0;

    /*x win cases*/
    if (x == 'p' && y == 'r')
        return 1;
    if (x == 'r' && y == 's')
        return 1;
    if (x == 's' && y == 'p')
        return 1;
    
    /*y win cases*/
    if (x == 'r' && y == 'p')
        return 2;
    if (x == 's' && y == 'r')
        return 2;
    if (x == 'p' && y == 's')
        return 2;

    return -1;
}