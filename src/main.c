#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "jeu.h"
#include "carte.h"
#include "config.h"
#include "pile.h"

int main(int argc, char* argv[]) {
    //Initialisation de l'aléatoire
    srand((unsigned int)time(NULL));

    if (argc < TAILLE_BUFFER_CMD) {
        printf("Erreur : Il faut au moins 2 joueurs.\n");
        printf("Usage : %s Joueur1 Joueur2 [Joueur3 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        for (int j = i + 1; j < argc; j++) {
            if (strcmp(argv[i], argv[j]) == 0) {
                printf("Erreur : Les joueurs doivent avoir des noms distincts (%s est en double).\n", argv[i]);
                return 1;
            }
        }
    }
    int nb_joueurs = argc - 1;
    int* scores = (int*)calloc(nb_joueurs, sizeof(int));
    int* joueurs_bloques = (int*)calloc(nb_joueurs, sizeof(int));

    if (scores == NULL || joueurs_bloques == NULL) {
        printf("Erreur allocation memoire.\n");
        return 1;
    }

    ConfigJeu ma_config = { 0 };

    if (charger_config("crazy.cfg", &ma_config) != 0) {
        printf("Erreur : Impossible de lire 'crazy.cfg' ou format incorrect.\n");
        free(scores);
        free(joueurs_bloques);
        return 1;
    }

    // INITIALISATION DU JEU 
    Deck d;
    initialiser_deck(&d, ma_config.nb_animaux);
    melanger_deck(&d);

    Podium bleu, rouge;
    init_podium(&bleu, ma_config.nb_animaux);
    init_podium(&rouge, ma_config.nb_animaux);

    int* indices_animaux = malloc(ma_config.nb_animaux * sizeof(int));
    if (indices_animaux == NULL) return 1;
    for (int i = 0; i < ma_config.nb_animaux; i++) indices_animaux[i] = i;

    // On mélange l'ordre des animaux 
    melanger_tableau_int(indices_animaux, ma_config.nb_animaux);

    // Répartition aléatoire
    int coupure = rand() % (ma_config.nb_animaux + 1);

    for (int i = 0; i < ma_config.nb_animaux; i++) {
        if (i < coupure) {
            empiler(&bleu, indices_animaux[i]);
        }
        else {
            empiler(&rouge, indices_animaux[i]);
        }
    }

    int index_carte = 0;
    int jeu_en_cours = 1;
    int nb_echecs_ce_tour = 0;
    char buffer_ligne[MAX_BUFFER_SAISIE] = { 0 }; // {0} pour eviter les warning
    char nom_joueur[MAX_NOM] = { 0 };
    char sequence[MAX_BUFFER_SAISIE] = { 0 };

    afficher_ordres(&ma_config);

    // BOUCLE PRINCIPALE 
    while (jeu_en_cours && index_carte < d.nb_carte_cree) {

        Carte* objectif = &d.c[index_carte];

        printf("\n\n");
        afficher_interface(&bleu, &rouge, objectif, ma_config.nom_animaux, ma_config.nb_animaux);

        memset(buffer_ligne, 0, MAX_BUFFER_SAISIE);

        if (fgets(buffer_ligne, MAX_BUFFER_SAISIE, stdin) == NULL) break;

        int i = 0;
        while (buffer_ligne[i] != '\0') {
            if (buffer_ligne[i] == '\n') {
                buffer_ligne[i] = '\0';
                break;
            }
            i++;
        }

        int nb_lus = sscanf(buffer_ligne, "%s %s", nom_joueur, sequence);

        int id_joueur = -1;
        for (int k = 1; k < argc; k++) {
            if (strcmp(nom_joueur, argv[k]) == 0) {
                id_joueur = k - 1;
                break;
            }
        }

        if (id_joueur == -1 || nb_lus < 2) {
            printf("Identite inconnue ou format incorrect \n");
            continue;
        }

        if (joueurs_bloques[id_joueur] == 1) {
            printf("%s ne peut plus jouer durant ce tour\n", argv[id_joueur + 1]);
            continue;
        }

        // VERIFICATION COMMANDE
        char test_cmd[TAILLE_BUFFER_CMD];
        strncpy(test_cmd, sequence, 2);
        test_cmd[2] = '\0';

        if (commande_autorisee(test_cmd, &ma_config) == 0) {
            printf("L'ordre %s n'existe pas\n", sequence);
            continue;
        }

        Podium save_bleu, save_rouge;
        init_podium(&save_bleu, ma_config.nb_animaux);
        init_podium(&save_rouge, ma_config.nb_animaux);
        copier_podium(&save_bleu, &bleu);
        copier_podium(&save_rouge, &rouge);

        executer_sequence(sequence, &bleu, &rouge, &ma_config);

        if (victoire(&bleu, &rouge, objectif) == 0) {
            printf("%s gagne un point\n", argv[id_joueur + 1]);
            scores[id_joueur]++;

            // MANCHE SUIVANTE 
            index_carte++;
            memset(joueurs_bloques, 0, nb_joueurs * sizeof(int));
            nb_echecs_ce_tour = 0;
            bleu.nb_elements = 0;
            rouge.nb_elements = 0;

            // Mélange l'ordre
            melanger_tableau_int(indices_animaux, ma_config.nb_animaux);
            // Nouvelle répartition aléatoire
            int coupure_v = rand() % (ma_config.nb_animaux + 1);

            for (int z = 0; z < ma_config.nb_animaux; z++) {
                if (z < coupure_v) empiler(&bleu, indices_animaux[z]);
                else empiler(&rouge, indices_animaux[z]);
            }
        }
        else {
            printf("La sequence ne conduit pas a la situation attendue\n");

            copier_podium(&bleu, &save_bleu);
            copier_podium(&rouge, &save_rouge);

            joueurs_bloques[id_joueur] = 1;
            nb_echecs_ce_tour++;
            printf("%s ne peut plus jouer durant ce tour\n", argv[id_joueur + 1]);

            if (nb_echecs_ce_tour >= nb_joueurs - 1) {
                int id_gagnant = -1;
                for (int j = 0; j < nb_joueurs; j++) {
                    if (joueurs_bloques[j] == 0) {
                        id_gagnant = j;
                        break;
                    }
                }

                if (id_gagnant != -1) {
                    printf("%s gagne un point car lui seul peut encore jouer durant ce tour\n", argv[id_gagnant + 1]);
                    scores[id_gagnant]++;
                    index_carte++;
                    memset(joueurs_bloques, 0, nb_joueurs * sizeof(int));
                    nb_echecs_ce_tour = 0;
                    bleu.nb_elements = 0;
                    rouge.nb_elements = 0;

                    melanger_tableau_int(indices_animaux, ma_config.nb_animaux);
                    int coupure_f = rand() % (ma_config.nb_animaux + 1);

                    for (int z = 0; z < ma_config.nb_animaux; z++) {
                        if (z < coupure_f) 
                             empiler(&bleu, indices_animaux[z]);
                        else empiler(&rouge, indices_animaux[z]);
                    }
                }
            }
        }

        if (save_bleu.pile) 
            free(save_bleu.pile);
        if (save_rouge.pile) 
            free(save_rouge.pile);
    }

    // FIN DU JEU
    afficher_resultats(nb_joueurs, argv, scores);

    free(scores);
    free(joueurs_bloques);
    free(indices_animaux);

    if (bleu.pile) free(bleu.pile);
    if (rouge.pile) free(rouge.pile);

    if (d.c) free(d.c);

    if (ma_config.nom_animaux) {
        for (int i = 0; i < ma_config.nb_animaux; i++)
            free(ma_config.nom_animaux[i]);
        free(ma_config.nom_animaux);
    }

    return 0;
}