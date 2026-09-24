#pragma once

#include "jeu.h"

enum {
    MAX = 256
};

/**
 * Lit le fichier de configuration (crazy.cfg) et remplit la structure ConfigJeu.
 * @param nom_fichier Le chemin du fichier (ex: "crazy.cfg")
 * @param config Un pointeur vers la structure ConfigJeu à remplir
 * @return 0 si tout s'est bien passé (Succès)
 * @return 1 si erreur (fichier introuvable, pas assez d'animaux, ou moins de 3 ordres valides)
 */
int charger_config(const char* nom_fichier, ConfigJeu* config);