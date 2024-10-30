#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// Structure pour les comptes bancaires
typedef struct {
    int numCompte;
    char nomTitulaire[100];
    float solde;
} CompteBancaire;

// Structure pour les clients
typedef struct Client {
    int idClient;
    char nom[100];
    char prenom[100];
    struct Client* suivant;
} Client;

// Prototypes des fonctions pour la gestion des operations
void creerCompte(CompteBancaire *compte);
void deposerArgent(CompteBancaire *compte, float montant);
void retirerArgent(CompteBancaire *compte, float montant);
void afficherCompte(CompteBancaire compte);

// Prototype des fonctions pour la gestion des clients
Client* ajouterClient(Client** listeClients, int idClient, char* nom, char* prenom);
Client* trouverClient(Client* listeClients, int idClient);
void modifierClient(Client* client, char* nom, char* prenom);
void supprimerClient(Client** listeClients, int idClient);
void afficherClients(Client* listeClients);

int main() {
    CompteBancaire compte;
    Client* listeClients = NULL;
    int choix;
    float montant;
    int idClient;
    char nom[100], prenom[100];
    Client* clientTemp;

    while(1) {
        printf("\n***** Menu Gestion Banque *****\n");
        printf("1. Ajouter client\n");
        printf("2. Modifier client\n");
        printf("3. Supprimer client\n");
        printf("4. Afficher clients\n");
        printf("5. Creer compte\n");
        printf("6. Deposer argent\n");
        printf("7. Retirer argent\n");
        printf("8. Afficher informations du compte\n");
        printf("9. Quitter\n");
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
                break;
            case 3:
                printf("ID Client a supprimer: ");
                scanf("%d", &idClient);
                supprimerClient(&listeClients, idClient);
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
                break;
            case 6:
                printf("Montant a deposer: ");
                scanf("%f", &montant);
                deposerArgent(&compte, montant);
                break;
            case 7:
                printf("Montant a retirer: ");
                scanf("%f", &montant);
                retirerArgent(&compte, montant);
                break;
            case 8:
                afficherCompte(compte);
                break;
            case 9:
                // Libération de la mémoire et sortie
                while(listeClients != NULL) {
                    clientTemp = listeClients;
                    listeClients = listeClients->suivant;
                    free(clientTemp);
                }
                exit(0);
            default:
                printf("Choix invalide!\n");
        }
    }

    return 0;
}
// Les fonctions pour la gestion des comptes et operations (creerCompte, deposerArgent, retirerArgent, afficherCompte)

void creerCompte(CompteBancaire *compte) {
    printf("Numero de compte: ");
    scanf("%d", &compte->numCompte);
    printf("Nom du titulaire: ");
    scanf("%s", compte->nomTitulaire); // Attention : Utilisez fgets pour les chaînes avec espaces
    compte->solde = 0;
    printf("Compte cree avec succes!\n");
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
    printf("Nom du titulaire: %s\n", compte.nomTitulaire);
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

