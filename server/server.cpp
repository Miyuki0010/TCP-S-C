#include "server.h"
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>

using namespace std;

ServerSocket::ServerSocket(int port) {
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = htons(port);

  if (bind(serverSocket, (struct sockaddr *)&serverAddress,
           sizeof(serverAddress)) < 0) {
    perror("Error binding socket");
    exit(EXIT_FAILURE);
  }

  char ipAddress[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(serverAddress.sin_addr), ipAddress, INET_ADDRSTRLEN);
  cout << "Server running on IP address: " << ipAddress << endl;
}

void ServerSocket::listenForConn() {
  listen(serverSocket, 5);

  cout << "Server listening on port: " << ntohs(serverAddress.sin_port) << endl;

  while (true) {
    int clientSocket = accept(serverSocket, NULL, NULL);

    cout << "Client connected" << endl;
    thread clientThread(&ServerSocket::handleClient, this, clientSocket);

    clientThread.detach();
  }
}
void ServerSocket::stop() { close(serverSocket); }

void ServerSocket::start() {
  listen(serverSocket, 5);

  while (true) {
    struct sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress,
                              &clientAddressSize);
    if (clientSocket < 0) {
      perror("Error accepting client connection");
      continue;
    }

    // Add the new client to the list of connected clients
    connectedClients.push_back(clientSocket);

    // Start a new thread to handle the client's messages
    std::thread clientThread(&ServerSocket::handleClient, this, clientSocket);
    clientThread.detach();
  }
}

void ServerSocket::handleClient(int clientSocket) {
  char buffer[1024];
  std::string message = "Hello from server!";
  send(clientSocket, message.c_str(), message.length(), 0);

  int bytesRead = recv(clientSocket, buffer, 1024, 0);
  if (bytesRead < 0) {
    perror("Error receiving data from client");
  } else {
    buffer[bytesRead] = '\0';
    std::cout << "Received from client: " << buffer << std::endl;
  }

  close(clientSocket);
}
