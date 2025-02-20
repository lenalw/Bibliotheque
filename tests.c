#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "biblioH.h"
#include "biblioLC.h"
#include "entreeSortieH.h"
#include "entreeSortieLC.h"

#define NB_TESTS 7

void sauvegarder_temps_csv(const char *nom_fichier, int taille_biblio, double temps_LC, double temps_H) {
    FILE *fichier = fopen(nom_fichier, "a");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    fprintf(fichier, "%d,%.6f,%.6f\n", taille_biblio, temps_LC, temps_H);
    fclose(fichier);
}

int main() {
    const char *fichiers_csv[] = {"temps_recherche_exemplaires.csv", "temps_recherche_num.csv", "temps_recherche_titre.csv","temps_recherche_auteur.csv" };

    for (int i = 0; i < 4; i++) {
        FILE *fichier = fopen(fichiers_csv[i], "w");
        if (fichier == NULL) {
            perror("Erreur lors de la création du fichier CSV");
            return 1;
        }
        fprintf(fichier, "Taille_Bibliotheque,Temps_Liste,Temps_Hachage\n");
        fclose(fichier);
    }

    int tailles[] = {1000, 2000, 4000, 8000, 16000, 32000, 50000};

    for (int i = 0; i < NB_TESTS; i++) {
        int n = tailles[i];

        Biblio *b = charger_n_entrees("GdeBiblio.txt", n);
        BiblioH *bH = charger_n_entreesH("GdeBiblio.txt", n);

        if (!b || !bH) {
            printf("Erreur d'allocation mémoire pour la bibliothèque\n");
            return 1;
        }

        clock_t start, end;
        double temps_LC, temps_H;


        // Recherche des exemplaires
        start = clock();
        recherche_exemplaires(b);
        end = clock();
        temps_LC = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        recherche_exemplairesH(bH);
        end = clock();
        temps_H = (double)(end - start) / CLOCKS_PER_SEC;

        sauvegarder_temps_csv("temps_recherche_exemplaires.csv", n, temps_LC, temps_H);


        // Recherche par numéro
        start = clock();
        recherche_num(12345, b);
        end = clock();
        temps_LC = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        recherche_numH(12345, bH);
        end = clock();
        temps_H = (double)(end - start) / CLOCKS_PER_SEC;

        sauvegarder_temps_csv("temps_recherche_num.csv", n, temps_LC, temps_H);


        // Recherche par titre
        start = clock();
        recherche_titre("TitreTest", b);
        end = clock();
        temps_LC = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        recherche_titreH("TitreTest", bH);
        end = clock();
        temps_H = (double)(end - start) / CLOCKS_PER_SEC;

        sauvegarder_temps_csv("temps_recherche_titre.csv", n, temps_LC, temps_H);


        // Recherche par auteur
        start = clock();
        recherche_aut("AuteurTest", b);
        end = clock();
        temps_LC = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        recherche_autH("AuteurTest", bH);
        end = clock();
        temps_H = (double)(end - start) / CLOCKS_PER_SEC;

        sauvegarder_temps_csv("temps_recherche_auteur.csv", n, temps_LC, temps_H);
    }

    printf("Les données ont été sauvegardées.\n");

    return 0;
}
