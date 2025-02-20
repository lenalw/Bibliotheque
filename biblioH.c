#include "biblioH.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int fonctionClef(char* auteur){
    int res = 0;
    for (int i = 0; auteur[i] != '\0'; i++){
        res+=(int)(auteur[i]);
    }
    return res;
}

LivreH* creer_livreH(int num,char* titre,char* auteur){
    LivreH *l = (LivreH *)malloc(sizeof(LivreH));
    assert(l);
    l->clef = fonctionClef(auteur);
    l->num = num;
    l->titre = strdup(titre);
    l->auteur = strdup(auteur);
    l->suivant = NULL;

    return l;
}

void liberer_livreH(LivreH* l){
    if (!l) return;

    free(l->titre);
    free(l->auteur);
    free(l);
}


BiblioH* creer_biblioH(int m){
    if (m <= 0) {
        fprintf(stderr, "Erreur: Taille invalide pour la table de hachage.\n");
        return NULL;
    }

    BiblioH *b = (BiblioH *)malloc(sizeof(BiblioH));
    assert(b);

    b->T = (LivreH**)malloc((size_t)m * sizeof(LivreH*));
    assert(b->T);

    for (int i = 0; i < m; i++) b->T[i] = NULL;

    b->nE = 0;
    b->m = m;

    return b;
}


void liberer_biblioH(BiblioH* b){
    if (!b) return;

    for (int i = 0; i < b->m; i++) {
        LivreH *tmp = b->T[i];
    	while(tmp){
    	     LivreH *res= tmp;
    	     tmp = tmp->suivant;
    	     liberer_livreH(res);
    	} 
    }

    free(b->T);
    free(b);
}


int fonctionHachage(int cle, int m){
    double a = (sqrt(5.0)-1) / 2;
    int nb = (int)floor(cle * a);
    return (int)floor(m * (cle*a - nb)) % m; //modulo pour éviter les débordements
}

void inserer(BiblioH* b,int num,char* titre,char* auteur){
    if (b == NULL || b->T == NULL) return;

    int cle = fonctionClef(auteur);
    int pos = fonctionHachage(cle, b->m);

    LivreH* nv = creer_livreH(num, titre, auteur);
    if (!nv) return;

    nv->suivant = b->T[pos];
    b->T[pos] = nv;

    b->nE++;
}

void afficher_livreH(LivreH *l){
    if (l == NULL){
        return;
    } 
    printf("Livre numéro : %d, titre : %s, auteur : %s\n", l->num, l->titre, l->auteur);
}

void afficher_bibliH(BiblioH *b){
    if (!b) return ;
    LivreH **l = b->T;
    if ( !l ) return ;


    for(int i = 0; i < b->m; i++){
        LivreH *lst = l[i];
        while (lst != NULL) {
            afficher_livreH(lst);
            lst = lst->suivant;
        }
    }
}


LivreH *recherche_numH(int num, BiblioH *b){
    if (!b) return NULL;
   
    for(int i = 0; i < b->m; i++){
        LivreH *livre = b->T[i];
        while (livre != NULL) {
            if (livre->num == num){
                return livre;
            } 
            livre = livre->suivant;
        }
    }

    return NULL;
}


LivreH *recherche_titreH(char * titre, BiblioH *b){
    if (!b) return NULL;

    for(int i = 0; i < b->m; i++){
        LivreH *livre = b->T[i];
        while (livre != NULL) {
            if (strcmp(livre->titre, titre) == 0 ){
                return livre;
            } 
            livre = livre->suivant;
        }
    }
    
    return NULL;
}

BiblioH *recherche_autH(char * auteur, BiblioH *b){
    if (!b) return NULL;
    
    BiblioH *res = NULL;
    int cle = fonctionClef(auteur);
    int i = fonctionHachage(cle, b->m);
    LivreH *l = b->T[i];
    
    if (l) {
        while(l){
            if(strcmp(l->auteur, auteur) == 0){
                if(!res){
                    res = creer_biblioH(1);
                }
                inserer(res, l->num, l->titre, l->auteur);
            }
    	l = l->suivant;
        }
    }

    return res;
}

void supp_ouvrageH(BiblioH *b, int num, char * auteur, char * titre){
	if (!b) return;
	
	int clef = fonctionClef(auteur);
	int i = fonctionHachage(clef, b->m);
	
	LivreH *l= b->T[i];
	
	if( l && (l->num == num) && (strcmp(l->titre,titre)==0) && (strcmp(l->auteur,auteur)==0)){  //si c'est le premier element
		b->T[i] = l->suivant; 
		liberer_livreH(l); 
        return;
	}

	LivreH *tmp;
	while(l){
		tmp = l->suivant;
		
		if(tmp && tmp->num == num && strcmp(tmp->titre,titre)==0 && strcmp(tmp->auteur,auteur)==0){
			l->suivant = tmp->suivant;
			liberer_livreH(tmp);
            return ;
		}

		l = l->suivant;
	}
}


BiblioH *fusionH(BiblioH *b1, BiblioH *b2){
    if ( !b1 || !b2 ) return NULL;

	for(int i =0; i< b2->m; i++){
	    LivreH *l = b2->T[i];
			
		while(l){
            inserer(b1, l->num, l->titre, l->auteur);
			l = l->suivant; 
		}
    }
		
	liberer_biblioH(b2);
    b2 = NULL;	
	return b1;

}

//la fonction renvoie que les exemplaires d'un ouvrage, pas l'ouvrage en question
BiblioH *recherche_exemplairesH(BiblioH *b) {
    if (b == NULL || b->T == NULL) return NULL;

    BiblioH *res = creer_biblioH(b->m);
    assert(res); 

    for(int i = 0; i < b->m; i++){
        LivreH *l1 = b->T[i];
        
        while(l1!=NULL){
            LivreH *l2 = l1->suivant;
            while (l2 != NULL) {
                if (strcmp(l1->auteur, l2->auteur) == 0 && strcmp(l1->titre, l2->titre) == 0 && (l1->num != l2->num)) {
                    inserer(res, l2->num, l2->titre, l2->auteur);
                    break;
                }
                l2 = l2->suivant;
            }
            
            l1 = l1->suivant;
        }
    }

    return res;
}