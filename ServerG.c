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


    sprintf(buf3, "This round of rock, paper, scissors is best of %d", m); //Send number of games to be played to clients, as well as instructions
    printf("Debugging: %s\n", buf3);

    err = send(cSocket[0], buf3, strlen(buf3), 0);
    err = send(cSocket[1], buf3, strlen(buf3), 0);

    for (i = 0; i < m; i++) {                              //For (up to) m
        printf("Entering loop for the %d time!\n", i);
        memset(buf1, 0, 2);                     //reset three buffers
        memset(buf2, 0, 2);  
        memset(buf3, 0, BUFLEN);  
        err = recv(cSocket[0], buf1, 2, 0);        //Recv
        printf("%s\n", buf1);

        err = recv(cSocket[1], buf2, 2, 0);
        printf("%s\n", buf2);

        result = rps(buf1[0], buf2[0]);
        printf("Result: %d\n", result);

        if (result == 1) {
            printf("Entered result = 1 if statement\n");
            numberOfWins[0]++;
            sprintf(buf3, "Winner of round %d\nNumber of wins: %d\n", i + 1, numberOfWins[0]);
            err = send(cSocket[0], buf3, 50, 0);
            memset(buf3, 0, BUFLEN); 
            sprintf(buf3, "Loser of round %d\nNumber of wins: %d\n", i + 1, numberOfWins[1]);
            err = send(cSocket[1], buf3, 50, 0);

            if (numberOfWins[0] == n) {
                err = send(cSocket[0], "winnerwinner", 13, 0);
                err = send(cSocket[1], "loserloser", 11, 0);
                break;
            }
        }
        else if (result == 2) {
            printf("Entered result = 2 if statement\n");
            numberOfWins[1]++;
            sprintf(buf3, "Loser of round %d\nNumber of wins: %d\n", i + 1, numberOfWins[0]);
            err = send(cSocket[0], buf3, 50, 0);
            memset(buf3, 0, BUFLEN); 
            sprintf(buf3, "Winner of round %d\nNumber of wins: %d\n", i + 1, numberOfWins[1]);
            err = send(cSocket[1], buf3, 50, 0);
            if (numberOfWins[1] == n) {
                err = send(cSocket[0], "loserloser", 11, 0);
                err = send(cSocket[1], "winnerwinner", 13, 0);
                break;
            }
        }
        else if (result == 0) {
            printf("Entered result = 0 if statement\n");
            sprintf(buf3, "tie on round %d\n", i + 1);
            err = send(cSocket[0], buf3, 50, 0);
            err = send(cSocket[1], buf3, 50, 0);
        }
        else /*Something went wrong, should never be here*/ {
            i--;
            sprintf(buf3, "error\n");
            err = send(cSocket[0], buf3, 6, 0);
            err = send(cSocket[1], buf3, 6, 0);
        }
    }


    close(cSocket[0]);
    close(cSocket[1]);
    return 0;
}


int rps(char x, char y) {
    printf("char x: %c\n", x);
    printf("char y: %c\n", y);
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