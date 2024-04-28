#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define PORT 8080

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in server, client;
    int addrlen = sizeof(struct sockaddr_in);
    char buffer[1024] = {0};
    char* hello = "Hello from server";

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation error.\n");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed.\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Listen
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Listen failed.\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&client, &addrlen)) == INVALID_SOCKET) {
        printf("Accept failed.\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    recv(new_socket, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}
