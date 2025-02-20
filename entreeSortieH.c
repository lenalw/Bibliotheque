#include "entreeSortieH.h"
#include <stdlib.h>
#include <stdio.h>

BiblioH* charger_n_entreesH(char* nomfic, int n){
    BiblioH* b = creer_biblioH(100);
    FILE* f= fopen(nomfic, "r");
    if (!f) return NULL;

    int num; 
    char titre[256], auteur[256];
    for(int i=0; i < n && fscanf(f, "%d %s %s", &num, titre, auteur)==3; i++){
        
        inserer(b, num, titre, auteur);
	}
    
    fclose(f);    
    return b;
}

void enregistrer_biblioH(BiblioH *b, char* nomfic){

    FILE *f = fopen(nomfic, "w");
    if (!f) return;

    for(int i=0; i<b->m; i++){
   	    LivreH* l=  b->T[i];
    	while (l) {
            fprintf(f, "%d %d %s %s\n",l->clef, l->num, l->titre, l->auteur);
            l = l->suivant;
   	    }  
    }
    
    fclose(f);
}
