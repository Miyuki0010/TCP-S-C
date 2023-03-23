#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

using namespace std;

class ServerSocket {
private:
  int serverSocket;
  struct sockaddr_in serverAddress;
  vector<int> connectedClients;
  void handleClient(int clientSocket);

public:
  ServerSocket(int port);
  void listenForConn();
  void stop();
  void start();
};

#endif // DEBUG!
