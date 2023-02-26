#ifndef SERVER_H
#define SERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#define SERVERPORT 54321
#define SERVERPORTSTR "54321"
#define SERVERIP "127.0.0.1"
#define SERVERNAME "ahscentos"
#define BUFLEN 100
#endif