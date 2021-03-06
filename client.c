// NWEN 243, Victoria University of Wellington. Author, Kris Bubendorfer.

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#define bufsize 1024

int main(argc, argv) int argc; char *argv[];{
  int sock, rval;
  struct hostent *host;
  struct sockaddr_in server;  // not a pointer.
  char buf[bufsize];

  if(argc != 4){
    printf("usage:\ntcpclient hostname port string\n\n");
    return(-1);
  }

  // look up hostname (server) using DNS

  if ((host = gethostbyname(argv[1])) == 0) {
    fprintf(stderr, "%s: unknown host\n", argv[1]);
    return(-1);
  }

  // Set up fields for socket to point to host and port

  bcopy(host->h_addr, &server.sin_addr, host->h_length);
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));


  // Is the string size greater than the buffer?
  if(strlen(argv[3]) > bufsize){
	  fprintf(stdout,"Mate you need to enter a smaller string\n");
	  return(-1);
  }
  for(int i =0; i < 100; i++){

  // Create socket
  sock = socket(AF_INET, SOCK_STREAM, 0);

  // connect (3-way handshake)
  int connectCode  = connect(sock, (struct sockaddr *) &server,  sizeof(server));
  if(connectCode < 0){
	  fprintf(stdout, "Error connecting with the server\n");
	  return(-1);
  }

  // Copy the arg into buf so we can send it to the server
  strncpy(buf, argv[3], bufsize);

  // Send sentence to server
    int write_value = write(sock, &buf, bufsize);

    // read response from server
    int read_code = read(sock, &buf, bufsize);

    // print result to window
    fprintf(stdout,"%s\n", buf);
    

  close(sock);
  sleep(1);
  }
}

