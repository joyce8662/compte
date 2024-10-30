#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// Structure pour les clients
typedef struct Client {
    int idClient;
    char nom[100];
    char prenom[100];
    struct Client* suivant;
} Client;

// Structure pour les comptes bancaires
typedef struct CompteBancaire {
    int numCompte;
    float solde;
    Client *titulaire;
    struct CompteBancaire* suivant;
} CompteBancaire;

// Prototypes des fonctions pour la gestion des operations
void creerCompte(CompteBancaire *compte, Client *client);
void deposerArgent(CompteBancaire *compte, float montant);
void retirerArgent(CompteBancaire *compte, float montant);
void afficherCompte(CompteBancaire compte);
void sauvegarderClients(Client* listeClients);

// Prototype des fonctions pour la gestion des clients
Client* ajouterClient(Client** listeClients, int idClient, char* nom, char* prenom);
Client* trouverClient(Client* listeClients, int idClient);
void modifierClient(Client* client, char* nom, char* prenom);
void supprimerClient(Client** listeClients, int idClient);
void afficherClients(Client* listeClients);
void sauvegarderComptes(CompteBancaire* listeComptes);
void chargerComptes(CompteBancaire** listeComptes, Client* listeClients);
CompteBancaire* trouverCompte(CompteBancaire* listeComptes, int numCompte);
void chargerClients(Client** listeClients);

int main(){
    // Initialisation des listes de clients et de comptes
    Client* listeClients = NULL;
    CompteBancaire* listeComptes = NULL;

    CompteBancaire compte;
    Client* clientTrouve;
    int choix;
    int  numCompte;
    CompteBancaire* compteTrouve = NULL;
    float montant;
    int idClient;
    char nom[100],prenom[100];
    Client* clientTemp;

    // Charger les données au démarrage
    chargerClients(&listeClients); // Charge d'abord tous les clients
   chargerComptes(&listeComptes, listeClients); // Ensuite, charge les comptes en associant les clients correspondants

   do{

        printf("*BONJOUR CHER(S) CLIENT, BIENVENU DANS VOTRE BANQUE $TAPTAP SEND$,QUELLE OPERATION SOUHAITEZ VOUS REALISEZ DANS CE MENU*\n");
        printf("\n******** Menu Gestion Banque ************\n");
        printf("**    1. Ajouter client                 **\n");
        printf("**    2. Modifier client                **\n");
        printf("**    3. Supprimer client               **\n");
        printf("**    4. Afficher clients               **\n");
        printf("**    5. Creer compte                   **\n");
        printf("**    6. Deposer argent                 **\n");
        printf("**    7. Retirer argent                 **\n");
        printf("**    8. Afficher informations du compte **\n");
        printf("**    9. Rechercher client par ID        **\n");
        printf("**    10.Rechercher compte par numéro    **\n");
        printf("**    11. Quitter                        **\n");
        printf("\n*****************************************\n");
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                printf("ID Client: ");
                scanf("%d", &idClient);
                printf("Nom: ");
                scanf("%s", nom);
                printf("Prenom: ");
                scanf("%s", prenom);
                ajouterClient(&listeClients, idClient, nom, prenom);
                sauvegarderClients(listeClients);
                break;
            case 2:
                printf("ID Client a modifier: ");
                scanf("%d", &idClient);
                clientTemp = trouverClient(listeClients, idClient);
                if(clientTemp == NULL) {
                    printf("Client introuvable!\n");
                    break;
                }
                printf("Nouveau Nom: ");
                scanf("%s", nom);
                printf("Nouveau Prenom: ");
                scanf("%s", prenom);
                modifierClient(clientTemp, nom, prenom);
                sauvegarderClients(listeClients);
                break;
            case 3:
                printf("ID Client a supprimer: ");
                scanf("%d", &idClient);
                supprimerClient(&listeClients, idClient);
                sauvegarderClients(listeClients);
                break;
            case 4:
                afficherClients(listeClients);
                break;
            case 5:
                printf("ID Client pour le compte: ");
                scanf("%d", &idClient);
                clientTemp = trouverClient(listeClients, idClient);
                if(clientTemp == NULL) {
                    printf("Client introuvable!\n");
                    break;
                }
                 creerCompte(&compte, clientTemp);
                 sauvegarderComptes(listeComptes);
                break;
            case 6:
                printf("Montant a deposer: ");
                scanf("%f", &montant);
                deposerArgent(&compte, montant);
                sauvegarderComptes(listeComptes);
                break;
            case 7:
                printf("Montant a retirer: ");
                scanf("%f", &montant);
                retirerArgent(&compte, montant);
                sauvegarderComptes(listeComptes);
                break;
            case 8:
                afficherCompte(compte);
                break;

            case 9:
                printf("Entrez l'ID du client à rechercher: ");
                scanf("%d", &idClient);
                clientTrouve = trouverClient(listeClients, idClient);
                if(clientTrouve != NULL) {
                    printf("Client trouvé: %s %s\n", clientTrouve->nom, clientTrouve->prenom);
                } else {
                    printf("Client non trouvé.\n");
                }
                break;
            case 10:
                printf("Entrez le numéro de compte à rechercher: ");
                scanf("%d", &numCompte);
                compteTrouve = trouverCompte(listeComptes, numCompte); // Assurez-vous d'avoir cette fonction
                if(compteTrouve != NULL) {
                    printf("Compte trouvé: %d, Titulaire: %s %s, Solde: %.2f\n",
                        compteTrouve->numCompte,
                        compteTrouve->titulaire->nom,
                        compteTrouve->titulaire->prenom,
                        compteTrouve->solde);
                } else {
                    printf("Compte non trouvé.\n");
                }
                break;
           case 11:
                printf("Sauvegarde et fermeture en cours...\n");
                sauvegarderClients(listeClients); // Optionnel si vous voulez sauvegarder avant de quitter
                sauvegarderComptes(listeComptes); // Optionnel aussi

                // Libération de la mémoire pour les clients et les comptes
                Client* clientTemp;
                while(listeClients != NULL) {
                    clientTemp = listeClients;
                    listeClients = listeClients->suivant;
                    free(clientTemp);
                }

                CompteBancaire* compteTemp;
                while(listeComptes != NULL) {
                    compteTemp = listeComptes;
                    listeComptes = listeComptes->suivant;
                    free(compteTemp);
                }

                printf("Application fermée.\n");
                return 0; // Sort de la boucle et termine le programme
        }
    } while(choix != 11);

    return 0; // Cette ligne ne sera jamais atteinte
}

// Les fonctions pour la gestion des comptes et operations (creerCompte, deposerArgent, retirerArgent, afficherCompte)

// Fonction pour créer un compte avec un client associé
void creerCompte(CompteBancaire *compte, Client *client) {
    static int dernierNumCompte = 1000; // Un simple générateur de numéros de compte`

    if (client == NULL) {
        printf("Client non spécifié pour le compte.\n");
        return;
    }
    compte->titulaire = client; // Associe le client au compte
    compte->numCompte = ++dernierNumCompte; // Génère un nouveau numéro de compte
    compte->solde = 0; // Initialise le solde à 0
    printf("Compte créé pour %s %s avec succès. Numéro de compte: %d\n", client->nom, client->prenom, compte->numCompte);
}

void deposerArgent(CompteBancaire *compte, float montant) {
    compte->solde += montant;
    printf("Depot reussi. Nouveau solde: %.2f\n", compte->solde);
}

void retirerArgent(CompteBancaire *compte, float montant) {
    if(montant > compte->solde) {
        printf("Fonds insuffisants!\n");
    } else {
        compte->solde -= montant;
        printf("Retrait reussi. Nouveau solde: %.2f\n", compte->solde);
    }
}

void afficherCompte(CompteBancaire compte) {
    printf("\nInformations du compte:\n");
    printf("Numero de compte: %d\n", compte.numCompte);
    printf("Nom du titulaire: %s\n", compte.titulaire->nom); // Accès via pointeur
    printf("Prenom du titulaire: %s\n", compte.titulaire->prenom); // Ajouté pour cohérence
    printf("Solde: %.2f\n", compte.solde);
}


// Les fonctions pour la gestion des clients (ajouter, trouver, modifier, supprimer, afficher)

// Fonction pour ajouter un client à la liste

Client* ajouterClient(Client** listeClients, int idClient, char* nom, char* prenom) {
    Client* nouveauClient = (Client*)malloc(sizeof(Client));
    if (nouveauClient == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return NULL;
    }
    nouveauClient->idClient = idClient;
    strcpy(nouveauClient->nom, nom);
    strcpy(nouveauClient->prenom, prenom);
    nouveauClient->suivant = *listeClients;
    *listeClients = nouveauClient;
    printf("Client ajouté avec succès.\n");
    return nouveauClient;
}

// Fonction pour trouver un client par ID

Client* trouverClient(Client* listeClients, int idClient) {
    Client* actuel = listeClients;
    while (actuel != NULL) {
        if (actuel->idClient == idClient) {
            return actuel;
        }
        actuel = actuel->suivant;
    }
    return NULL; // Client non trouvé
}

// Fonction pour modifier les informations d'un client

void modifierClient(Client* client, char* nom, char* prenom) {
    if (client == NULL) {
        printf("Client introuvable.\n");
        return;
    }
    strcpy(client->nom, nom);
    strcpy(client->prenom, prenom);
    printf("Client modifié avec succès.\n");
}

// Fonction pour supprimer un client de la liste

void supprimerClient(Client** listeClients, int idClient) {
    Client* actuel = *listeClients;
    Client* precedent = NULL;
    while (actuel != NULL && actuel->idClient != idClient) {
        precedent = actuel;
        actuel = actuel->suivant;
    }
    if (actuel == NULL) {
        printf("Client introuvable.\n");
        return;
    }
    if (precedent == NULL) {
        *listeClients = actuel->suivant; // Le client à supprimer est le premier de la liste
    } else {
        precedent->suivant = actuel->suivant; // Supprimer le client de la liste
    }
    free(actuel);
    printf("Client supprimé avec succès.\n");
}

// Fonction pour afficher tous les clients

void afficherClients(Client* listeClients) {
    Client* actuel = listeClients;
    if (actuel == NULL) {
        printf("Aucun client à afficher.\n");
        return;
    }
    while (actuel != NULL) {
        printf("ID: %d, Nom: %s, Prenom: %s\n", actuel->idClient, actuel->nom, actuel->prenom);
        actuel = actuel->suivant;
    }
}

CompteBancaire* trouverCompte(CompteBancaire* listeComptes, int numCompte) {
    CompteBancaire* actuel = listeComptes;
    while (actuel != NULL) {
        if (actuel->numCompte == numCompte) {
            return actuel;
        }
        actuel = actuel->suivant; // Supposons que vous avez un pointeur 'suivant' dans votre structure de CompteBancaire
    }
    return NULL; // Compte non trouvé
}

void sauvegarderClients(Client* listeClients) {
    FILE* fichier = fopen("clients.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour écriture.\n");
        return;
    }

    Client* actuel = listeClients;
    while (actuel != NULL) {
        // Écrire les données du client dans le fichier
        fprintf(fichier, "%d %s %s\n", actuel->idClient, actuel->nom, actuel->prenom);
        actuel = actuel->suivant; // Passer au client suivant dans la liste
    }

    fclose(fichier); // Ne pas oublier de fermer le fichier
    printf("Tous les clients ont été sauvegardés avec succès.\n");
}

void chargerClients(Client** listeClients) {
    FILE* fichier = fopen("clients.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    int idClient;
    char nom[100];
    char prenom[100];
    while (fscanf(fichier, "%d %s %s", &idClient, nom, prenom) != EOF) {
        Client* nouveauClient = (Client*)malloc(sizeof(Client));
        if (nouveauClient == NULL) {
            printf("Erreur d'allocation mémoire.\n");
            break;
        }
        nouveauClient->idClient = idClient;
        strcpy(nouveauClient->nom, nom);
        strcpy(nouveauClient->prenom, prenom);
        nouveauClient->suivant = *listeClients; // Ajoute le nouveau client en tête de liste
        *listeClients = nouveauClient;
    }
    fclose(fichier);
}
void sauvegarderComptes(CompteBancaire* tete) {
    FILE* fichier = fopen("comptes.txt", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    CompteBancaire* courant = tete;
    while (courant != NULL) {
        // Assurez-vous que courant->titulaire n'est pas NULL avant d'accéder à idClient
        if (courant->titulaire != NULL) {
            fprintf(fichier, "%d %f %d\n", courant->numCompte, courant->solde, courant->titulaire->idClient);
        }
        courant = courant->suivant;
    }
    fclose(fichier);
}

void chargerComptes(CompteBancaire** tete, Client* listeClients) {
    FILE* fichier = fopen("comptes.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    int numCompte;
    float solde;
    int idClient;
    while (fscanf(fichier, "%d %f %d\n", &numCompte, &solde, &idClient) != EOF) {
        CompteBancaire* nouveauCompte = (CompteBancaire*)malloc(sizeof(CompteBancaire));
        if (nouveauCompte == NULL) {
            printf("Erreur d'allocation mémoire.\n");
            break;
        }
        nouveauCompte->numCompte = numCompte;
        nouveauCompte->solde = solde;
        // Trouvez le client dans listeClients qui correspond à idClient et assignez-le à nouveauCompte->titulaire
        Client* clientTrouve = trouverClient(listeClients, idClient);
        nouveauCompte->titulaire = clientTrouve; // Cela peut être NULL si aucun client correspondant n'est trouvé
        nouveauCompte->suivant = *tete;
        *tete = nouveauCompte;
    }
    fclose(fichier);
}
