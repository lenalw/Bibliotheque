# bibliotheque
Gestion de bibliothèque
Ce projet implémente une gestion de bibliothèque avec deux structures de données principales pour le stockage des ouvrages :

    Liste chaînée (fichiers avec le préfixe “LC”)
    Table de hachage (fichiers avec le préfixe “H”)

L’objectif est de comparer les performances de recherche dans ces deux structures, de charger et sauvegarder des données, et de proposer une interface interactive.
Fichiers et Fonctions
1. Fichiers pour la Table de Hachage

    entreeSortieH.c
        charger_n_entreesH(char nomfic, int n)*
        Charge les n premiers ouvrages à partir d’un fichier dans une bibliothèque utilisant la table de hachage.
        enregistrer_biblioH(BiblioH b, char nomfic)
        Sauvegarde la bibliothèque (structure de hachage) dans un fichier.

2. Fichiers pour la Liste Chaînée

    biblioLC.h
        Définit la structure d’un ouvrage (Livre) avec ses champs (numéro, titre, auteur, pointeur vers l’ouvrage suivant) et la structure de la bibliothèque (Biblio) (tête de liste).
        Déclare les fonctions suivantes :
            creer_livre(int num, char titre, char auteur)** : Crée un nouvel ouvrage.
            liberer_livre(Livre l)* : Libère la mémoire allouée pour un ouvrage.
            creer_biblio() : Crée et initialise une nouvelle bibliothèque (liste chaînée).
            liberer_biblio(Biblio b)* : Libère l’ensemble des ouvrages d’une bibliothèque.
            inserer_en_tete(Biblio b, int num, char titre, char* auteur)** : Insère un ouvrage en tête de liste.

    entreeSortieLC.h
        Déclare les fonctions de gestion des entrées/sorties pour la bibliothèque en liste chaînée :
            charger_n_entrees(char nomfic, int n)* : Charge les n premiers ouvrages depuis un fichier.
            enregistrer_biblio(Biblio b, char nomfic)** : Enregistre la bibliothèque dans un fichier.

    entreeSortieLC.c
        Implémente charger_n_entrees : Ouvre le fichier, lit successivement les données (numéro, titre, auteur) et insère chaque ouvrage dans la liste.
        Implémente enregistrer_biblio : Parcourt la bibliothèque et écrit les informations dans un fichier.

    biblioLC.c
        Contient l’implémentation des fonctions déclarées dans biblioLC.h :
            Création, insertion et libération des ouvrages et de la bibliothèque.
            La fonction creer_livre alloue de la mémoire et duplique les chaînes de caractères.
            liberer_livre et liberer_biblio effectuent la désallocation.

3. Fichiers Communes et Interface

    main.c
        Fournit une interface interactive pour manipuler la bibliothèque.
        menu() : Affiche le menu principal avec les options telles que quitter, afficher la bibliothèque, insérer un ouvrage, rechercher par numéro ou par titre.
        La fonction main gère la boucle principale de l’application en appelant les fonctions correspondantes aux choix de l’utilisateur.

4. Comparaison et Tests de Performance

    mainComp.c
        Programme de test comparatif qui charge un fichier d’ouvrages et mesure les temps de recherche dans les deux structures (liste chaînée et table de hachage).
        Utilise des fonctions de chronométrage pour comparer l’efficacité des deux approches.

    tests.c
        Contient des fonctions de tests automatisés.
        *sauvegarder_temps_csv(const char nom_fichier, int taille_biblio, double temps_LC, double temps_H)
        Enregistre les temps mesurés pour chaque taille de bibliothèque dans un fichier CSV.
        Ce fichier permet d’effectuer plusieurs tests (NB_TESTS) et de tracer les courbes de performance.

Utilisation

    Compilation
    Compilez le projet grace à la commande make.

    Exécution
        Pour l’interface interactive, lancez l’exécutable généré par main.c.
        Pour les tests comparatifs, lancez l’exécutable généré par mainComp.c ou tests.c.
        Pour les graphes, lancez la commande python3 graphe.py

    Analyse des Performances
    Les tests génèrent un fichier CSV qui peut être utilisé pour tracer les courbes de temps de recherche en fonction de la taille de la bibliothèque.

Conclusion

Ce projet montre la différence de performance entre une liste chaînée et une table de hachage pour la gestion d’une bibliothèque. La structure en table de hachage offre des temps de recherche quasi constants (O(1) en moyenne) alors que la liste chaînée présente un temps linéaire (O(n)). Les différents modules du projet (chargement, sauvegarde, insertion, recherche et tests de performance) permettent de comparer ces approches et d’en tirer des conclusions quant à leur efficacité.
