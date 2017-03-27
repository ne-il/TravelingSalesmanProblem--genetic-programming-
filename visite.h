#ifndef __VISITE__
#define __VISITE__ 

#include "carte.h"


/* Cette fonction génère une visite aléatoirement d'une carte passé en argument
 On quitte le programme si l'allocation a échouer on renvoie la visite sinon. */
void generer_visite_alea(const Carte* carte, Visite* visite);

/* Cette fonction permet de calculer la distance totale des visites d'une carte les deux passé en argument 
Renvoie la distance total des visites.*/
double calculer_distance_visite(const Carte* carte, const Visite* visite);

/* Cette fonction sauvegarde une visite que on a passé dans un fichier que on a passé en argument*/
void sauvegarder_visite(FILE * fichier,const Carte* carte,const Visite* visite);

/* Cette fonction charge une fichier dans un fichier que on a passé en argument
On quite le programme si l'allocation c'est mal passé on modifie la visite et la carte passé en argument sinon.  */
void charger_visite(FILE * fichier, Carte* carte, Visite* visite);

int calculer_indice_distance_min(Carte * carte, int indice_depart, int** ville_marque);

void calculer_visite_glouton(Carte *carte, Visite *glouton);

void supprimer_visite(Visite *visite);


/*Met les pointeurs à NULL*/
void initialiser_visite(Visite* visite);

int est_egale_visite(const Visite *visite_1,const Visite *visite_2);

int est_different_visite(const Visite *visite_1, const Visite *visite_2);

void copier_visite(Visite *visite_dest, Visite *visite_src);

void allouer_visite(Visite* visite);

void echange(int* tab, int i, int j);

void mutation(Visite *visite);

void croisement_visites(const Carte *carte, const Visite *visite_1, const Visite *visite_2, Visite *visite_croisee);

#endif