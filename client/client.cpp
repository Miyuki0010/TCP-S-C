#include "client.h"

ClientSocket::ClientSocket() {
  serverAddress = "127.0.0.1"; // default address
  serverPort = 8888;           // default port

  clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(serverPort);
  inet_pton(AF_INET, serverAddress.c_str(), &serverAddr.sin_addr);

  if (connect(clientSocket, (struct sockaddr *)&serverAddr,
              sizeof(serverAddr)) < 0) {
    perror("Error connecting to server");
    exit(EXIT_FAILURE);
  }
}

ClientSocket::ClientSocket(string serverAddress, int serverPort) {
  this->serverAddress = serverAddress;
  this->serverPort = serverPort;

  clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(serverPort);
  inet_pton(AF_INET, serverAddress.c_str(), &serverAddr.sin_addr);

  if (connect(clientSocket, (struct sockaddr *)&serverAddr,
              sizeof(serverAddr)) < 0) {
    perror("Error connecting to server");
    exit(EXIT_FAILURE);
  }
}

void ClientSocket::sendAndReceive() {
  char buffer[1024];
  int bytesReceived;
  while (true) {
    std::cout << "Enter message: ";
    std::string message;
    std::getline(std::cin, message);

    if (message == "quit") {
      break;
    }

    send(clientSocket, message.c_str(), message.length(), 0);

    bytesReceived = recv(clientSocket, buffer, 1024, 0);
    std::cout << "Received: " << buffer << std::endl;
  }
  close(clientSocket);
}
