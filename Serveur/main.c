#include "header.h"

char buffer[512];
int ma_socket;

<<<<<<< HEAD
void *troakatorz(void *arg) {
    printf("%i\n", getpid());
    D_argy *param;
    int c = 0;
    int i = -1;
    param = (D_argy *) arg;
    //read(param->client_socket, buffer, sizeof(buffer));
    //printf("%s\n", buffer);
    while(c < NB_DOSSIER){
        if (param->monensemblededossier[c].disponible){
            param->monensemblededossier[c].disponible = 0;
            pthread_mutex_lock(param->monensemblededossier[c].mu_temps);
            i = c;
            c = NB_DOSSIER;
        }
        c++;
    }
    printf("%i\t%i\n",i,param->monensemblededossier[c].disponible);

    if (i == -1)
        write(param->client_socket, "Toutes les réservations sont prises !", 128);
    else{
        printf("Ligne 40\n");

        while (1);
    }
    shutdown(param->client_socket, 2);
    close(param->client_socket);
};


int main() {
    printf("%i\n", getpid());
    Dossier *D_D;
    int I_I;
=======
//des trucs

int main() {
>>>>>>> 9a32b5571c04a61f99394cf6fff88073caf84ead
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

<<<<<<< HEAD
    D_D = (Dossier *)malloc(sizeof(Dossier) * NB_DOSSIER);
    I_I = 0;
    while (I_I < NB_DOSSIER){
        D_D[I_I].disponible = 1;
        D_D[I_I].num_dossier = 0;
        D_D[I_I].nom = NULL;
        D_D[I_I].prenom = NULL;
        D_D[I_I].mu_temps = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
        pthread_mutex_init(D_D[I_I].mu_temps, NULL);

        I_I++;
    }

    while ((client_socket = accept(ma_socket, (struct sockaddr*) &client_address, &long_addr))> 0)
    {
        D_argy *T_T;

        T_T = (D_argy *)malloc(sizeof(D_argy) * 1);
        T_T->client_socket = client_socket;
        T_T->monensemblededossier = D_D;

       //if(fork() == 0){

            pthread_create(&tresdheure, NULL, troakatorz, T_T);
           // pthread_join(tresdheure, NULL);

        //    exit(0);
      //  }
    }

    close(ma_socket);
}
=======
    if ((client_socket = accept(ma_socket, (struct sockaddr*) &client_address, &long_addr))> 0)
    {
        read(client_socket, buffer, sizeof(buffer));
        printf("%s\n", buffer);

        shutdown(client_socket, 2);
        close(client_socket);
    }
}
>>>>>>> 9a32b5571c04a61f99394cf6fff88073caf84ead
