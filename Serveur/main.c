#include "header.h"

int ma_socket;

void *troakatorz(void *arg) {
    char buffer[512];
    char num_dossier[11];

    D_argy *param;
    int c = 0;
    int i = -1;
    param = (D_argy *) arg;

    read(param->client_socket, buffer, sizeof(buffer));
    if (buffer[0] == 'r'){
        while(c < NB_DOSSIER){
            if (param->monensemblededossier[c].disponible){
                param->monensemblededossier[c].disponible = 0;
                i = c;
                c = NB_DOSSIER;
            }
            c++;
        }

        if (i == -1)
            write(param->client_socket, "Toutes les réservations sont prises !", 128);
        else{
            write(param->client_socket, "Une réservation est possible !", 128);
            read(param->client_socket, buffer, sizeof(buffer));
            param->monensemblededossier[i].nom = strdup(buffer);
            read(param->client_socket, buffer, sizeof(buffer));
            param->monensemblededossier[i].prenom = strdup(buffer);

            c = 0;
            while (c < 10){
                num_dossier[c] = '0' + (rand() % 10);
                c++;
            }
            num_dossier[10] = '\0';
            param->monensemblededossier[i].num_dossier = strdup(num_dossier);
            write(param->client_socket, num_dossier, sizeof(num_dossier));
            printf("Le dossier numéro : %s à été réservé par %s %s\n",
                   num_dossier, param->monensemblededossier[i].nom, param->monensemblededossier[i].prenom);
        }
    }
    else{
        read(param->client_socket, buffer, sizeof(buffer));

        read(param->client_socket, num_dossier, sizeof(num_dossier));
        c = 0;
        i = 0;
        while(c < NB_DOSSIER){
            if (!param->monensemblededossier[c].disponible){
                if (!strcmp(buffer, param->monensemblededossier[c].nom) &&
                !strcmp(num_dossier, param->monensemblededossier[c].num_dossier)) {
                    param->monensemblededossier[c].disponible = 1;
                    param->monensemblededossier[c].nom = NULL;
                    param->monensemblededossier[c].prenom = NULL;
                    param->monensemblededossier[c].num_dossier = NULL;
                    c = NB_DOSSIER;
                    i = 1;
                    write(param->client_socket, "Réservation annulée avec succès !", 128);
                    printf("Le dossier numéro : %s à été annulé\n", num_dossier);

                }
            }
        c++;
        }
        if (!i)
            write(param->client_socket, "Votre réservation est introuvable !", 128);
    }
    shutdown(param->client_socket, 2);
    close(param->client_socket);
};


int main() {
    char buffer[512];

    Dossier *D_D;
    int I_I;

    struct sockaddr_in maya_dress;
    struct sockaddr_in client_address;
    int long_addr;
    int client_socket;
    pthread_t tresdheure;

    srand(time(NULL));

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

    D_D = (Dossier *)malloc(sizeof(Dossier) * NB_DOSSIER);
    I_I = 0;
    while (I_I < NB_DOSSIER){
        D_D[I_I].disponible = 1;
        D_D[I_I].num_dossier = NULL;
        D_D[I_I].nom = NULL;
        D_D[I_I].prenom = NULL;

        I_I++;
    }

    while ((client_socket = accept(ma_socket, (struct sockaddr*) &client_address, &long_addr))> 0)
    {
        D_argy *T_T;

        T_T = (D_argy *)malloc(sizeof(D_argy) * 1);
        T_T->client_socket = client_socket;
        T_T->monensemblededossier = D_D;

        pthread_create(&tresdheure, NULL, troakatorz, T_T);

    }

    close(ma_socket);
}

