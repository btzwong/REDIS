#include "server.h"

int main() {
    Server server(6379);  // Redis default port
    server.start();       // Start listening for clients
    return 0;
}