#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char message[BUFFER_SIZE];

    // Crear socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error al crear el socket\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir la dirección IP
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Dirección inválida\n");
        return -1;
    }

    // Conectar al servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Error al conectar\n");
        return -1;
    }

    // Pedir el mensaje al usuario
    printf("Escribe el mensaje a enviar: ");
    fgets(message, BUFFER_SIZE, stdin);

    // Enviar el mensaje
    send(sock, message, strlen(message), 0);
    printf("Mensaje enviado\n");

    close(sock);

    return 0;
}
