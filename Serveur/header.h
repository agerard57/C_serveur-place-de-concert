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

# define NB_DOSSIER 100

struct dossier{
    int disponible;
    char *num_dossier;
    char *nom;
    char *prenom;
};
typedef struct dossier Dossier;

struct arg{
    int client_socket;
    Dossier *monensemblededossier;
};
typedef struct arg D_argy;

#endif