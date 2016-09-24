#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#define bufsize 1024

void eatZombies(int n){
	// This function removes the zombie process state left
	// after the child exits. Learn about this in NWEN 301!

	wait3(NULL,WNOHANG,NULL); // Nom Nom
}

int main(int argc, char *argv[]){
	int sock, length, msgsock, status;
	struct sockaddr_in server, client;
	char buf[bufsize];

	// for forking, and cleaning up zombie child state afterwards
	// You must not change this code.

	pid_t id;
	signal(SIGCHLD, &eatZombies);

	// OK, NWEN 243 code starts here.
	if(argc < 1){
        printf("Please include one arg which is the port number to host the server on \n");
        return(-1);
     }

	// Create a socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(msgsock < 0){
    	printf("Error creating the socket \n");
        return(-1);
    }

	// Next, create the socket addressing structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1])); // this time 1st arg is port#
	printf("Created socket successfully \n");

	// Bind the socket
	int bind_code = bind(sock, (struct sockaddr *) &server, sizeof(server));
	if(bind_code < 0){
    	printf("Error trying to bind to socket \n");
        return(-1);
    }
	printf("Successfully binded the socket \n");


	// Listen to the socket
	int listen2 = listen(sock, 5);
	if(listen2 < 0){
    	printf("Error listening to socket \n");
        return(-1);
    }

    socklen_t socklength = sizeof(client);
	while(1){
		// Accept the connection request
		msgsock = accept(sock, (struct sockaddr *) &client, &socklength);
	    printf("Accepted the connection \n");

		// the next call makes a new child process that will actually handle the client.
		id = fork();

		if(id == 0){  // This is the child and needs to do the work for the server.
			// Read from the connection socket, process the data and write back to the socket
			int read_code = read(msgsock, &buf, bufsize);
			if(read_code < 0){
				printf("Error reading from the socket \n");
			}

	        printf("Read data from the socket \n");

			// Modify the buffers data, in this case we will SHOUT the message back to the client
            for(int i=0; i < bufsize; i++){
                buf[i] = toupper(buf[i]);
            }
            fprintf(stdout,"%s\n", buf);
			int write_code = write(msgsock, &buf, bufsize);
			printf("Wrote a message to the socket \n");

		    // Then close and finally call exit(0) when done.
		    close(msgsock);
	        exit(0);

		}else if(id > 0){  // This is the parent, and it should just loop around
			continue;

		}else{ // We have an error
			error("An error occoured trying to fork the socket");
			return(-1);
		}

	}
	close(sock);
}

