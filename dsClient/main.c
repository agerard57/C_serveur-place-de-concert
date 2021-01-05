#include "header.h"

int to_servers_socket = -1;

void vider_buffer() {
    int c;
    while ((c = getchar()) != EOF && c != '\n');
}

int main() {
    struct sockaddr_in server_socket_address;
    struct hostent * server_host_ent;
    long hostaddr;
    char buffer[512];
    char buffer2[512];

    char c;

    char server_name[16];

    printf("Saisir l'ip du serveur :\n");
    scanf("%s",server_name);

    bzero(&server_socket_address, sizeof(server_socket_address));
    hostaddr = inet_addr(server_name);

    if (hostaddr != (long) - 1)
        bcopy(&hostaddr, &server_socket_address.sin_addr, sizeof(hostaddr));
    else {
        server_host_ent = gethostbyname(server_name);
        if (server_host_ent == NULL) {
            printf("Problème au niveau de l'hôte\n");
            exit(0);
        }
        bcopy(server_host_ent -> h_addr, &server_socket_address.sin_addr, server_host_ent -> h_length);
    }

    server_socket_address.sin_port = htons(30000);
    server_socket_address.sin_family = AF_INET;
    //Création de la socket
    if ((to_servers_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Création socket client ratée !\n");
        exit(0);
    }
    //Demande de connexion
    if (connect(to_servers_socket, (struct sockaddr *) & server_socket_address, sizeof(server_socket_address)) < 0) {
        printf("Demande de connexion ratée\n");
        exit(0);
    }

    printf("Voulez-vous faire ou annuler une réservation ? (F/A)\n"); //TODO MENU

    vider_buffer();
    scanf("%c", & c);
    if (c == 'F') {
        write(to_servers_socket, "r\0", 2);
        read(to_servers_socket, buffer, sizeof(buffer));
        printf("%s\n", buffer);

        if (buffer[0] == 'U') {
            printf("Veuillez saisir votre nom :\n");
            vider_buffer();
            scanf("%s", buffer2);
            write(to_servers_socket, buffer2, sizeof(buffer2));

            printf("Veuillez saisir votre prenom :\n");
            vider_buffer();
            scanf("%s", buffer2);
            write(to_servers_socket, buffer2, sizeof(buffer2));

            read(to_servers_socket, buffer, sizeof(buffer));
            printf("Votre numéro de dossier est : %s\n", buffer);
        }
    }
    if (c == 'A') {
        write(to_servers_socket, "a\0", 2);

        printf("Veuillez saisir votre nom :\n");
        vider_buffer();
        scanf("%s", buffer2);
        write(to_servers_socket, buffer2, sizeof(buffer2));

        printf("Veuillez saisir votre numéro de dossier :\n");
        vider_buffer();
        scanf("%s", buffer2);
        write(to_servers_socket, buffer2, sizeof(buffer2));
        read(to_servers_socket, buffer, sizeof(buffer));
        printf("%s\n", buffer);
    }
    //Fermeture de la connexion
    shutdown(to_servers_socket, 2);
    close(to_servers_socket);
}