#include "client.h"

int main() {
  string serverAddress;
  int serverPort;

  cout << "Enter server address: ";
  cin >> serverAddress;
  cout << "Enter server port: ";
  cin >> serverPort;

  ClientSocket client(serverAddress, serverPort);
  client.sendAndReceive();
  return 0;
}
