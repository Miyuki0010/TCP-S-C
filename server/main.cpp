#include "server.h"

int main() {
  ServerSocket server(8080);
  server.listenForConn();
  return 0;
}
