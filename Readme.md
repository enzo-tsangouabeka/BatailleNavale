# Projet Bataille Navale

## Description

Ce projet est une simulation du jeu classique **Bataille Navale**, développée en C++. Deux joueurs s'affrontent sur des plateaux de jeu de 10x10 cases pour localiser et couler les navires adverses.

### Fonctionnalités principales
- **Niveau 0** : Simule une partie où les bateaux sont positionnés aléatoirement au début du jeu. Les joueurs tirent tour à tour, et la partie se termine lorsque tous les navires d'un joueur sont coulés.
- **Niveau 1 (à implémenter)** : Les joueurs placent leurs propres navires.
- **Niveau 2 (à implémenter)** : Un joueur affronte une intelligence artificielle qui tire aléatoirement.

---

## Prérequis

- **Compilateur C++** compatible avec C++11 ou supérieur.
- **Windows** (utilisation de la bibliothèque `windows.h` pour changer la couleur de la console).
- **CLion** ou tout IDE prenant en charge C++ (facultatif).

---

## Instructions

### Étape 1 : Compilation
1. Clonez ce projet ou copiez les fichiers sources dans un répertoire local.
2. Compilez le projet avec un compilateur comme `g++`. Exemple avec MinGW :
   ```bash
   g++ -o BatailleNavale main.cpp -std=c++20
   ```


### Étape 2 : Exécution

Lancez l'exécutable généré :
    ```bash
    ./BatailleNavale
    ```

### Étape 3 : Règles du jeu (niveau 0)

- Chaque joueur a un plateau de jeu de 10x10 cases.
- Les bateaux sont placés aléatoirement par le programme au début du jeu (dans cette version).
- Le joueur 1 commence à tirer.
- Chaque tir est représenté par une coordonnée (par ex. A1).
- La partie se termine lorsque tous les navires d'un joueur sont coulés.

---

### Détails techniques
#### **Types de navires :**

    Carrier : 5 cases
    Battleship : 4 cases
    Cruiser : 3 cases
    Submarine : 3 cases
    Destroyer : 2 cases

#### **Statut des cases**

    ~ : Case vide (mer)
    C, B, K, S, D : Parties visibles des navires
    X : Missile tombé dans l'eau ou touché un navire

#### **Couleurs de console**

Le jeu utilise des couleurs pour améliorer l'expérience visuelle :

    Bleu : Navires.
    Rouge : Missiles touchées.
    Gris clair : Mer et missiles manqué.


### **Auteur**

- Enzo Tsangouabeka
- Étudiant en BTS Informatique
- etsangouabeka@gmail.com


### To do
- Systeme de choix du niveau
- Mettre des `short` à la place des `int` (ou des `char`) pour gagner en mémoire
- Correction des fautes d'orthographes
- printMatrix et prompt : Mettre les 2 plateaux sur la même ligne + améliorer l'interface du jeu + Afficher les scores et le round