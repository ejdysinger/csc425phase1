/*
 * client.c
 *
 *  Created on: Feb 4, 2016
 *      Author: Eamon Dysinger
 *
 */
//headers
#include "client.h"

#define DEBUGFLAG 0

int main(int argc, char* argv[]){
	//variables
	struct sockaddr_in server;        // struct storing connection information
	char* buffer;                      // char buffer to read up to 1024 characters from the input line
	int bufferSize;                    // the size of the buffer read from the user
	int toSocket;                      // integer value for the socket
	int oprStatus;

	// allocate the user buffer to hold max 1024 characters, not including the newline
	buffer = ((char *) malloc(BUFFER_SIZE));

	// allocate the serv_addr object and populate its fields
	server.sin_family = AF_INET;
	// compute the server IP address from the command line using a call to inet_aton
	inet_aton(argv[0], (struct in_addr *)&server);
	// convert the port specification into an integer, then to an unsigned short, then to a network short
	server.sin_port = htons((ushort)atoi(argv[1]));

	// Create TCP stream socket; if socket creation fails, print error msg and exit
	if((toSocket = socket(AF_INET,SOCK_STREAM,0)) < 0){
		fprintf(stderr,"ERROR 1: client failed to coreate socket\n");
		exit(-1);
	}

	// Connect to the server with the use of connect(), passing a sockaddr_in structure with the sin_family set to AF_INET, sin_port set to the port the endpoint is listening (in network byte order), and sin_addr set to the IP address of the listening server (also in network byte order.)
	if((oprStatus = connect(toSocket,(struct sockaddr *)&server,sizeof(server))) < 0){
		fprintf(stderr,"ERROR 2: CLIENT failed to connect to SERVER\n");
		exit(-1);
	}

	// continually read lines from the user until a blank line is read; after that is done, terminate.
	while((bufferSize = getUserInput(buffer)) != USER_INPUT_BLANK){
		// Communicate with the server by using send()
		// first send the size of the message
		send(toSocket, buffer, 4, 0);
		// next send the message itself.
		send(toSocket, buffer, strlen(buffer),0);
	}

	// Terminate the connection and clean up with a call to close().
	shutdown(toSocket, SHUT_RDWR);
	free(buffer);
}

/*****************************************************************************************************
 METHOD:      getUserInput
 DESCRIPTION: Prompts the user for a line of input and reads the line of input into a buffer
 PARAMS:      the buffer into which the user input should be read
 RETURNS:     the size of the buffer read
******************************************************************************************************/
int getUserInput(char* buffer){
	// clear the buffer
	memset(buffer, 0, sizeof(BUFFER_SIZE));
	// prompt the user
	fprintf(stdout,"\nEnter a line of text: ");
	// read their response
	fgets(buffer,1025,stdin);
	return strlen(buffer);
}

/*****************************************************************************************************
 METHOD:      clientInit
 DESCRIPTION: allocates memory for the buffer and the sockaddr_in struct and populates its members
 PARAMS:      pointers to buffer, sockaddr_in and the array of user params
 RETURNS:     void
******************************************************************************************************
void clientInit(char *buffer, struct sockaddr_in *server, char * argv){
	// allocate the user buffer to hold max 1024 characters, not including the newline
	buffer = ((char *) malloc(BUFFER_SIZE));

	// allocate the serv_addr object and populate its fields
	server.sin_family = PF_INET;
	// compute the server IP address from the command line using a call to inet_aton
	inet_aton(argv[0], server);
	// convert the port specification into an integer, then to an unsigned short, then to a network short
	server.sin_port = htons((ushort)atoi(argv[1]));
} */
