#include "ville.h"

void initialiser_ville (Ville* ville){
	ville->nom = NULL;
	ville->x = -1;
	ville->y = -1;
}

void allouer_ville (Ville* ville, char* buffer){
	assert (ville->nom == NULL);

	ville->nom = (char*) calloc ( (strlen (buffer) +1) ,  sizeof (char) );
	if (NULL == ville->nom)
		exit (EXIT_FAILURE);
	
	strcpy (ville->nom, buffer);
}

void lire_ville (Ville* v){
	char buffer[128];
	
	printf ("Entrez la ville avec ce format 'Nom x y' \n");
	scanf ("%s %d %d", buffer, &(v->x), &(v->y));

	allouer_ville (v, buffer);

}

void sauvegarder_ville (FILE * fichier, const Ville* v){
	assert (NULL != fichier);

	fprintf (fichier, "%s %d %d \n", v->nom, v->x, v->y);
}

void generer_ville_aleatoire (Ville* v){
	char lettre = '0';
	char buffer[128];

	assert (NULL != v);

	v->x = BORDURE + ( rand () %  (LARGEUR_FENETRE - (2*BORDURE)) );
	v->y = BORDURE + ( rand () %  (HAUTEUR_FENETRE - (2*BORDURE)) );
	lettre = 65 + (rand () % 26);
	sprintf (buffer,"%d%c%d", v->x, lettre, v->y);

	allouer_ville (v, buffer);
}

void charger_ville (FILE * fichier, Ville* v){
	char buffer[128];

	assert (NULL != fichier);

	if  (fscanf (fichier, "%s %d %d", buffer, &(v->x), &(v->y)) != 3)
		exit (EXIT_FAILURE);	

	allouer_ville (v, buffer);
}

double calculer_distance_ville (const Ville* v1, const Ville* v2){
	double distance = 0;

	distance = ( (v2->x - v1->x) *  (v2->x - v1->x)) +  ( (v2->y - v1->y) *  (v2->y - v1->y));
	distance = sqrt (distance);
	
	return distance;
}

void supprimer_ville (Ville* ville){
	free (ville->nom);
}



int est_egale_ville (const Ville* ville_1, const Ville* ville_2){
	if  (ville_1->x != ville_2->x || ville_1->y != ville_2->y || strcmp (ville_1->nom, ville_2->nom) != 0)
		return 0;
	return 1;
}

int est_different_ville (const Ville *ville_1, const Ville *ville_2){
	return (!est_egale_ville (ville_1, ville_2));
}

void copier_ville (Ville *ville_dest, const Ville* ville_src){
	char* chaine_tmp = NULL;

	ville_dest->x = ville_src->x;
	ville_dest->y = ville_src->y;


	chaine_tmp = (char *) realloc (ville_dest->nom , strlen (ville_src->nom) * sizeof (char) + 1);
	if  (chaine_tmp == NULL){
	     printf ("Reallocation impossible\n");
	     free (ville_dest->nom);
	     exit (EXIT_FAILURE);
	}
	else
			ville_dest->nom = chaine_tmp;

	strcpy (ville_dest->nom, ville_src->nom);
}