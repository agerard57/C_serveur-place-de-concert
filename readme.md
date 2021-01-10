# PROJET SYSTEME

## Table des matières

- [Présentation](#pres)
- [Comment lancer l'application ?](#lancer)
  * [I. Lancer le serveur :](#i)
  * [II. Lancer le client :](#ii)
- [Comment utiliser l'application ?](#utiliser)
	* [Faire une réservation](#reserver)
	* [Annuler une réservation](#annuler)
	* [Quiter l'application](#quit)
- [ Les spécificités de l'application ?](#specs)
	* [Limite de dossier maximum](#limite)
	* [Création automatique et aléatoire des numéro de dossier](#dossier)
	* [Fichier de sauvgarde](#save)

## Présentation<a name="#pres"></a>
Il s'agit d'une application de réservation de places de concert fait entièrement en C.
Le projet repose sur un système de communication entre un serveur et un ou des clients

___
## Comment lancer l'application?<a name="#lancer"></a>

### I. Lancer le serveur :<a name="#i"></a>
- Compilation du serveur : 
```console
root@monPC:~$ gcc -o serveur main.c -lpthread
```

> :warning: **Lors de la compilation** : Il ne faut pas oublier l'option **`-lpthread`**!


- Lancement du serveur :
```console
root@monPC:~$ gcc ./serveur
```

### II. Lancer le client :<a name="#ii"></a>
- Compilation du client : 
```console
root@monPC:~$ gcc -o client main.c
```

- Lancement du client:
```console
root@monPC:~$ gcc ./client
```
## Comment utiliser l'application ?<a name="utiliser"></a>
Une fois les deux pages (serveur et client) lancés en même temps sur deux terminaux différents, il faut établir la communication entre les deux.
Pour cela, il faudra renseigner au client l'adresse du serveur, qui est affiché sur la page :
|Fenêtre SERVEUR  | Fenêtre CLIENT |
|--|--|
|![image](https://user-images.githubusercontent.com/56207146/104113428-f70b9d80-52f9-11eb-9887-48582843f82d.png)  |  ![image](https://user-images.githubusercontent.com/56207146/104113445-1b677a00-52fa-11eb-8da4-75a0712130eb.png)|

Dès lors, la page principale du client s'affichera : 

![image](https://user-images.githubusercontent.com/56207146/104113535-edcf0080-52fa-11eb-90d5-8a64a944b6d9.png)

De là, trois options s'offrent à nous :
___
 1. Faire une réservation
 2. Annuler une réservation
 3. Quitter l'application
 ___
Le menu est très intuitif et les 3 choix sont assez explicites à l'utilisateur.

### Faire une réservation<a name="reserver"></a>

Cette fenêtre permet d'ajouter simplement un dossier, en renseignant juste le **nom** ainsi que le **prénom** du client: un numéro de client sera alors généré aléatoirement.

![image](https://user-images.githubusercontent.com/56207146/104113671-1a374c80-52fc-11eb-9f11-4ffcbbe45d4c.png)

Quand la réservation est confirmée, le serveur en reçoit la notification dans la partie "*Actions...*"

![image](https://user-images.githubusercontent.com/56207146/104113710-5b2f6100-52fc-11eb-816c-2c7376d7ea0c.png)
> :exclamation: **Attention** : La création de dossiers sera impossible dans le cas ou il n'y a plus de place disponible !

### Annuler une réservation<a name="annuler"></a>

Cette fenêtre permet d'annuler n'importe quel dossier enregistré en utilisant le **nom** et le **numéro de dossier**

![image](https://user-images.githubusercontent.com/56207146/104113796-72bb1980-52fd-11eb-8531-92c5d840d6e6.png)

Le serveur vous confirmera aussi la suppression du dossier :

![image](https://user-images.githubusercontent.com/56207146/104113794-7189ec80-52fd-11eb-8d15-d1f0f79f5f71.png)

> :exclamation: **Attention** : Si une des informations entrées sont erronés ou n'existent pas, un message préviendra de l'échec de l'opération
![image](https://user-images.githubusercontent.com/56207146/104113797-7353b000-52fd-11eb-9a1d-b3501e40efc0.png)

> 
### Quiter l'application<a name="quit"></a>
Quitter vous affichera une page qui vous souhaite une bonne journée, voilà tout :smiley:

![image](https://user-images.githubusercontent.com/56207146/104113873-62576e80-52fe-11eb-88be-013aa52077ab.png)

Le programme s'arrêtera complétement à la pression de la touche **"entrée"** et stoppera aussitôt la connexion.

## Les spécificités de l'application ?<a name="specs"></a>

Cette partie est dédiée à quelques fonctionnalités qui méritent leur propre partie;

 ### Limite de dossier maximum<a name="limite"></a>
 
 Dans le fichier [*dsServeur/header.h*](https://github.com/agerard57/PROJET_SYSTEME/blob/master/dsServeur/header.h) du projet, la ligne ci-dessous définit le nombre maximum de clients avant de retourner une erreur (100 dans notre cas).
 ___
 ```c
#define NB_DOSSIER 100
 ```
 
 >[Lien de la ligne](https://github.com/agerard57/PROJET_SYSTEME/blob/602d5db3aca87086b7011d6337b5c1c69eb04bae/dsServeur/header.h#L17)
 >Ligne de code représentant le nombre de dossiers maximum
 
___

 ```c
write(param -> client_socket, "Toutes les réservations sont prises !", 128);
 ```
 
>[Lien de la ligne](https://github.com/agerard57/PROJET_SYSTEME/blob/602d5db3aca87086b7011d6337b5c1c69eb04bae/dsServeur/main.c#L51)
>Ligne de code du cas "Toutes les réservations sont prises"
___

 ### Création automatique et aléatoire des numéro de dossier<a name="dossier"></a>

 
 Dans un souci d'efficacité, nous avons décidés de générer aléatoirement les numéros de dossier à la réservation. 
 
```c
c = 0;

while (c < 10) { //Génération aléatoire d'un numéro de dossier
	num_dossier[c] = '0' + (rand() % 10);
	c++;
}
```
>[Lien des lignes](https://github.com/agerard57/PROJET_SYSTEME/blob/602d5db3aca87086b7011d6337b5c1c69eb04bae/dsServeur/main.c#L59)

### Fichier de sauvgarde<a name="save"></a>

Les dossiers sont tous stockés dans le fichier texte [*dsServeur/save.txt*], ce qui permet de sauvgarder les clients voulant s'inscrire, et cela, même après arrêt du serveur... (https://github.com/agerard57/PROJET_SYSTEME/blob/master/dsServeur/save.txt)


___

***GERARD Alexandre / GIANGRECO Vincent***

*Semestre 3
2020-2021 - IUT Informatique*

