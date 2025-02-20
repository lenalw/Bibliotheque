#ifndef BIBLIOLC_H
#define BIBLIOLC_H

#include <stdlib.h>
#include <stdio.h>


typedef struct livre{
    int num ;
    char * titre ;
    char * auteur ;
    struct livre * suiv ; 
} Livre ;

typedef struct Livre{ /* Tete fictive */
    Livre * L ; /* Premier element */ 
}Biblio ;

Livre* creer_livre(int num,char* titre,char* auteur);
void liberer_livre(Livre* l);
Biblio* creer_biblio();
void liberer_biblio(Biblio* b);
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur);
void afficher_livre(Livre *l);


void afficher_bibli(Biblio *b);
Livre *recherche_num(int num, Biblio *b);
Livre *recherche_titre(char * titre, Biblio *b);
Biblio *recherche_aut(char * auteur, Biblio *b);
Biblio *supp_ouvrage(int num, char * auteur, char * titre, Biblio *b);
Biblio *fusion(Biblio *b1, Biblio *b2);
Biblio* recherche_exemplaires(Biblio *b);

#endif