#include <stdio.h>
#include <winsock2.h>


int main() {
    WSADATA WSAData;

    SOCKET server, client;

    SOCKADDR_IN serverAddr, clientAddr;

    WSAStartup(MAKEWORD(2, 0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);

    printf("Initializing...\n");

    bind(server, (SOCKADDR *) &serverAddr, sizeof(serverAddr));
    listen(server, 0);

    printf("Listening for incoming connections...\n");

    char buffer[2048];
    int clientAddrSize = sizeof(clientAddr);
    while ((client = accept(server, (SOCKADDR *) &clientAddr, &clientAddrSize)) != INVALID_SOCKET) {
        FILE *fd = fopen("C:\\Users\\USER\\CLionProjects\\socketsServer\\sockets_test_transmitted.txt", "w");
        printf("            Client connected!\n");
        while (1) {
            recv(client, buffer, sizeof(buffer), 0);
            fwrite(buffer, 1, sizeof(buffer), fd);
            if (buffer[0] == '\n') {
                break;
            }
        }
        printf("            received\n");

        memset(buffer, 0, sizeof(buffer));

        closesocket(client);
        printf("Client disconnected.\n");
    }
    return 0;
}