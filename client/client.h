#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

class ClientSocket {
private:
  int clientSocket;
  string serverAddress;
  int serverPort;

public:
  ClientSocket();
  ;
  ClientSocket(string serverAddress, int serverPort);
  void sendAndReceive();
};

#endif // !DEBUG
