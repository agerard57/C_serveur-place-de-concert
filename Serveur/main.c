#include "header.h"

int ma_socket;

void *fonc(void * arg) {
    char buffer[512];
    char num_dossier[11];

    Arg *param;
    int c = 0;
    int i = -1;
    param = (Arg *) arg;

    read(param -> client_socket, buffer, sizeof(buffer));
    if (buffer[0] == 'r') {
        while (c < NB_DOSSIER) {
            if (param -> ensemble_dossiers[c].disponible) {
                param -> ensemble_dossiers[c].disponible = 0;
                i = c;
                c = NB_DOSSIER;
            }
            c++;
        }

        if (i == -1)
            write(param -> client_socket, "Toutes les réservations sont prises !", 128);
        else {
            write(param -> client_socket, "Une réservation est possible !", 128);
            read(param -> client_socket, buffer, sizeof(buffer));
            param -> ensemble_dossiers[i].nom = strdup(buffer);
            read(param -> client_socket, buffer, sizeof(buffer));
            param -> ensemble_dossiers[i].prenom = strdup(buffer);

            c = 0;
            while (c < 10) {
                num_dossier[c] = '0' + (rand() % 10);
                c++;
            }
            num_dossier[10] = '\0';
            param -> ensemble_dossiers[i].num_dossier = strdup(num_dossier);
            write(param -> client_socket, num_dossier, sizeof(num_dossier));
            printf("Le dossier numéro : %s à été réservé par %s %s\n",
                   num_dossier, param -> ensemble_dossiers[i].nom, param -> ensemble_dossiers[i].prenom);
        }
    } else {
        read(param -> client_socket, buffer, sizeof(buffer));

        read(param -> client_socket, num_dossier, sizeof(num_dossier));
        c = 0;
        i = 0;
        while (c < NB_DOSSIER) {
            if (!param -> ensemble_dossiers[c].disponible) {
                if (!strcmp(buffer, param -> ensemble_dossiers[c].nom) &&
                    !strcmp(num_dossier, param -> ensemble_dossiers[c].num_dossier)) {
                    param -> ensemble_dossiers[c].disponible = 1;
                    param -> ensemble_dossiers[c].nom = NULL;
                    param -> ensemble_dossiers[c].prenom = NULL;
                    param -> ensemble_dossiers[c].num_dossier = NULL;
                    c = NB_DOSSIER;
                    i = 1;
                    write(param -> client_socket, "Réservation annulée avec succès !", 128);
                    printf("Le dossier numéro : %s à été annulé\n", num_dossier);

                }
            }
            c++;
        }
        if (!i)
            write(param -> client_socket, "Votre réservation est introuvable !", 128);
    }
    shutdown(param -> client_socket, 2);
    close(param -> client_socket);
};

int main() {
    char buffer[512];

    Dossier *Dos;
    int i;

    struct sockaddr_in my_adr;
    struct sockaddr_in client_address;
    int long_addr;
    int client_socket;
    pthread_t td;

    srand(time(NULL));

    bzero(&my_adr, sizeof(my_adr));
    my_adr.sin_port = htons(30000);
    my_adr.sin_family = AF_INET;
    my_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    //Création de la socket
    if ((ma_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Création de la socket échouée !\n");
        exit(0);
    }

    bind(ma_socket, (struct sockaddr * ) &my_adr, sizeof(my_adr)); //Bind le serveur sur la socket
    listen(ma_socket, 5);
    long_addr = sizeof(client_address);

    Dos = (Dossier *) malloc(sizeof(Dossier) * NB_DOSSIER);
    i = 0;
    while (i < NB_DOSSIER) {
        Dos[i].disponible = 1;
        Dos[i].num_dossier = NULL;
        Dos[i].nom = NULL;
        Dos[i].prenom = NULL;

        i++;
    }

    while ((client_socket = accept(ma_socket, (struct sockaddr *) &client_address, &long_addr)) > 0) {
        Arg *T;

        T = (Arg *) malloc(sizeof(Arg) * 1);
        T -> client_socket = client_socket;
        T -> ensemble_dossiers = Dos;

        pthread_create(&td, NULL, fonc, T);

    }

    close(ma_socket);
}