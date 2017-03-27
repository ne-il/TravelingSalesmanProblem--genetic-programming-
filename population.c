#include "population.h"

void initialiser_population(Population* population){
	assert(population != NULL);

	population->individus = NULL;
	population->carte = NULL;
	population->nb_individus = 0;
}

/*Tout doit déja etre initialiser, et la population doit déja connaitre sa taille dans population->nb_individus */
void allouer_population(Population* population, Carte* carte){	
	int i;
	assert(population != NULL);
	assert(carte != NULL);

	population->individus = (Visite*) malloc (population->nb_individus * sizeof (Visite));

	if(NULL == population->individus){
		exit(EXIT_FAILURE);
	}

	for(i=0; i < population->nb_individus; i++){
		initialiser_visite(&(population->individus[i]) );
		population->individus[i].nb_ville = carte->nb_ville;

	}

	population->carte = carte;

}

/*Recoit une population déja initialisée!!*/
void generer_population_aleatoire(Carte* carte, Population* population){
	int i;
	assert(carte != NULL);
	assert(population != NULL);


	allouer_population(population, carte);

	for(i=0; i < population->nb_individus; i++){
		generer_visite_alea(carte, &(population->individus[i]) );
		population->individus[i].distance = calculer_distance_visite(carte, &(population->individus[i]) );

	}
}



static int compare (void const *a, void const *b){

   Visite const *p1 =(Visite*) a;
   Visite const *p2 =(Visite*) b;

   return (p1->distance) - (p2->distance);
}



void evolution(Carte* carte,  Population* population, Visite* visite_charge, Parametre_evolution* parametre, int verbeux){
	char fitness_affichage[512];
	char signe;
	int i;
	int random;
	Visite glouton;
	int fitness_tmp=0;



	random = rand()  % 5;
	if (!random)
		random = 1;

	generer_population_aleatoire(carte, population);

	
	if (visite_charge != NULL){
		copier_visite( &(population->individus[ population->nb_individus -1]) , visite_charge );
	}


	qsort (population->individus, population->nb_individus, sizeof(Visite), compare);
	fitness_tmp = population->individus[0].distance;

	
	calculer_visite_glouton(carte, &glouton);

    do{

		for(i=0; i < parametre->proportion_de_clone; i++)
			copier_visite(&(population->individus[ population->nb_individus -1 -i]) , &(population->individus[i] ) );
		
		qsort (population->individus, population->nb_individus, sizeof(Visite), compare);


		for (i = 1; i < parametre->proportion_de_croisee; i++){
			croisement_visites(carte, &(population->individus[i]), &(population->individus[i + 1]), &(population->individus[ population->nb_individus - 1 - i]) );
			population->individus[population->nb_individus - 1 - i].distance = calculer_distance_visite(carte, &(population->individus[population->nb_individus - 1 - i]));
		}

		qsort (population->individus, population->nb_individus, sizeof(Visite), compare);


		for(i = parametre->debut_mutation; i < parametre->fin_mutation; i++){
			mutation( &(population->individus[i]) );
			population->individus[i].distance = calculer_distance_visite(carte, &(population->individus[i]));
		}

		qsort (population->individus, population->nb_individus, sizeof(Visite), compare);

		if(verbeux){
			if ( population->individus[0].distance < fitness_tmp ){
				fitness_tmp = population->individus[0].distance;
				afficher_visite ( carte, &(population->individus[0]) );
			}
		}


		nettoyer_fenetre_graphique();
		afficher_graphique_visite(carte, &(population->individus[0]) );

		if (population->individus[0].distance > glouton.distance)
			signe = '>';
		else if ( population->individus[0].distance < glouton.distance )
			signe = '<';
		else
			signe = '=';
			
		sprintf(fitness_affichage,"PVC		%d villes		fitness_mutation: %.2f %c fitness_glouton: %.2f ", carte->nb_ville, population->individus[0].distance, signe, glouton.distance  ); 
		MLV_change_window_caption( fitness_affichage, "PVC");

	}while(MLV_get_keyboard_state(MLV_KEYBOARD_RETURN) != MLV_PRESSED);


	supprimer_visite(&glouton);

}

void supprimer_population(Population* population){

	int i=0;

	for(i=0; i<population->nb_individus; i++){
		supprimer_visite(&( population->individus[i]) );
	}

	free(population->individus);
	population->nb_individus = 0;
	population->carte = NULL;
}
