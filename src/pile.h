#pragma once
#include "jeu.h"

/**
 @brief Initialise un podium en le mettant à zéro.
   Met le compteur d'éléments (nb_elements) à 0.
 @param p Pointeur vers le podium à initialiser.
 */
void init_podium(Podium* p, int taille_max);

/**
 @brief Ajoute un animal au sommet du podium
 @param p Pointeur vers le podium.
 @param un entier représentant l'animal à ajouter.
 @pre Le podium ne doit pas être plein.
 @return 1 si l'ajout a réussi, 0 si le podium était plein.
 */
int empiler(Podium* p, int animal);

/**
 @brief Retire et renvoie l'animal au sommet du podium (Pop).
 @param p Pointeur vers le podium.
 @pre Le podium ne doit pas être vide (nb_elements > 0).
 @return L'entier représentant l'animal qui a été retiré.
 */
int depiler(Podium* p);

/**
 @brief Regarde l'animal au sommet sans le retirer.
 @param p Pointeur vers le podium.
 @pre Le podium ne doit pas être vide.
 @return L'entier représentant l'animal au sommet.
 */
int sommet_podium(Podium* p);

/**
 @brief Vérifie si le podium est vide.
 @param p Pointeur vers le podium à tester.
 @return 1 (Vrai) si le podium est vide, sinon 0 (Faux).
 */
int podium_vide(Podium* p);

/**
 @brief Copie le contenu d'un podium source vers un podium destination.
 @param destination Pointeur vers le podium qui recevra la copie (son contenu sera écrasé).
 @param source Pointeur vers le podium modèle à copier.
 */
void copier_podium(Podium* destination, Podium* source);

