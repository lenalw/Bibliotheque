import matplotlib.pyplot as plt

# Liste des fichiers CSV et des titres des graphiques
fichiers_csv = {
    "temps_recherche_exemplaires.csv": "Temps de Recherche des Exemplaires",
    "temps_recherche_num.csv": "Temps de Recherche par Numéro",
    "temps_recherche_titre.csv": "Temps de Recherche par Titre",
    "temps_recherche_auteur.csv": "Temps de Recherche par Auteur"
}

# Fonction pour lire un fichier CSV et extraire les données
def lire_csv(filename):
    n_values = []
    time_list = []
    time_hash = []
    
    with open(filename, "r") as f:
        next(f)  # Ignorer l'en-tête
        for line in f:
            values = line.strip().split(",")  # Séparer les colonnes
            n_values.append(int(values[0]))  # Taille de la bibliothèque
            time_list.append(float(values[1]) * 1000)  # Temps pour la liste chaînée (converti en ms)
            time_hash.append(float(values[2]) * 1000)  # Temps pour la table de hachage (converti en ms)
    
    return n_values, time_list, time_hash

# Boucle pour générer et afficher chaque graphique
for fichier, titre in fichiers_csv.items():
    n_values, time_list, time_hash = lire_csv(fichier)

    plt.figure(figsize=(10, 6))
    plt.plot(n_values, time_list, label="Liste Chaînée (O(n²))", marker='o', linestyle='--')
    plt.plot(n_values, time_hash, label="Table de Hachage (O(n))", marker='s', linestyle='-')

    plt.xlabel("Taille de la Bibliothèque (n)")
    plt.ylabel("Temps d'exécution (millisecondes)")
    plt.title(titre)
    plt.legend()
    plt.grid(True)

    plt.show()
