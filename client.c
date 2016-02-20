/*
 * client.c
 * Author: Eamon Dysinger
 * Command Line syntax:  ./client ip port
 *
 */

#include "client.h"

#define DEBUGFLAG 1

int main(int argc, char* argv[]){
	//variables
	struct sockaddr_in server;        // struct storing connection information
	char* buffer[BUFFER_SIZE];        // char buffer to read up to 1024 characters from the input line
	char* str[4];
	char* message_in_a_bottle[BUFFER_SIZE + 4];  // the complete message that the client can send to the server
	int bufferSize;                   // the size of the buffer read from the user
	int toSocket;                     // integer value for the socket
	int oprStatus;
	uint32_t bfSz;


	if(DEBUGFLAG == 1){
		fprintf(stdout,"debug(main): starting up client\n");
	}

	// allocate the serv_addr object and populate its fields
	// compute the server IP address from the command line using a call to inet_aton
	// inet_aton(argv[1], (struct in_addr *)&server);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port = htons(atoi(argv[2]));
	bzero(&server.sin_zero,8);

	if(DEBUGFLAG == 1){
		fprintf(stdout,"debug(main): client server info entered\n       eth0 address is %s\n       port is %s (%d)\n",argv[1], argv[2], atoi(argv[2]));
	}

	// Create TCP stream socket; if socket creation fails, print error msg and exit
	if((toSocket = socket(AF_INET,SOCK_STREAM,0)) == ERROR){
		fprintf(stderr,"ERROR 1: client failed to create socket\n");
		exit(ERROR);
	}

	if(DEBUGFLAG == 1){
		fprintf(stdout,"debug(main):socket successfully generated\n");
	}

	// Connect to the server with the use of connect(), passing a sockaddr_in structure with the sin_family set to AF_INET, sin_port set to the port the endpoint is listening (in network byte order), and sin_addr set to the IP address of the listening server (also in network byte order.)
	if((oprStatus = connect(toSocket,(struct sockaddr *)&server,sizeof(struct sockaddr_in))) == ERROR){
		fprintf(stderr,"ERROR 2: CLIENT failed to connect to SERVER\n");
		exit(ERROR);
	}

	if(DEBUGFLAG == 1){
		fprintf(stdout,"debug(main): socket successfully connected\n");
	}

	// continually read lines from the user until a blank line is read; after that is done, terminate.
	while((bufferSize = getUserInput(buffer)) != USER_INPUT_BLANK){
		if(DEBUGFLAG == 1){
			fprintf(stdout,"debug(main): text has been fetched (%s)\n", buffer);
		}
		// Communicate with the server by using send()
		// first send the size of the message
		if((oprStatus = send(toSocket, &bufferSize, 32,0) == ERROR){
			fprintf(stderr,"Connection to server lost\n");
			break;
		}
		// send the message itself
		if((oprStatus = send(toSocket, buffer, bufferSize,0) == ERROR){
			fprintf(stderr,"Connection to server lost\n");
			break;
		}


//		padMessageSize(str,bufferSize);

//		if(DEBUGFLAG == 1){
//			fprintf(stdout,"debug(main):interpreting buffer size\n       buffer size: %s",str);
//		}

//		// constructs the message from the buffer and its size
//		if(DEBUGFLAG == 1){
//			fprintf(stdout,"debug(main): clearing message\n", buffer);
//		}
//		memset(message_in_a_bottle, '\0', BUFFER_SIZE + 32);
//		if(DEBUGFLAG == 1){
//			fprintf(stdout,"debug(main): Placing length value in message\n", buffer);
//		}
//		bfSz = htonl(bufferSize);
//		memcpy(message_in_a_bottle, &bfSz,32);
//		if(DEBUGFLAG == 1){
//			fprintf(stdout,"debug(main): placing buffer in message\n", buffer);
//		}
//		memcpy(message_in_a_bottle+32, buffer, bufferSize);
//		if((oprStatus = send(toSocket, message_in_a_bottle, bufferSize + 32,0) == ERROR){
//			fprintf(stderr,"Connection to server lost\n");
//			break;
//		}
	}

	if(DEBUGFLAG == 1){
		fprintf(stdout,"debug(main): shutting down socket\n");
	}
	// Terminate the connection and clean up with a call to close().
	close(toSocket);
	free(buffer);
}

/*****************************************************************************************************
 METHOD:      getUserInput
 DESCRIPTION: Prompts the user for a line of input and reads the line of input into a buffer
 PARAMS:      the buffer into which the user input should be read
 RETURNS:     the size of the buffer read
******************************************************************************************************/
int getUserInput(char* buffer){
	if(DEBUGFLAG == 1){
		fprintf(stdout,"debug(getUserInput): starting\n");
	}
	char * str;
	// clear the buffer
	memset(buffer, 0, sizeof(BUFFER_SIZE) - 1);
	// prompt the user
	fprintf(stdout,"\nEnter a line of text: ");
	// read their response
	fgets(buffer,1024,stdin);
	if(DEBUGFLAG == 1){
		fprintf(stdout,"debug(getUserInput): text fetched (%s)\n", buffer);
	}
	return strlen(buffer);
}

/*****************************************************************************************************
 METHOD:      padMessageSize
 DESCRIPTION: takes the message, converts it to a string and pads it with zeroes
 PARAMS:      a pointer to the character array, the integer value of the message size
 RETURNS:     void
******************************************************************************************************/
void padMessageSize(char * buffer, int bufferSize){
	// clear the old data contained in the buffer
	memset(buffer,'\0',4);
	// determine how many digits the base-ten string length integer is and pad accordingly
	if(bufferSize >= 1000)
		sprintf(buffer,"%d", bufferSize);
	else if(bufferSize >= 100)
		sprintf(buffer,"0%d", bufferSize);
	else if(bufferSize >= 10)
		sprintf(buffer,"00%d", bufferSize);
	else
		sprintf(buffer,"000%d", bufferSize);
}
