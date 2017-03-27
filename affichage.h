#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include "visite.h"


void initialiser_fenetre();

/* Affiche une ville avec le format NOM_Ville  Cord_X Cord_Y */
void afficher_ville(const Ville* v);

/* Cette fonction sert a l'affichage d'une carte passé en argument */
void afficher_carte(const Carte* carte);

/* Cette fonction permet d'afficher les visites d'une carte, les deux passé en argument. + la fitness de la visite */
void afficher_visite (const Carte* carte,const Visite* visite);

/* Cette fonction permet d'afficher seulement la fitness d'une visite passé en argument. + la fitness de la visite */
void afficher_juste_fitness (const Carte* carte,const Visite* visite);


void afficher_population(Population* population);

/*determine les coordonnes extremes d'une carte prise en paramatre et les place dans une variable de type Extremum recu en parametre*/
void calculer_coordonnees_extremes (const Carte * carte, Extremum* extreme);

void convertir_coordonnees_reels_pour_affichage (const Extremum* extreme, int x_reel, int y_reel, int* x_affichage, int* y_affichage );


void afficher_graphique_visite(const Carte* carte, const Visite* visite);

void afficher_graphique_carte(const Carte* carte);

void nettoyer_fenetre_graphique();

#endif