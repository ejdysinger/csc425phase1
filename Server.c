/*
 * Server.c
 *
 *  Created on: Feb 5, 2016
 *      Author: Eamon Dysinger
 */

#include "Server.h"

#define DEBUGFLAG 0

int main(int argc, char* argv[]){
	//variables
	char* buffer[BUFFER_SIZE];         // char buffer to read up to 1024 characters from the input line
	int bufferSize, len;            // the size of the buffer read from the user
	int serverSocket, clientSocket;
	int optSuccess;
 	struct sockaddr_in server, client;

	// initialize buffer and sockaddr struct
	// serverInit(&server, buffer, argv);

	// allocate the serv_addr object and populate its fields
	server.sin_family = AF_INET;
	server.sin_addr = INADDR_ANY;
	// convert the port specification into an integer, then to an unsigned short, then to a network short
	server.sin_port = htons((ushort)atoi(argv[1]));

	// Create a TCP stream socket using IPv4 protocol
	if((serverSocket = socket(AF_INET,SOCK_STREAM,0)) < 0){
		fprintf(stderr,"ERROR 1: SERVER failed to create socket\n");
		exit(-1);
	}

	// Bind the socket to the listen port, with a call to bind().
	if((optSuccess = bind(serverSocket, (struct sockaddr *)&server, sizeof(server))) < 0){
		fprintf(stderr,"ERROR 2: SERVER failed to bind socket\n");
		exit(-1);
	}

	// Prepare the socket to listen for connections (making it a listening socket), with a call to listen().
	if((listen(serverSocket, 5)) == -1){
		fprintf(stderr,"ERROR 3: SERVER failed accept\n");
		exit(-1);
	}

	// Accept incoming connections, via a call to accept()
	while(1){
		if((clientSocket  = accept(serverSocket,(struct sockaddr *) &client, &len)) == -1){
			fprintf(stderr,"ERROR 4: SERVER failed accept\n");
			exit(-1);
		}
		else{
			memset(buffer, 0, sizeof(buffer));
		    // Communicate with the remote host, through recv(), and write the messages received to stdout
			// first read the buffer size
			recv(clientSocket, buffer,4,0);
			bufferSize = atoi(buffer);
			// adjust the size of the message to be read
			if(bufferSize > BUFFER_SIZE) bufferSize = BUFFER_SIZE;
			// if an empty string is read, break from the receive loop and end the server's execution
			else if(bufferSize == 0) break;
			// read the actual message
			recv(clientSocket, buffer,bufferSize,0);
			// print the message
			fprintf(stdout, "Message : %s",buffer);
		}
	}

	// Close the socket that was opened once it is no longer needed, using close().
	close(clientSocket);
	close(serverSocket);
	free(buffer);
	return 0;
}

/*****************************************************************************************************
 METHOD:      serverInit
 DESCRIPTION: allocates memory for the buffer and the sockaddr_in struct and populates its members
 PARAMS:      pointers to buffer, sockaddr_in and the array of user params
 RETURNS:     void
******************************************************************************************************/
/*void serverInit(char *buffer, struct sockaddr_in *server, char * argv){

}*/

/*****************************************************************************************************
 METHOD:
 DESCRIPTION:
 PARAMS:
 RETURNS:
******************************************************************************************************/
