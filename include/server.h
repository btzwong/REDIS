#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>

class Server {
public:
    Server(int port);      // constructor (takes a port number)
    void start();          // starts the server (listens for clients)

private:
    int port_;             // which port to listen on
    SOCKET server_fd_;   
};

#endif