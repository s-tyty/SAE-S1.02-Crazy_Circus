#pragma once
#pragma warning (disable : 6308 28183)
#include"jeu.h"

typedef struct Carte {
    EtatJeu config;
    int etat; // 1 si déjà piocher , 0 sinon
} Carte;

typedef struct {
    Carte* c;
    int nb_cartes_total;
    int nb_carte_cree;
} Deck;



/**
   @brief Calcule la factorielle d'un nombre entier (n!).
    Utilisé pour déterminer le nombre total de cartes à générer.
   @param n Le nombre dont on veut la factorielle.
   @return Le résultat de n!.
 */
int factorielle(int n);

/**
 @brief Échange la valeur de deux entiers via leurs adresses.
 @param a Pointeur vers le premier entier.
 @param b Pointeur vers le deuxième entier.
 */
void echanger_animaux(int* a, int* b);




/*==================  GENERATION DES CARTES   ===================*/

/**
 @brief Initialise le deck et lance la génération de toutes les cartes.
 @param d Pointeur vers la structure Deck à initialiser.
 @param nb_animaux Le nombre d'animaux dans le jeu.
 */
void initialiser_deck(Deck* d, int nb_animaux);

/**
 @brief Algorithme de Heap (Permutations).
   Fonction récursive qui génère toutes les permutations possibles d'un tableau.
 @param d Pointeur vers le Deck.
 @param tab Le tableau d'animaux en cours de mélange.
 @param c Compteur pour la récursion
 @param n Nombre total d'animaux .
 */
void algo_heap(Deck* d, int* tab, int c, int n);

/**
 @brief Crée une carte unique à partir d'une permutation et d'un séparateur.
 @param d Pointeur vers le Deck.
 @param Le tableau contenant l'ordre actuel des animaux.
 @param L'indice où l'on sépare le tableau (gauche = Bleu, droite = Rouge).
 @param Le nombre total d'animaux.
 */
void cree_une_carte(Deck* d, int* tab_animaux, int separateur, int nb_animaux);

/**
 * @brief Mélange les cartes du deck (Fisher-Yates).
 * @param le deck de carte
 */
void melanger_deck(Deck* d);

/**
 * @brief Mélange aléatoirement un simple tableau d'entiers.
 * @param tab Le tableau à mélanger 
 * @param taille Le nombre d'éléments dans le tableau.
 */
void melanger_tableau_int(int* tab, int taille);