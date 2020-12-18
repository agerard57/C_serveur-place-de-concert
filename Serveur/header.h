#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <netinet/in.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <signal.h>
# include <stdbool.h>
# include <time.h>
# include <pthread.h>

<<<<<<< HEAD
# define NB_DOSSIER 5

struct dossier{
    int disponible;
    int num_dossier;
    char *nom;
    char *prenom;
    pthread_mutex_t *mu_temps;
};
typedef struct dossier Dossier;

struct arg{
    int client_socket;
    Dossier *monensemblededossier;
};
typedef struct arg D_argy;

=======
>>>>>>> 9a32b5571c04a61f99394cf6fff88073caf84ead
#endif