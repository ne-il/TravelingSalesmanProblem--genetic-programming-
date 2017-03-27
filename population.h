#ifndef __POPULATION__
#define __POPULATION__ 

#include "visite.h"
#include "affichage.h"




void initialiser_population(Population* population);

/*Tout doit déja etre initialiser, et la population doit déja connaitre sa taille dans population->nb_individus */
void allouer_population(Population* population, Carte* carte);

/*Recoit une population déja initialisée!!*/
void generer_population_aleatoire(Carte* carte, Population* population);

void evolution(Carte* carte,  Population* population, Visite* visite_charge, Parametre_evolution* parametre, int verbeux);

void copier_population(Population* population_dest, Population* population_src);

void supprimer_population(Population* population);

#endif