#include "entreeSortieLC.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Biblio* charger_n_entrees(char* nomfic, int n) {
    Biblio* b = creer_biblio();
    if (!b) return NULL;  

    FILE* f = fopen(nomfic, "r");
    if (!f) {
        fprintf(stderr, "Erreur : impossible de lire dans le fichier %s.\n", nomfic);
        liberer_biblio(b);  
        return NULL;
    }

    int num; 
    char titre[256], auteur[256];

    for (int i = 0; i < n && fscanf(f, "%d %s %s", &num, titre, auteur) == 3; i++) {
        inserer_en_tete(b, num, strdup(titre), strdup(auteur));  
    }

    fclose(f);
    return b;
}

void enregistrer_biblio(Biblio *b, char* nomfic) {
    if (!b || !b->L) {
        fprintf(stderr, "Erreur : bibliothèque vide ou inexistante.\n");
        return;
    }

    FILE *f = fopen(nomfic, "w");
    if (!f) {
        fprintf(stderr, "Erreur : impossible d'écrire dans le fichier %s.\n", nomfic);
        return;
    }

    Livre* l = b->L;
    while (l) {
        fprintf(f, "%d %s %s\n", l->num, l->titre, l->auteur);
        l = l->suiv;
    }  
    fclose(f);
}


