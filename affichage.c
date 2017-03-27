#include "affichage.h"



void initialiser_fenetre(){
	MLV_create_window("PVC", "PVC",LARGEUR_FENETRE ,HAUTEUR_FENETRE); 	
}


void afficher_ville(const Ville* v){
	printf("%s %d %d \n", v->nom, v->x, v->y);
}

void afficher_carte(const Carte* carte){
	int i;
	
	for(i=0; i < carte->nb_ville; i++){
		afficher_ville( &(carte->villes[i]) ); 
	}
	printf("\n");
}

void afficher_visite (const Carte* carte,const Visite* visite){
	int i=0;

	for (i=0; i<visite->nb_ville; i++){
		printf("%d)",i+1);
		afficher_ville( &(carte->villes[ visite->parcours[i] ] ) );
	}

	printf( "----FITNESS: %.2f \n", visite->distance );

	printf("\n");
}





void afficher_population(Population* population){
	int i;
	assert(population != NULL);
	assert(population->individus != NULL );
	assert(population->carte != NULL);

	for(i=0; i < population->nb_individus; i++){
		afficher_visite(population->carte, &(population->individus[i]));
	}
}

void afficher_juste_fitness (const Carte* carte,const Visite* visite){


	printf("----FITNESS: %.2f \n", visite->distance);

	printf("\n");
}

void afficher_fitness_population(Population* population){
	int i;

	assert(population != NULL);
	assert(population->individus != NULL );
	assert(population->carte != NULL);

	for(i=0; i < population->nb_individus; i++){
		afficher_juste_fitness(population->carte, &(population->individus[i]));
	}
}




void calculer_coordonnees_extremes (const Carte * carte, Extremum* extreme){

	int i;
	assert(carte != NULL);


	extreme->x_max = extreme->x_min = carte->villes[0].x;
	extreme->y_max = extreme->y_min = carte->villes[0].y;

	for (i = 1; i < carte->nb_ville; i++){

		if (carte->villes[i]. x < extreme->x_min)
			extreme->x_min = carte->villes[i].x;

		if (carte->villes[i].x > extreme->x_max)
			extreme->x_max = carte->villes[i].x;

		if (carte->villes[i].y < extreme->y_min)
			extreme->y_min = carte->villes[i].y;

		if (carte->villes[i].y > extreme->y_max)
			extreme->y_max = carte->villes[i].y;

	}
}
/*--------------------------------------------------------*/
void convertir_coordonnees_reels_pour_affichage (const Extremum* extreme, int x_reel, int y_reel, int* x_affichage, int* y_affichage ){
	*x_affichage = ( ( (LARGEUR_FENETRE - 2*BORDURE) * (x_reel - extreme->x_min) / (extreme->x_max - extreme->x_min) )) + BORDURE;
	*y_affichage = ( ( (HAUTEUR_FENETRE - 2*BORDURE) * (y_reel - extreme->y_min) / (extreme->y_max - extreme->y_min) )) + BORDURE;
}

void afficher_graphique_visite(const Carte* carte, const Visite* visite){

	static int memo = 1;
	static Carte carte_affichage;
	static Extremum extreme;
	int i;
	MLV_Color couleur=MLV_COLOR_GREEN;


	if (memo){

		initialiser_carte (&carte_affichage);
		carte_affichage.nb_ville = carte->nb_ville;
		allouer_carte (&carte_affichage);

		calculer_coordonnees_extremes (carte, &extreme);

		if( extreme.x_max > LARGEUR_FENETRE || extreme.y_max > HAUTEUR_FENETRE ){

			for (i = 0; i < carte->nb_ville; i++){
				convertir_coordonnees_reels_pour_affichage (&extreme, carte->villes[i].x, carte->villes[i].y, &(carte_affichage.villes[i].x), &(carte_affichage.villes[i].y) );
			}
		}
		else{

			for (i = 0; i < carte->nb_ville; i++){
				carte_affichage.villes[i].x = carte->villes[i].x;
				carte_affichage.villes[i].y = carte->villes[i].y;
			}
		}

		memo = 0;
	}



	MLV_draw_filled_rectangle(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE, MLV_COLOR_BLACK);

	MLV_draw_filled_circle (carte_affichage.villes[ visite->parcours[0] ].x , carte_affichage.villes[ visite->parcours[0] ].y, TAILLE_POINT, couleur);


	couleur=MLV_COLOR_WHITE;
	for (i = 0; i < carte->nb_ville-1; i++){
		
		MLV_draw_line (carte_affichage.villes[ visite->parcours[i] ].x , carte_affichage.villes[ visite->parcours[i] ].y, carte_affichage.villes[ visite->parcours[i+1] ].x , carte_affichage.villes[ visite->parcours[i+1] ].y , MLV_COLOR_PINK);
		MLV_draw_filled_circle (carte_affichage.villes[ visite->parcours[i+1] ].x , carte_affichage.villes[ visite->parcours[i+1] ].y, TAILLE_POINT, couleur);

	}

	couleur=MLV_COLOR_RED;
	MLV_draw_filled_circle (carte_affichage.villes[ visite->parcours[carte->nb_ville-1] ].x , carte_affichage.villes[ visite->parcours[carte->nb_ville-1] ] .y, TAILLE_POINT, couleur);


	MLV_actualise_window();

}

void afficher_graphique_carte(const Carte* carte){
	int i;
	MLV_Color couleur = MLV_COLOR_GREEN;

	MLV_draw_filled_rectangle(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE, MLV_COLOR_BLACK);
	MLV_draw_filled_circle (carte->villes[0].x , carte->villes[0].y, TAILLE_POINT, couleur);

	couleur=MLV_COLOR_RED;
	MLV_draw_filled_circle (carte->villes[1].x , carte->villes[1] .y, TAILLE_POINT, couleur);

	couleur=MLV_COLOR_WHITE;
	for (i = 1; i < carte->nb_ville-1; i++)
		MLV_draw_filled_circle (carte->villes[i+1].x , carte->villes[i+1].y, TAILLE_POINT, couleur);



	MLV_actualise_window();
}

void nettoyer_fenetre_graphique(){
	MLV_draw_filled_rectangle(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE, MLV_COLOR_BLACK);
}
