#include "server.h"
#include <iostream>

// Windows socket headers
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")  // Link Winsock library

//1

using namespace std;

Server::Server(int port) : port_(port), server_fd_(INVALID_SOCKET) {}

void Server::start() {
    // 1. Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        cerr << "WSAStartup failed: " << iResult << "\n";
        return;
    }

    // 2. Create a socket
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ == INVALID_SOCKET) {
        cerr << "Error creating socket\n";
        WSACleanup();
        return;
    }

    // 3. Bind the socket to an IP + port
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;   // Listen on all network interfaces
    serverAddr.sin_port = htons(port_);        // Convert port to network byte order

    if (bind(server_fd_, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Bind failed\n";
        closesocket(server_fd_);
        WSACleanup();
        return;
    }

    // 4. Start listening
    if (listen(server_fd_, SOMAXCONN) == SOCKET_ERROR) {
        cerr << "Listen failed\n";
        closesocket(server_fd_);
        WSACleanup();
        return;
    }

    cout << "Server listening on port " << port_ << "...\n";

  // 5. Accept clients forever
while (true) {
    SOCKET clientSocket;
    sockaddr_in clientAddr{};
    int clientSize = sizeof(clientAddr);

    clientSocket = accept(server_fd_, (sockaddr*)&clientAddr, &clientSize);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Accept failed\n";
        continue; // keep server running
    }

    cout << "Client connected!\n";

    // 6. Handle client messages in a loop (line-based)
    char buffer[1024];
    std::string message;

    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            message += buffer;

            // Telnet sends CRLF ("\r\n") when you press Enter
            size_t pos;
            while ((pos = message.find("\r\n")) != std::string::npos) {
                std::string line = message.substr(0, pos);
                message.erase(0, pos + 2);

                cout << "Received: " << line << "\n";

                // Echo back the whole line once
                send(clientSocket, line.c_str(), line.size(), 0);
            }
        }
        else if (bytesReceived == 0) {
            cout << "Client disconnected.\n";
            break; // exit client loop
        }
        else {
            cerr << "recv() failed.\n";
            break;
        }
    }

    closesocket(clientSocket); // ✅ close this client only
}

// only runs when server shuts down (not reached in infinite loop yet)
closesocket(server_fd_);
WSACleanup();

}