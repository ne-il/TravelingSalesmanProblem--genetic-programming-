#include "carte.h"


void initialiser_carte (Carte* carte){
	carte->villes=NULL;
	carte->nb_ville=0;
}
/*Il faut que le champ carte->nb_ville contienne déja une valeur et que carte->villes = NULL*/
void allouer_carte (Carte* carte){

	carte->villes = (Ville*) calloc( carte->nb_ville , sizeof(Ville) );
	if (NULL == carte->villes)
		exit(EXIT_FAILURE);
}

void lire_carte (Carte * carte){
	int i;


	printf("Combien de ville voulez vous creez pour la carte?\n");
	scanf("%d", &(carte->nb_ville) );

	allouer_carte (carte);


	for(i=0; i< carte->nb_ville; i++){
		lire_ville ( &(carte->villes[i]) ) ;
	}
}

void generer_carte_aleatoire (Carte* carte ){
	int i=0;

	assert(carte != NULL);

	allouer_carte (carte);

	for(i=0; i< carte->nb_ville; i++)
		 generer_ville_aleatoire ( &(carte->villes[i])) ;	
}

void sauvegarder_carte (FILE* fichier, const Carte* carte){
	int i;

	for(i=0; i< carte->nb_ville; i++){
		sauvegarder_ville (fichier, &(carte->villes[i]) ); 
	}
	printf("Sauvegarde effectuée\n");
}

void charger_carte (FILE* fichier, Carte* carte){
	int i;

	fscanf(fichier, "%d", &(carte->nb_ville) ) ;

	allouer_carte (carte);


	for (i = 0; i<carte->nb_ville; i++){
		charger_ville ( fichier, & (carte->villes[i]));	
	}
}



void creer_carte_click(Carte* carte){
	int i;
	char lettre;
	int souris_x;
	int souris_y;
	char buffer[128];
	
	MLV_Color couleur;
	
	souris_x=0;
	souris_y=0;


	allouer_carte (carte);

	for(i = 0; i < carte->nb_ville; i++){
		if(i == 0)
			couleur=MLV_COLOR_GREEN;

		else if(i == 1)
			couleur=MLV_COLOR_RED;
		else
			couleur=MLV_COLOR_WHITE;
	
		do{
			MLV_wait_mouse (&souris_x, &souris_y);
		}while (souris_x < BORDURE || souris_x > (LARGEUR_FENETRE+BORDURE) || souris_y < BORDURE || souris_y > (HAUTEUR_FENETRE + BORDURE) ) ;

		carte->villes[i].x= souris_x;
		carte->villes[i].y= souris_y;
	
		lettre = 65 + rand()%26;

		sprintf(buffer,"%d%c%d",carte->villes[i].x, lettre, carte->villes[i].y);


		carte->villes[i].nom=(char*) malloc( ( strlen(buffer) +1) * sizeof(char));	
		if (NULL == carte->villes[i].nom)
			exit(EXIT_FAILURE);	

		strcpy( carte->villes[i].nom, buffer);

		MLV_draw_filled_circle (carte->villes[i].x , carte->villes[i].y, TAILLE_POINT, couleur);
		MLV_actualise_window();

	}
	

}

void supprimer_carte (Carte *carte){
	int i;

	for(i=0; i < carte->nb_ville; i++){
		supprimer_ville ( &(carte->villes[i]) );
	}

	free (carte->villes);


}



int est_egale_carte (const Carte *carte_dest, const Carte *carte_src){
	int i;

	if (carte_dest->nb_ville != carte_src->nb_ville)
			return 0;

	for(i=0; i < carte_dest->nb_ville; i++){

		if ( est_different_ville (&carte_dest->villes[i], &carte_src->villes[i]) )
			return 0;
	}

	return 1;
}

int est_different_carte (const Carte *carte_1,const Carte *carte_2){

	return(!est_egale_carte (carte_1, carte_2));
}

/*Faire bien attention à la mémoire */
void copie_carte (Carte *carte_dest, const Carte* carte_src){
	int i;

	Ville* villes_tmp=NULL;

	villes_tmp = (Ville *) realloc(carte_dest->villes , carte_src->nb_ville * sizeof(Ville) );

	if ( villes_tmp == NULL ){
	     printf("Reallocation impossible\n");
	     free (carte_dest->villes);
	     exit(EXIT_FAILURE);
	}
	else
			carte_dest->villes = villes_tmp;



	carte_dest->nb_ville = carte_src->nb_ville;

	for(i=0; i < carte_src->nb_ville; i++  ){
		copier_ville ( &(carte_dest->villes[i]), &(carte_src->villes[i]) ) ;
	}
}