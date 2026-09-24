#include"jeu.h"
#include"carte.h"
#include "pile.h"


int factorielle(int n) {
    int f = 1;
    for (int i = 1; i <= n; ++i) {
        f *= i;
    }
    return f;
}

void initialiser_deck(Deck* d, int nb_animaux) {
    int n = nb_animaux;
    d->nb_cartes_total = factorielle(n + 1);
    d->c = (Carte*)malloc(d->nb_cartes_total * sizeof(Carte)); // Allocation dynamique du tableau de toutes les cartes
    assert(d->c != NULL);
    d->nb_carte_cree = 0; // Compteur de carte cree a 0 

    // Création d'un tableau temporaire pour générer les permutations
    int* tab = (int*)malloc(nb_animaux * sizeof(int));
    if (tab == NULL) { // Vérification du succes de l'allocation
        printf("Erreur critique : Plus de memoire pour tab !\n");
        exit(1); // On arrête tout proprement
    }
    for (int i = 0; i < nb_animaux; i++) {
        tab[i] = i;
    }

    algo_heap(d, tab, nb_animaux, nb_animaux); // Generation de toutes les permutations possibles
    free(tab); // On libère le tableau temporaire
}

void cree_une_carte(Deck* d, int* tab_animaux, int separateur, int nb_animaux) {

    int numero = d->nb_carte_cree;
    Carte* c = &d->c[numero];
    c->etat = 0; // Carte non jouée par défaut
    init_podium(&c->config.podiums[PODIUM_BLEU], nb_animaux);
    init_podium(&c->config.podiums[PODIUM_ROUGE], nb_animaux);

    for (int i = 0; i < nb_animaux; i++) {
        int animal = tab_animaux[i];
        if (i <= separateur) {
            empiler(&c->config.podiums[PODIUM_BLEU], animal);
        }
        else {
            empiler(&c->config.podiums[PODIUM_ROUGE], animal);
        }
    }
    d->nb_carte_cree++; // incrémentation pour passser a la prochaine carte
}




void echanger_animaux(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void algo_heap(Deck* d, int* tab, int c, int n) { // Génère toutes les permutations possibles pour les cartes

    if (c == 1) {
        for (int separateur = -1; separateur < n; separateur++) { // on crée toutes les variantes avec separateur
            cree_une_carte(d, tab, separateur, n);
        }
        return;
    }

    for (int i = 0; i < c; i++) {  //boucle pour "melanger"
        algo_heap(d, tab, c - 1, n);
        if (c % 2 == 1) {
            echanger_animaux(&tab[0], &tab[c - 1]); 
        }
        else {
            echanger_animaux(&tab[i], &tab[c - 1]); 
        }
    }
}


void melanger_deck(Deck* d) {    // Melange avec l'algorithme de Fisher-Yates
    int n = d->nb_carte_cree;
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1); // On choisit un index aléatoire j entre 0 et i
        Carte temp = d->c[i]; // On échange la carte i avec la carte aléatoire j
        d->c[i] = d->c[j];
        d->c[j] = temp;
    }
}


// Fonction pour mélanger un simple tableau d'entiers 
void melanger_tableau_int(int* tab, int taille) {
    for (int i = taille - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = tab[i];
        tab[i] = tab[j];
        tab[j] = temp;
    }
}