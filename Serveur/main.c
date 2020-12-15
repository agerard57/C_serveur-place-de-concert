#include "header.h"

char buffer[512];
int ma_socket;

//des trucs

int main() {
    struct sockaddr_in maya_dress;
    struct sockaddr_in client_address;
    int long_addr;
    int client_socket;
    pthread_t tresdheure;

    bzero(&maya_dress, sizeof(maya_dress));
    maya_dress.sin_port = htons(30000);
    maya_dress.sin_family = AF_INET;
    maya_dress.sin_addr.s_addr = htonl(INADDR_ANY);

    //Création de la socket
    if ((ma_socket= socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("Création de la socket échouée !\n");
        exit(0);
    }

    bind(ma_socket, (struct sockaddr*) &maya_dress, sizeof(maya_dress)); //Bind le serveur sur la socket
    listen(ma_socket, 5);
    long_addr = sizeof(client_address);

    if ((client_socket = accept(ma_socket, (struct sockaddr*) &client_address, &long_addr))> 0)
    {
        read(client_socket, buffer, sizeof(buffer));
        printf("%s\n", buffer);

        shutdown(client_socket, 2);
        close(client_socket);
    }
}
