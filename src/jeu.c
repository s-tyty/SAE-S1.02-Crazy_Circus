#include <stdio.h>
#include "jeu.h"
#include "carte.h"

void LO (Podium* bleu, Podium* rouge) {

    // On verifie qu'ont ne peut pas prendre un animal s'il n'y en a pas !
    if (podium_vide(rouge)) {
        printf("Mouvement impossible : Le podium ROUGE est vide ! \n");
        return;
    }

    int a = depiler(rouge);   // on recupere l'animaux qu'on enleve dans a 
    empiler(bleu, a);
}
void KI(Podium* bleu, Podium* rouge) {

    // On verifie qu'ont ne peut pas prendre un animal s'il n'y en a pas !
    if (podium_vide(bleu)) {
        printf("Mouvement impossible : Le podium BLEU est vide ! \n");
        return;
    }

    int a = depiler(bleu);
    empiler(rouge, a);
}

void SO(Podium* bleu, Podium* rouge) {

    // On verifie qu'il y a un animal dans chauque podium pour pouvoir les permuter 
    if (podium_vide(bleu) || podium_vide(rouge)) {      
        printf("Mouvement impossible : Il faut un animal sur chaque podium !\n");
        return;
    }

    int a = depiler(bleu);
    int b = depiler(rouge);

    empiler(bleu, b);
    empiler(rouge, a);
}

void NI(Podium* bleu, Podium* rouge) {
    if (bleu->nb_elements < 2) {
        return;
    }

    int hauteur = bleu->nb_elements;

    // Allocation dynamique
    int* temp = (int*)malloc(hauteur * sizeof(int));
    if (temp == NULL) {
        printf("Erreur d'allocation memoire \n");
        exit(1); 
    }

    // On vide le podium pour remplir le tableau temporaire
    for (int i = 0; i < hauteur; i++) {
        temp[i] = depiler(bleu);
    }

    // L'animal tout en bas est celui à l'indice [hauteur - 1]
    int animal_du_bas = temp[hauteur - 1];

    // On remet les animaux dans le podium (SAUF celui du bas)
    for (int i = hauteur - 2; i >= 0; i--) {
        empiler(bleu, temp[i]);
    }

    // On place l'animal du bas tout en HAUT
    empiler(bleu, animal_du_bas);

    free(temp);
}

void MA(Podium* bleu, Podium* rouge) {
    if (rouge->nb_elements < 2) {
        return;
    }

    int hauteur = rouge->nb_elements;

    int* temp = (int*)malloc(hauteur * sizeof(int));
    if (temp == NULL) {
        printf("Erreur d'allocation memoire \n");
        exit(1);
    }

    for (int i = 0; i < hauteur; i++) {
        temp[i] = depiler(rouge);
    }

    int animal_du_bas = temp[hauteur - 1];

    for (int i = hauteur - 2; i >= 0; i--) {
        empiler(rouge, temp[i]);
    }

    empiler(rouge, animal_du_bas);

    free(temp);
}

int victoire(Podium* bleu_etat, Podium* rouge_etat, Carte* carte_objectif){

Podium* bleu_attendu = &carte_objectif->config.podiums[PODIUM_BLEU];
Podium* rouge_attendu = &carte_objectif->config.podiums[PODIUM_ROUGE];


if (bleu_etat->nb_elements != bleu_attendu->nb_elements) {  // On vérifie la hauteur 
    return 1; // Perdu
}

// Verification du Podium Bleu
for (int i = 0; i < bleu_etat->nb_elements; i++) {
    if (bleu_etat->pile[i] != bleu_attendu->pile[i]) {
        return 1; // Un animal different
    }
}

// Verification du Podium Rouge
if (rouge_etat->nb_elements != rouge_attendu-> nb_elements) { // Verification de la hauteur du podium rouge
    return 1;
}
for (int i = 0; i < rouge_etat->nb_elements; i++) {    // Boucle pour verifier les animaux
    if (rouge_etat->pile[i] != rouge_attendu->pile[i]) {
        return 1;
    }
}
return 0; // Carte identique
}


void afficher_interface(Podium* b_jeu, Podium* r_jeu, Carte* obj, char** noms_animaux, int nb_total_animaux) {
    Podium* b_obj = &obj->config.podiums[PODIUM_BLEU];
    Podium* r_obj = &obj->config.podiums[PODIUM_ROUGE];

    // On parcourt de haut en bas 
    for (int h = nb_total_animaux - 1; h >= 0; h--) {

        //  PARTIE GAUCHE 
        // Bleu
        if (h < b_jeu->nb_elements)
            printf("%-12s", noms_animaux[b_jeu->pile[h]]);
        else
            printf("%-12s", "");

        // Rouge 
        if (h < r_jeu->nb_elements)
            printf("%-12s", noms_animaux[r_jeu->pile[h]]);
        else
            printf("%-12s", "");
        printf("       ");

        // Bleu Objectif
        if (h < b_obj->nb_elements)
            printf("%-12s", noms_animaux[b_obj->pile[h]]);
        else
            printf("%-12s", "");

        // Rouge Objectif
        if (h < r_obj->nb_elements)
            printf("%-12s", noms_animaux[r_obj->pile[h]]);
        else
            printf("%-12s", "");

        printf("\n");
    }

    // --- PIED DE PAGE 
    printf("----        ----       ==>     ----        ----\n");
    printf("BLEU        ROUGE              BLEU        ROUGE\n\n");
}



int commande_autorisee(char* cmd, ConfigJeu* conf) {
    for (int i = 0; i < conf->nb_ordre; i++) {
        // On compare la commande avec celles stockées dans la config
        if (strcmp(cmd, conf->ordre[i]) == 0) {
            return 1; // Trouvé !
        }
    }
    return 0; // Pas trouvé
}


void afficher_ordres(ConfigJeu* conf) {
    
    for (int i = 0; i < conf->nb_ordre; i++) {// On parcourt les ordres autorisés et on affiche la legende
        char* o = conf->ordre[i];

        if (strcmp(o, "KI") == 0) 
            printf("KI (B -> R)");
        else if (strcmp(o, "LO") == 0) 
            printf("LO (B <- R)");
        else if (strcmp(o, "SO") == 0) 
            printf("SO (B <-> R)");
        else if (strcmp(o, "NI") == 0) 
            printf("NI (B ^)");
        else if (strcmp(o, "MA") == 0) 
            printf("MA (R ^)");

        // Séparateur entre les ordres 
        if (i < conf->nb_ordre - 1) {
            printf(" | ");
        }
    }
    printf("\n\n");
} 

void executer_sequence(char* buffer, Podium* b, Podium* r, ConfigJeu* conf) {
    int len = strlen(buffer);

    for (int i = 0; i < len; i += LONGUEUR_CMD) {
        char cmd[TAILLE_BUFFER_CMD];

        cmd[0] = buffer[i];

        if (i + 1 < len) {
            cmd[1] = buffer[i + 1];
        }
        else {
            cmd[1] = '\0';
        }
        cmd[2] = '\0';

        // Vérification
        if (!commande_autorisee(cmd, conf)) {
            printf("Commande '%s' inconnue \n", cmd);
            continue;
        }

        // Exécution 
        if (strcmp(cmd, "LO") == 0)      LO(b, r);
        else if (strcmp(cmd, "KI") == 0) KI(b, r);
        else if (strcmp(cmd, "SO") == 0) SO(b, r);
        else if (strcmp(cmd, "NI") == 0) NI(b, r);
        else if (strcmp(cmd, "MA") == 0) MA(b, r);
    }
}

void afficher_resultats(int nb_joueurs, char* noms[], int* scores) {
    // Tri à bulles 
    // On va trier scores et on déplace noms en même temps 

    for (int i = 0; i < nb_joueurs - 1; i++) {
        for (int j = 0; j < nb_joueurs - i - 1; j++) {

            int echange_necessaire = 0;
            if (scores[j] < scores[j + 1]) { //Score décroissant
                echange_necessaire = 1;
            }

            else if (scores[j] == scores[j + 1]) { // Si égalité de points, ordre alphabétique croissant
                if (strcmp(noms[j + 1], noms[j + 2]) > 0) {
                    echange_necessaire = 1;
                }
            }

            if (echange_necessaire) {
                // Echange des scores
                int temp_s = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp_s;

                // Echange des noms 
                char* temp_n = noms[j + 1];
                noms[j + 1] = noms[j + 2];
                noms[j + 2] = temp_n;
            }
        }
    }

    // Affichage final 
    for (int i = 0; i < nb_joueurs; i++) {
        printf("%s %d\n", noms[i + 1], scores[i]);
    }
}