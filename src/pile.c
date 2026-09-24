#include "pile.h"

void init_podium(Podium* p, int taille_max) {
	p->nb_elements = 0;
	p->capacite_max = taille_max;

	// on réserve de la place pour la taille_max entiers
	p->pile = (int*)malloc(taille_max * sizeof(int));
	if (p->pile == NULL) {
		printf("Erreur : Plus de memoire pour le podium\n");
		exit(1);
	}
	for (int i = 0; i < taille_max; ++i) {
		p->pile[i] = -1; 
	}
}


void liberer_podium(Podium* p) {
	if (p->pile != NULL) {
		free(p->pile);
		p->pile = NULL;
	}
}
int empiler(Podium* p, int animal) {
	if (p->nb_elements >= p->capacite_max) { // Si le podium est déjà plein, on refuse d'ajouter
		return -1;
	}
	p->pile[p->nb_elements] = animal; // On place l'animal dans la première case libre
	p-> nb_elements++;
	return 0;
}

int depiler(Podium* p) {
	if (p->nb_elements <= 0) { // Si le podium est vide, on ne peut rien enlever
		return -1;
	}
	p->nb_elements--; // On décrémente d'abord pour pointer sur le dernier élément ajouté
	int n = p->pile[p->nb_elements];// On sauvegarde l'animal qui était au sommet pour le renvoyer
	p->pile[p->nb_elements] = 0;
	return n;
}

int sommet_podium(Podium* p) {
	if (p->nb_elements <= 0) { // Si c'est vide, il n'y a pas de sommet
		return -1;
	}
	return p->pile[p->nb_elements - 1];
}

int podium_vide(Podium* p){
	if (p->nb_elements == 0){// Si le compteur est à 0, c'est que c'est vide
		return 1;
	}
	return 0;
}


void copier_podium(Podium* destination, Podium* source) {
	destination->nb_elements = source->nb_elements; // On copie le nombre d'éléments

	for (int i = 0; i < source->nb_elements; i++) { // On copie chaque animal du tableau
		destination->pile[i] = source->pile[i];
	}
}

