#include <stdio.h>
#include <stdlib.h>
#include<stdio.h>
#include<stdlib.h>

// Structure pour les comptes bancaires
typedef struct {
    int numCompte;
    char nomTitulaire[100];
    float solde;
} CompteBancaire;

// Prototypes des fonctions
void creerCompte(CompteBancaire *compte);
void deposerArgent(CompteBancaire *compte, float montant);
void retirerArgent(CompteBancaire *compte, float montant);
void afficherCompte(CompteBancaire compte);

int main() {
    CompteBancaire compte;
    int choix;
    float montant;

    while(1) {
        printf("\n***** Menu Gestion Banque *****\n");
        printf("1. Creer compte\n");
        printf("2. Deposer argent\n");
        printf("3. Retirer argent\n");
        printf("4. Afficher informations du compte\n");
        printf("5. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                creerCompte(&compte);
                break;
            case 2:
                printf("Montant a deposer: ");
                scanf("%f", &montant);
                deposerArgent(&compte, montant);
                break;
            case 3:
                printf("Montant a retirer: ");
                scanf("%f", &montant);
                retirerArgent(&compte, montant);
                break;
            case 4:
                afficherCompte(compte);
                break;
            case 5:
                exit(0);
            default:
                printf("Choix invalide!\n");
        }
    }

    return 0;
}

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



