#include "biblioLC.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

Livre* creer_livre(int num,char* titre,char* auteur){
    Livre *l = (Livre *)malloc(sizeof(Livre));
    assert(l);
    l->num = num;
    l->titre = strdup(titre);
    l->auteur = strdup(auteur);
    l->suiv = NULL;
    return l;
}

void liberer_livre(Livre* l){
    if (!l) return;
    free(l->titre);
    free(l->auteur);
    free(l);
}

Biblio* creer_biblio(){
    Biblio *b = (Biblio *)malloc(sizeof(Biblio));
    assert(b);
    b->L = NULL;
    return b;
}

void liberer_biblio(Biblio* b){
    assert(b);
    Livre *cour = b->L;

    while (cour != NULL){
        Livre *suiv = cour->suiv;
        liberer_livre(cour);
        cour = suiv;
    }

    free(b);
}

void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur){
    if (!b) return;

    Livre *l = creer_livre(num, titre, auteur);

    if (l != NULL){
        l->suiv = b->L;
        b->L = l;
    }
}

void afficher_livre(Livre *l){
    if (!l || !l->titre || !l->auteur) {
        printf("Erreur : livre invalide.\n");
        return;
    }
    printf("Livre numéro : %d, titre : %s, auteur : %s\n", l->num, l->titre, l->auteur);
}

void afficher_bibli(Biblio *b){
    if (b == NULL){
        return ;
    } 
    Livre *courant = b->L;
    while (courant != NULL) {
        afficher_livre(courant);
        courant = courant->suiv;
    }
}


Livre *recherche_num(int num, Biblio *b){
    Livre *courant = b->L;
    while (courant != NULL) {
        if (courant->num == num) return courant;
        courant = courant->suiv;
    }
    return NULL;
}

Livre *recherche_titre(char * titre, Biblio *b){
    Livre *courant = b->L;
    while (courant != NULL) {
        if (strcmp(courant->titre, titre) == 0) return courant;
        courant = courant->suiv;
    }
    return NULL;
}

Biblio *recherche_aut(char * auteur, Biblio *b){
    Biblio *nv = creer_biblio();
    if (nv == NULL){
        return NULL;
    } 
    Livre *courant = b->L;
    while(courant != NULL){
        if (strcmp(courant->auteur, auteur) == 0){
            inserer_en_tete(nv, courant->num, courant->titre, courant->auteur);
        }
        courant = courant->suiv; 
    }
    return nv;
}


Biblio* supp_ouvrage(int num, char *auteur, char *titre, Biblio *b) {
    if (!b || !b->L) return b;

    Livre *actu = b->L;

    if ((actu->num == num) && (strcmp(actu->auteur, auteur) == 0) && (strcmp(actu->titre, titre) == 0)) {
        b->L = actu->suiv; 
        liberer_livre(actu); 
        return b;
    }

    while (actu != NULL && actu->suiv != NULL) {
        if ((actu->suiv->num == num) &&
            (strcmp(actu->suiv->auteur, auteur) == 0) &&
            (strcmp(actu->suiv->titre, titre) == 0)) {

            Livre *temp = actu->suiv;  
            actu->suiv = temp->suiv;   
            liberer_livre(temp);     
            return b;
        }
        actu = actu->suiv;
    }

    return b;
}



Biblio *fusion(Biblio *b1, Biblio *b2){
    if (! b1) return b2;
    if (! b2) return b1;

    Livre *courant = b1->L;

    if (courant == NULL) {
        b1->L = b2->L;
    } else {
        while (courant->suiv != NULL) {
            courant = courant->suiv;
        }
        courant->suiv = b2->L;
    }

    free(b2);
    return b1;
}

//la fonction renvoie que les exemplaires d'un ouvrage, pas l'ouvrage en question
Biblio* recherche_exemplaires(Biblio *b) {
    if (b == NULL || b->L == NULL) return creer_biblio();

    Biblio *res = creer_biblio();
    Livre *l1 = b->L;

    while (l1 != NULL) {
        Livre *l2 = l1->suiv;

        while (l2 != NULL) {
            if (strcmp(l1->auteur, l2->auteur) == 0 && strcmp(l1->titre, l2->titre) == 0 && (l1->num != l2->num)) {
                inserer_en_tete(res, l2->num, l2->titre, l2->auteur);
                break;
            }
            l2 = l2->suiv;
        }
        l1 = l1->suiv;
    }

    return res;
}

