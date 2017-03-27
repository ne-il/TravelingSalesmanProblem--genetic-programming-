 #include "visite.h"


void initialiser_visite(Visite* visite){
	visite->parcours=NULL;
	visite->nb_ville=0;
}

/*Il faut que visite->parcours = NULL et que visite->nb_ville soit déja rempli*/
void allouer_visite(Visite* visite){

	visite->parcours= (int *) malloc (visite->nb_ville * sizeof(int));
	if(NULL == visite->parcours )
		exit(EXIT_FAILURE);

}

void generer_visite_alea(const Carte* carte, Visite* visite){
	int i = 0;
	int alea = 0;

	visite->nb_ville = carte->nb_ville;

	allouer_visite(visite);

	for(i=1; i < visite->nb_ville -1; i++){
		visite->parcours[i]= -1;	
	}

	visite->parcours[0] = 0;
	visite->parcours[visite->nb_ville -1] = 1;

	for(i=2; i < visite->nb_ville ; i++){
		
		do{
			alea=rand() % visite->nb_ville;
		}while( visite->parcours[alea] != -1);

		visite->parcours[alea] = i;
	}
	visite->distance = calculer_distance_visite(carte, visite);
}

double calculer_distance_visite(const Carte* carte, const Visite* visite){
	int i;
	double distance_visite;

	distance_visite = 0;

	for (i = 0; i+1 < visite->nb_ville; i++)	{
		distance_visite += calculer_distance_ville( &(carte->villes[ visite->parcours[i] ]), &(carte->villes[ visite->parcours[i+1] ]));
	}

	return distance_visite;
}

void sauvegarder_visite(FILE * fichier,const Carte* carte, const Visite* visite){
	int i;

	fprintf(fichier, "%d\n",visite->nb_ville);
	for (i=0; i<visite->nb_ville; i++){
		fprintf(fichier, "%d)",visite->parcours[i]);
		sauvegarder_ville(fichier, &(carte->villes[ visite->parcours[i] ] ) );
	}
	printf("Sauvegarde effectuée\n");
}


void charger_visite(FILE * fichier, Carte* carte, Visite* visite){
	int i=0;
	int* parcours_tmp=NULL;
	Ville* villes_tmp=NULL;

	if ( fscanf (fichier, "%d", &(visite->nb_ville) ) == -1 ){
		printf ("erreur: le fichier est vide\n");
		exit (EXIT_FAILURE);
	}
	carte->nb_ville = visite->nb_ville;


/*On redimensionne les espaces memoires de visite et de carte*/
	parcours_tmp = (int *) realloc(visite->parcours , visite->nb_ville * sizeof(int) );
	if ( parcours_tmp == NULL ){
	     printf("Reallocation impossible\n");
	     free(visite->parcours);
	     exit(EXIT_FAILURE);
	}

	else
			visite->parcours = parcours_tmp;

	villes_tmp = (Ville *) realloc(carte->villes, carte->nb_ville * sizeof(Ville) );
	if ( villes_tmp == NULL ){
	     printf("Reallocation impossible\n");
	     free(carte->villes);
	     exit(EXIT_FAILURE);
	}
	else
		carte->villes=villes_tmp;
	

/*1) Nom X Y
  2) Nom X Y */

	for (i = 0; i < visite->nb_ville; i++){
		fscanf(fichier, "%d" , &(visite->parcours[i]));
		fseek(fichier, 1, SEEK_CUR);
		charger_ville(fichier, &(carte->villes[ visite->parcours[i] ] ) );
	}
		visite->distance= calculer_distance_visite(carte, visite);

}

/* A utiliser avec glouton pour definir la ville la plus proche localement*/
int calculer_indice_distance_min(Carte * carte, int indice_depart, int** ville_marque){
	int indice_min=0;
	double distance=0;
	double distance_min=0;
	int i=0;

	for ( i = 2; i < carte->nb_ville; i++){

		if( (*ville_marque)[i] != -1){

			distance= calculer_distance_ville(&carte->villes[indice_depart], &carte->villes[i]);
			if(distance< distance_min || distance_min == 0){
				distance_min=distance;
				indice_min=i;
			}
		}
	}
	(*ville_marque)[indice_min]=-1;

	return indice_min;
}

/*On veut que glouton ne soit pas encore alloué*/
void calculer_visite_glouton(Carte *carte, Visite *glouton) {
	int i=0;
	int* ville_marque=NULL;

	glouton->nb_ville = carte->nb_ville;

	ville_marque= (int *) calloc(carte->nb_ville, sizeof(int) );

	allouer_visite(glouton);

	glouton->parcours[0]=0;
	glouton->parcours[ carte->nb_ville -1 ]=1;

	ville_marque[0] = ville_marque[1] = -1;


	for(i=0; i< carte->nb_ville-2 ; i++){
		glouton->parcours[i+1] = calculer_indice_distance_min(carte, glouton->parcours[i], &ville_marque);
	}

	glouton->distance= calculer_distance_visite(carte, glouton);

	free( ville_marque);


}

void echange ( int* tab, int i, int j){
	int echange;
	echange = tab[j];
	tab[j] = tab[i];
	tab[i] = echange;
}


void mutation(Visite *visite){
 	int i, j, longueur, k;
 	int indice_milieu, derniere_ville;

 	indice_milieu = ( ( (visite->nb_ville) - 1 ) / 2 );

 	derniere_ville = visite->nb_ville - 1;


 	longueur = rand() % (indice_milieu);

 	if(longueur == 0)
 		longueur = 1;

 	do{
 	i = 1;
 	i += rand() % ( (visite->nb_ville )-1);

 	j = 1;
 	j += rand() % ( (visite->nb_ville )-1);

 	}while ( (i + longueur > derniere_ville) || (fabs( i-j) < longueur) || (j + longueur >= derniere_ville) );

 	for (k = 0; k < longueur; k++){
 		echange(visite->parcours, i + k, j + k);
 	}
}

void croisement_visites(const Carte *carte, const Visite *visite_1, const Visite *visite_2, Visite *visite_croisee){
	int *indice;
	int i, k;

	assert (visite_1 != NULL);
	assert (visite_2 != NULL);
	assert (visite_croisee != NULL);

	visite_croisee->nb_ville = carte->nb_ville;


	indice = (int *) calloc (visite_croisee->nb_ville, sizeof(int));

	visite_croisee->parcours[0] = 0;
	indice [0] = 1;

	visite_croisee->parcours[visite_1->nb_ville - 1] = 1;
	indice [1] = 1;

	k = 1;
	for (i = 1; i < visite_croisee->nb_ville - 1; i++){
		if ( indice[ visite_1->parcours[i] ] == 0){
			visite_croisee->parcours[k] = visite_1->parcours[i];
			indice[ visite_1->parcours[i]] = 1;
			k += 1;
		}

		if (   indice[ visite_2->parcours[i] ] == 0){
			visite_croisee->parcours[k] = visite_2->parcours[i];
			indice[ visite_2->parcours[i]] = 1;
			k += 1;
		}
	}
	visite_croisee->distance = calculer_distance_visite (carte, visite_croisee);
	free (indice);
}	



void supprimer_visite(Visite *visite){
	free(visite->parcours); 
}




int est_egale_visite(const Visite *visite_1,const Visite *visite_2){
	int i;
	if (visite_1->nb_ville != visite_2->nb_ville)
		return 0;
	for(i=0; i<visite_1->nb_ville; ++i){
		if (visite_1->parcours[i] != visite_2->parcours[i])
			return 0;
	}
	return 1;
}

int est_different_visite(const Visite *visite_1, const Visite *visite_2){
	return(!est_egale_visite(visite_1, visite_2));
}


/* Enorme fuite mémoire.*/
void copier_visite(Visite *visite_dest, Visite *visite_src){
	int i;
	int* parcours_tmp = NULL;


	/*supprimer_visite(visite_dest);

	visite_dest->parcours = (int*) malloc( visite_src->nb_ville * sizeof(int) );*/
	parcours_tmp = (int *) realloc(visite_dest->parcours, visite_src->nb_ville * sizeof(int));
	if (parcours_tmp == NULL){
		printf("Reallocation impossible\n");
		free( visite_dest->parcours);
		exit(EXIT_FAILURE);
	}
	else
		visite_dest->parcours = parcours_tmp;


	visite_dest->nb_ville = visite_src->nb_ville;

	for (i = 0; i < visite_dest->nb_ville; ++i)	{
		visite_dest->parcours[i] = visite_src->parcours[i];
	}
	visite_dest->distance = visite_src->distance;

}