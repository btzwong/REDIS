#ifndef SERVER_H
#define SERVER_H

class Server {
public:
    Server(int port);      // constructor (takes a port number)
    void start();          // starts the server (listens for clients)

private:
    int port_;             // which port to listen on
    int server_fd_;        // the server socket (file descriptor)
};

#endif