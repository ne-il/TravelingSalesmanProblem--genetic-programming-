#ifndef __INCLUDE__
#define __INCLUDE__ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <getopt.h>
#include <MLV/MLV_all.h>

#define LARGEUR_FENETRE 1000
#define HAUTEUR_FENETRE 600
#define MAX 728
#define TAILLE_POINT 3
#define BORDURE 10
#define TAILLE_POPULATION 1000


typedef struct{
	char* nom;
	int x, y;
}Ville;


typedef struct{
	Ville* villes;
	int nb_ville;
}Carte;


typedef struct{
	int* parcours;
	int nb_ville;
	double distance;
}Visite;

typedef struct{
	Visite* individus;
	Carte* carte;
	int nb_individus;
}Population;

typedef struct{
	int x_max;
	int y_max;
	int x_min;
	int y_min;	
}Extremum;


typedef struct {
	int proportion_de_clone;
	int proportion_de_croisee;
	int debut_mutation;
	int fin_mutation;	
}Parametre_evolution;

#endif

