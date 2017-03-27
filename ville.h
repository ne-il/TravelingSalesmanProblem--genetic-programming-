#ifndef __VILLE__
#define __VILLE__ 

#include "include.h"


/* Affiche une ville avec le format NOM_Ville  Cord_X Cord_Y */
void afficher_ville(const Ville* v);


/* Permet de lire une ville avec le bon format de ville (Nom cord_x cord_y) par l'utilisateur 
Quitte le programme si l'allocation a eu un problème renvoie la ville sinon.*/
void lire_ville(Ville* v);

/* Cette fonction prend deux entiers en parametre qui sont les coord max possible.
On quite le programme si l'allocation c'est mal passé on renvoie la ville sinon.  */
void generer_ville_aleatoire(Ville* v);

/* Cette fonction sauvegarde une ville que on a passé dans un fichier que on a passé en argument*/
void sauvegarder_ville(FILE * fichier,const Ville* v);

/* Cette fonction charge une ville dans un fichier que on a passé en argument
On quite le programme si l'allocation c'est mal passé on renvoie la ville sinon.  */
void charger_ville(FILE * fichier, Ville* v);

/* Cette fonction calcule et renvoie la distance entre deux villes que l'on a passé en parametre */
double calculer_distance_ville (const Ville* v1, const Ville* v2);


void supprimer_ville(Ville* ville);

/*Cette fonction met à NULL les pointeurs et à 0 la distance et le nombre de ville*/
void initialiser_ville(Ville* ville);

/*Alloue l'espace mémoire necessaire pour le nom de la ville*/
void allouer_ville (Ville* ville, char* buffer);

/*renvoie 1 si ville_1 et ville_1 sont égal; 0 sinon*/
int est_egale_ville(const Ville* ville_1, const Ville* ville_2);

/*renvoie 1 si ville_1 et ville_1 sont différentes; 0 sinon*/
int est_different_ville(const Ville *ville_1,const Ville *ville_2);

/*Copie en prodondeurs d'une ville_src vers une ville_dst*/
void copier_ville(Ville *ville_dest,const Ville* ville_src);

#endif