# TCP-Server

This is a basic TCP server. This was for a NWEN 243 Assignment. All it does is shouts a message back to client
(uppercases the message).

To compile and run server:
1. Compile in terminal: gcc tcpserver.c -o server
2. Run ./server port_number_to_host_on
e.g. ./server 5000


To compile and run client:
1. Compile in terminal: gcc client.c -o client
2. Run ./client address   port_num_to_connect_to   message
e.g. ./client localhost 5000 "Hello World"
