#ifndef __CARTE__
#define __CARTE__ 

#include "ville.h"


/* Cette fonction sert a lire un nombre desiré par l'utilisateur de ville 
On quitte le programme si une allocation c'est mal passé renvoie la carte sinon. */
void lire_carte(Carte * carte);

/* Cette fonction permet de créer une carte aléatoirement
On quite le programme si l'allocation c'est mal passé on renvoie la carte sinon.  */
void generer_carte_aleatoire(Carte* carte );

/* Cette fonction sauvegarde une carte que on a passé dans un fichier que on a passé en argument*/
void sauvegarder_carte(FILE* fichier, const Carte* carte);

/* Cette fonction charge une carte dans un fichier que on a passé en argument
On quite le programme si l'allocation c'est mal passé on renvoie la carte sinon.  */
void charger_carte(FILE* fichier, Carte* carte);

void supprimer_carte(Carte *carte);

/*Alloue l'espace memoire nécessaire au tableau de villes de la carte*/
void allouer_carte (Carte* carte);

/*Met les pointeurs à NULL*/
void initialiser_carte(Carte* carte);

int est_egale_carte(const Carte *carte_dest, const Carte *carte_src);

int est_different_carte(const Carte *carte_1,const Carte *carte_2);

void copie_carte(Carte *carte_dest, const Carte* carte_src);

void allouer_carte (Carte * carte);

void creer_carte_click(Carte* carte);

#endif