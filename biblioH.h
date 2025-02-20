#ifndef BIBLIOH_H
#define BIBLIOH_H

#include <stdlib.h>
#include <stdio.h>


typedef struct livreh{
    int clef ;
    int num;
    char * titre ;
    char * auteur ;
    struct livreh *suivant ;
} LivreH ;

typedef struct table{
    int nE ; 
    int m ; 
    LivreH **T;
} BiblioH;

int fonctionClefH(char* auteur);
int fonctionHachageH(int cle, int m);

LivreH* creer_livreH(int num,char* titre,char* auteur);
void liberer_livreH(LivreH* l);

BiblioH* creer_biblioH(int m);
void liberer_biblioH(BiblioH* b);
void inserer(BiblioH* b,int num,char* titre,char* auteur);
void afficher_livreH(LivreH *l);
void afficher_bibliH(BiblioH *b);
LivreH *recherche_numH(int num, BiblioH *b);
LivreH *recherche_titreH(char * titre, BiblioH *b);
BiblioH *recherche_autH(char * auteur, BiblioH *b);
void supp_ouvrageH(BiblioH *b, int num, char * auteur, char * titre);
BiblioH *fusionH(BiblioH *b1, BiblioH *b2);
BiblioH *recherche_exemplairesH(BiblioH *b);

#endif