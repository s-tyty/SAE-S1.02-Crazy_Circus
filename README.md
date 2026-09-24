# Crazy Circus - Version Numérique (SAÉ S1.02)

Ce projet, réalisé dans le cadre de la SAÉ S1.02 "Comparaison d'approches algorithmiques" du BUT Informatique, est une adaptation numérique en langage C du jeu de société **Crazy Circus**[cite: 2, 6]. 

**Auteurs :** MUHAMMAD AHMED et SITTININAE ADITYA (Équipe 92)[cite: 2].

## Description du projet
Le principe du jeu repose sur un défi algorithmique : les joueurs doivent déterminer mentalement la séquence d'ordres la plus rapide pour déplacer des animaux (Lion, Ours, Éléphant) d'une configuration initiale vers une configuration cible[cite: 2, 6]. Les animaux sont répartis sur deux podiums (Bleu et Rouge) manipulés sous forme de structures de données (Piles LIFO)[cite: 2].

### Fonctionnalités principales
* **Moteur de jeu :** Implémentation complète des 5 ordres de déplacement autorisés (`KI`, `LO`, `SO`, `NI` et `MA`)[cite: 4, 6].
* **Configuration dynamique :** Chargement des animaux et des règles au lancement via le fichier `crazy.cfg`[cite: 2, 6].
* **Multijoueur local :** Gestion des tours de jeu, vérification des erreurs et calcul automatique du vainqueur[cite: 2, 6].
* **Robuste et Sécurisé :** Gestion stricte de l'allocation dynamique de la mémoire (aucune fuite) et prévention des erreurs de saisie utilisateur (programmation défensive)[cite: 2].

## Architecture du dépôt
* `src/` : Contient l'intégralité du code source (logique métier, structure des piles, génération des cartes et boucle principale)[cite: 16].
* `docs/` : Contient le rapport de projet, le sujet officiel et les règles du jeu original[cite: 16].
* `crazy.cfg` : Fichier de configuration paramétrable requis pour lancer une partie[cite: 16].

## Compilation et Exécution

### Prérequis
* Un compilateur C (ex: GCC).
* Conserver le fichier `crazy.cfg` à la racine, dans le même répertoire que l'exécutable compilé[cite: 8, 16].

### Commandes
1. **Compiler le code :**
```bash
gcc src/*.c -o crazy_circus
