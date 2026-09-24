#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "jeu.h" // Nécessaire pour les constantes

int charger_config(const char* nom_fichier, ConfigJeu* config) {
    FILE* f = fopen(nom_fichier, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", nom_fichier);
        return 1;
    }
    char buffer[MAX];

    // Lecture des animaux 

    if (fgets(buffer, MAX, f) != NULL) {
        char* curseur = buffer;
        char mot_bidon[MAX_NOM];
        int nb_lus = 0;
        int compteur = 0;

        // Comptage préliminaire
        while (sscanf(curseur, "%s%n", mot_bidon, &nb_lus) == 1) {
            compteur++;
            curseur += nb_lus;
        }

        config->nb_animaux = compteur;
        if (config->nb_animaux < 2) {
            printf("Erreur : Il faut au moins 2 animaux dans le fichier config.\n");
            fclose(f);
            return 1;
        }

        // Allocation mémoire
        config->nom_animaux = (char**)malloc(sizeof(char*) * config->nb_animaux);
        if (config->nom_animaux == NULL) { fclose(f); return 1; }

        curseur = buffer;
        int i = 0;

        // Remplissage
        while (i < config->nb_animaux && sscanf(curseur, "%s%n", mot_bidon, &nb_lus) == 1) {
            config->nom_animaux[i] = (char*)malloc(sizeof(char) * (strlen(mot_bidon) + 1));
            strcpy(config->nom_animaux[i], mot_bidon);

            i++;
            curseur += nb_lus;
        }
    }

    if (fgets(buffer, MAX, f) != NULL) {
        char* curseur = buffer;
        char mot_lu[MAX_NOM] = { 0 };
        int nb_lus = 0;
        config->nb_ordre = 0;

        // On lit tant qu'on n'a pas dépassé le max ou la fin de ligne
        while (config->nb_ordre < MAX_ORDRES &&
            sscanf(curseur, "%s%n", mot_lu, &nb_lus) == 1) {

            int est_valide = 0;
            if (strcmp(mot_lu, "KI") == 0) est_valide = 1;
            else if (strcmp(mot_lu, "LO") == 0) est_valide = 1;
            else if (strcmp(mot_lu, "SO") == 0) est_valide = 1;
            else if (strcmp(mot_lu, "NI") == 0) est_valide = 1;
            else if (strcmp(mot_lu, "MA") == 0) est_valide = 1;

            if (est_valide) {
                strcpy(config->ordre[config->nb_ordre], mot_lu);
                config->nb_ordre++;
            }
            curseur += nb_lus;
        }
    }
        fclose(f);
    // C'est ici qu'on vérifie si on a 3 ordres minimums valides
    if (config->nb_ordre < 3) {
        printf("Erreur : Le fichier config doit contenir au moins 3 ordres VALIDES (parmi KI, LO, SO, NI, MA).\n");
        // Nettoyage mémoire avant de quitter
        if (config->nom_animaux) {
            for (int i = 0; i < config->nb_animaux; i++) 
                free(config->nom_animaux[i]);
                free(config->nom_animaux);
        }
        return 1;
    }

    return 0;
}