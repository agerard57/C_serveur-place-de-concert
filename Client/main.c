#include "header.h"
<<<<<<< HEAD
#define SERVER_NAME "172.17.228.75"
=======
#define SERVER_NAME "192.168.248.20"
>>>>>>> 9a32b5571c04a61f99394cf6fff88073caf84ead

int to_servers_socket = -1;

int main()
{
    struct sockaddr_in server_socket_address;
    struct hostent *server_host_ent;
    long hostaddr;
    char buffer[512];
    char buffer2[512];

    bzero(&server_socket_address, sizeof(server_socket_address));
    hostaddr = inet_addr(SERVER_NAME);

    if (hostaddr != (long) - 1)
        bcopy(&hostaddr, &server_socket_address.sin_addr, sizeof(hostaddr));
    else {
        server_host_ent = gethostbyname(SERVER_NAME);
        if (server_host_ent == NULL) {
            printf("Problème au niveau de l'hôte\n");
            exit(0);
        }
        bcopy(server_host_ent->h_addr, &server_socket_address.sin_addr, server_host_ent->h_length);
    }

    server_socket_address.sin_port = htons(30000);
    server_socket_address.sin_family = AF_INET;
    //Création de la socket
    if ((to_servers_socket = socket(AF_INET, SOCK_STREAM, 0))< 0) {
        printf("Création socket client ratée !\n");
        exit(0);
    }
    //Demande de connexion
    if (connect (to_servers_socket, (struct sockaddr*) &server_socket_address, sizeof(server_socket_address))< 0)
    {
        printf("Demande de connexion ratée\n");
        exit(0);
    }

<<<<<<< HEAD

    read(to_servers_socket, buffer, sizeof(buffer));
    printf("Q\n");

=======
    //Contenu be like
    write(to_servers_socket, "Bonjour\0", sizeof(char) * 8);
>>>>>>> 9a32b5571c04a61f99394cf6fff88073caf84ead

    //Fermeture de la connexion
    shutdown(to_servers_socket, 2);
    close(to_servers_socket);
}