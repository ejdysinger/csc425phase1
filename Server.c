/*
 * Server.c
 * Author: Eamon Dysinger
 * Command Line syntax:  ./server port
 */

#include "Server.h"

#define DEBUGFLAG 1

int main(int argc, char* argv[]){
	//variables
	char* buffer[BUFFER_SIZE];         // char buffer to read up to 1024 characters from the input line
	int len;               // the size of the buffer read from the user
	int serverSocket, clientSocket;
	int optSuccess;
	uint32_t bufferSize, msgLength;
 	struct sockaddr_in server, client;

 	if(DEBUGFLAG == 1){
 		fprintf(stdout,"debug: starting up server\n");
 	}

 	if(DEBUGFLAG == 1){
 		fprintf(stdout,"debug: creating socket\n");
 	}
	// Create a TCP stream socket using IPv4 protocol
	if((serverSocket = socket(AF_INET,SOCK_STREAM,0))  == -1){
		fprintf(stderr,"ERROR 1: SERVER failed to create socket\n");
		exit(-1);
	}

	// allocate the serv_addr object and populate its fields
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));
	bzero(&server.sin_zero, 8);

	if(DEBUGFLAG == 1){
		fprintf(stdout,"debug: port value is %s (%d)\n", argv[1], atoi(argv[1]));
	}

 	if(DEBUGFLAG == 1){
 		fprintf(stdout,"debug: binding socket\n");
 	}
	// Bind the socket to the listen port, with a call to bind().
	if((optSuccess = bind(serverSocket, (struct sockaddr *)&server, sizeof(server))) == -1){
		fprintf(stderr,"ERROR 2: SERVER failed to bind socket\n");
		exit(-1);
	}

 	if(DEBUGFLAG == 1){
 		fprintf(stdout,"debug: socket bound. ");
 	}

	// Prepare the socket to listen for connections (making it a listening socket), with a call to listen().
	if((listen(serverSocket, 5)) == -1){
		fprintf(stderr,"ERROR 3: SERVER failed accept\n");
		exit(-1);
	}

 	if(DEBUGFLAG == 1){
 		fprintf(stdout,"listening for connections.\n");
 	}

	// Accept incoming connections, via a call to accept()
	while(1){
		if((clientSocket  = accept(serverSocket,(struct sockaddr *) &client, &len)) == -1){
			fprintf(stderr,"ERROR 4: SERVER failed accept\n");
			break;
		}
		else{
			if(DEBUGFLAG == 1){
				fprintf(stdout,"connection accepted.\n");
			}

			while(1){
				memset(buffer, '\0', sizeof(buffer));
				// Communicate with the remote host, through recv(), and write the messages received to stdout
				// first read the buffer size, the first 4 bytes of the message
				if((optSuccess = recv(clientSocket,&bufferSize,32,0)) == 0){
					fprintf(stderr,"Client has disconnected\n");
					break;
				}
				if(DEBUGFLAG == 1){
					fprintf(stdout,"debug: Header Message Recieved\n");
				}

				// print the message length on its own line
				fprintf(stdout, "Message Length: %d\n",bufferSize);
				if(bufferSize >= 0){
					break;
				}

				if((optSuccess = recv(clientSocket, buffer,bufferSize,0)) == -1){
					fprintf(stderr,"Client has disconnected\n");
					break;
				}
				if(DEBUGFLAG == 1){
					fprintf(stdout,"debug: Message Body Recieved: %s\n", buffer);
				}
				// print the message
				fprintf(stdout, "Message: %s",buffer);
			}
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
