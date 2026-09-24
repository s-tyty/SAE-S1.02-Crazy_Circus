#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "animaux.h"
#pragma warning (disable : 6308 4996)

enum { 
    MAX_ORDRES = 10,   // Nombre max d'ordres
    PODIUM_BLEU = 0,
    PODIUM_ROUGE = 1,
    MAX_PODIUM = 2 ,
    LONGUEUR_CMD = 2,      // Une commande fait 2 lettres 
    TAILLE_BUFFER_CMD = 3, // 2 lettres + 1 caractère de fin (\0)
    MAX_BUFFER_SAISIE = 100 // Taille max de ce que tape le joueur
};

typedef struct {
    char** nom_animaux;
    int nb_animaux;
    char ordre[MAX_ORDRES][MAX_ORDRES];  
    int nb_ordre;
} ConfigJeu;

typedef struct {
    int* pile;
    int nb_elements;
    int capacite_max;// Hauteur
} Podium;

typedef struct {
    Podium podiums[MAX_PODIUM]; // 0 pour Bleu, 1 pour Rouge
} EtatJeu; 

typedef struct {
    char nom[MAX_NOM];
    int score;
    int jouer;
} Joueur;

typedef struct Carte Carte;

// Structure temporaire juste pour le classement
typedef struct {
    char* nom;
    int score;
} JoueurClassement;

/*=============== COMMANDE PRINCIPAL DU JEU  ================*/

 /**
  @brief Déplace le sommet du ROUGE vers le sommet du BLEU.
  @param bleu Pointeur vers le podium bleu.
  @param rouge Pointeur vers le podium rouge.
  @pre Le podium rouge ne doit pas être vide.
  */
void LO(Podium* bleu, Podium* rouge);

/**
 @brief Déplace le sommet du BLEU vers le sommet du ROUGE.
 @param bleu Pointeur vers le podium bleu.
 @param rouge Pointeur vers le podium rouge.
 @pre Le podium bleu ne doit pas être vide.
 */
void KI(Podium* bleu, Podium* rouge);

/**
 @brief Échange les deux animaux aux sommets.
 @param bleu Pointeur vers le podium bleu.
 @param rouge Pointeur vers le podium rouge.
 @pre Le podium bleu et le podium rouge ne doivent pas être vides.
 */
void SO(Podium* bleu, Podium* rouge);

/*
 @brief Déplace l'animal du BAS du BLEU vers le HAUT du BLEU (Rotation).
 @param bleu Pointeur vers le podium bleu.
 @param rouge Pointeur vers le podium rouge .
 @pre Le podium bleu doit avoir au moins 2 animaux pour que l'ordre change.
 */
void NI(Podium* bleu, Podium* rouge);

/*
 @brief Déplace l'animal du BAS du ROUGE vers le HAUT du ROUGE (Rotation).
 @param bleu Pointeur vers le podium bleu .
 @param rouge Pointeur vers le podium rouge.
 @pre Le podium rouge doit avoir au moins 2 animaux pour que l'ordre change.
 */
void MA(Podium* bleu, Podium* rouge);
 

/**
 @brief Vérifie si la configuration du joueur correspond à la carte objectif.
 @param bleu_jeu Pointeur vers le podium bleu actuel du joueur.
 @param rouge_jeu Pointeur vers le podium rouge actuel du joueur.
 @param carte_objectif Pointeur vers la carte à reproduire.
 @return 0 si les configurations sont strictement identiques (Gagné), sinon 1.
 */
int victoire(Podium* bleu_jeu, Podium* rouge_jeu, Carte* carte_objectif);


/**
 * @brief Affiche l'interface en split-screen (Jeu à gauche, Objectif à droite).
 * @param b_jeu, r_jeu Les podiums du joueur.
 * @param obj La carte objectif.
 * @param noms_animaux Le tableau des noms chargés depuis la config.
 * @param nb_total_animaux Le nombre total d'animaux pour gérer la hauteur d'affichage.
 */
void afficher_interface(Podium* b_jeu, Podium* r_jeu, Carte* obj, char** noms_animaux, int nb_total_animaux);

/**
 * @brief Vérifie si une commande est dans la liste autorisée (chargée depuis le config).
 * @return 1 si autorisé, 0 sinon.
 */
int commande_autorisee(char* cmd, ConfigJeu* conf);

/**
 * @brief Lit la saisie et exécute les mouvements (ex: "LOKI").
 * Découpe la chaine par bloc de 2 lettres.
 */
void executer_sequence(char* buffer, Podium* b, Podium* r, ConfigJeu* conf);

/**
*@brief Affiche la légende des ordres autorisés.
*/
void afficher_ordres(ConfigJeu* conf);

/**
 * @brief Trie les joueurs (Score décroissant, puis nom alphabétique) et affiche le résultat.
 * @param nb_joueurs Le nombre de joueurs
 * @param noms Le tableau argv (attention, les noms commencent à l'index 1)
 * @param scores Le tableau des scores (commence à l'index 0)
 */
void afficher_resultats(int nb_joueurs, char* noms[], int* scores);
