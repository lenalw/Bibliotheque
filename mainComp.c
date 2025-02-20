#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>  
#include "biblioLC.h"
#include "entreeSortieLC.h"
#include "biblioH.h"
#include "entreeSortieH.h"

int main(int argc, char *argv[]) {
    // Vérifier si un fichier a été passé en argument
    if (argc < 2) {
        printf("Erreur : Il faut fournir un fichier en argument.\n");
        return 1; 
    }

    
    char *fichier = argv[1];  
    printf("Chargement du fichier : %s\n", fichier);

    
    clock_t start, end;
    double cpu_time_used;


    Biblio *b = charger_n_entrees(fichier, 1000);  
    BiblioH *bH = charger_n_entreesH(fichier, 1000);  

    // Recherche dans la liste chaînée par auteur*
    printf("=============================================\n");
    start = clock();
    Biblio *b1 = recherche_aut("o",b);
    if (b1 == NULL){ printf("Le livre n'existe pas\n"); }
    else {afficher_bibli(b1);}
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Temps recherche par auteur (liste chaînée): %f secondes\n", cpu_time_used);

    // Recherche dans la table de hachage par auteur
    start = clock();
    BiblioH *bH1 = recherche_autH("o", bH);
     if (bH1 == NULL){ printf("Le livre n'existe pas\n"); }
    else {afficher_bibliH(bH1);}
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Temps recherche par auteur (table de hachage): %f secondes\n", cpu_time_used);

    // Recherche dans la liste chaînée par titre
    printf("=============================================\n");
    start = clock();
    Livre *l_lc2 = recherche_titre("haha", b);
    if (l_lc2 == NULL){ printf("Le livre n'existe pas\n");}
    else {afficher_livre(l_lc2);}
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Temps recherche par titre (liste chaînée): %f secondes\n", cpu_time_used);

    // Recherche dans la table de hachage par titre
    start = clock();
    LivreH *l_h2 = recherche_titreH("haha", bH);
     if (l_h2 == NULL){ printf("Le livre n'existe pas\n");}
    else {afficher_livreH(l_h2);}
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Temps recherche par titre (table de hachage): %f secondes\n", cpu_time_used);

    // Recherche dans la liste chaînée par numéro
    printf("=============================================\n");
    start = clock();
    Livre *l_lc3 = recherche_num(61, b);
    if (l_lc3 == NULL){ printf("Le livre n'existe pas\n");}
    else {afficher_livre(l_lc3);}
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Temps recherche par numéro (liste chaînée): %f secondes\n", cpu_time_used);

    // Recherche dans la table de hachage par numéro
    start = clock();
    LivreH *l_h3 = recherche_numH(61, bH);
    if (l_h3 == NULL){ printf("Le livre n'existe pas\n");}
    else {afficher_livreH(l_h3);}
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Temps recherche par numéro (table de hachage): %f secondes\n", cpu_time_used);
    
    return 0;
    
    
}
