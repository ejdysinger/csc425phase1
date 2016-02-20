/*
 * Server.h
 * Author: Eamon Dysinger
 */

#ifndef SERVER_H_
#define SERVER_H_

// headers
#include <netinet/in.h>      // AF_INET and AF_INET6 address families and their corresponding protocol families, PF_INET and PF_INET6. These include standard IP addresses and TCP and UDP port numbers.
#include <sys/socket.h>      // Core socket functions and data structures
#include <sys/types.h>       //
#include <sys/un.h>          // PF_UNIX and PF_LOCAL address family. Used for local communication between programs running on the same computer.
#include <arpa/inet.h>       // Functions for manipulating numeric IP addresses.
#include <netdb.h>           // Functions for translating protocol names and host names into numeric addresses. Searches local data as well as name services.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//enums
#define BUFFER_SIZE 1056 // the max length of buffer that the client will read from the user plus 32 bits for the length
#define USER_INPUT_BLANK 0


// function prototypes
void serverInit(char *buffer, struct sockaddr_in *server, char * argv);

#endif /* SERVER_H_ */
