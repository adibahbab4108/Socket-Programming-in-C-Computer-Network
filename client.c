#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define PORT 8080

int main() {
    WSADATA wsa;
    SOCKET client_fd;
    struct sockaddr_in server;
    char* hello = "Hello Adib, Are you there? (from client)";
    char buffer[1024] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    // Create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation error.\n");
        WSACleanup();
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect
    if (connect(client_fd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Connection failed.\n");
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }

    send(client_fd, hello, strlen(hello), 0);
    printf("Hello message sent.\n");

    recv(client_fd, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    closesocket(client_fd);
    WSACleanup();
    return 0;
}
