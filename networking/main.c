#include <stdlib.h>     // standard lib
#include <unistd.h>     // standard POSIX functions
#include <sys/socket.h> // socket functions
#include <arpa/inet.h>  // hton functions
#include <netinet/in.h> // sockaddr structs
#include <stdio.h>      // standard io

// server settings
#define PORT            5555 // port to listen from
#define BACKLOG         10   // number of pending requests to allow

// domain
// AF_INET  = IPv4 connections
// AF_INET6 = IPv6 connections
#define SOCKET_DOMAIN   AF_INET6

// type
// SOCK_STREAM = TCP  (reliable connection)
// SOCK_DGRAM  = UDP (unreliable, no connection, but fast)
#define SOCKET_TYPE     SOCK_STREAM

// protocol
// 0 = default
#define SOCKET_PROTOCOL 0

int main(int argc, char* argv[]) {
	// create socket
	int serverSocket = socket(SOCKET_DOMAIN, SOCKET_TYPE, SOCKET_PROTOCOL);
	if (serverSocket == -1) {
		fprintf(stderr, "socket\n");
		return EXIT_FAILURE;
	}

	printf("Socket: %i\n", serverSocket);

	// create server socket info
	struct sockaddr_in serverAddress = {0};
	serverAddress.sin_family = SOCKET_DOMAIN;
	serverAddress.sin_addr.s_addr = INADDR_ANY; // enable accepting requests from any IP
	serverAddress.sin_port = htons(PORT);

	// bind socket
	if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
		fprintf(stderr, "bind\n");
		close(serverSocket);
		return 1;
	}

	// create client info
	struct sockaddr_in clientAddress;
	socklen_t clientAddrLen = sizeof(clientAddress);

	int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddrLen);
	if (clientSocket == -1) {
		fprintf(stderr, "accept\n");
		close(clientSocket);
		return 1;
	}

	close(clientSocket);
	close(serverSocket);

	return EXIT_SUCCESS;
}

