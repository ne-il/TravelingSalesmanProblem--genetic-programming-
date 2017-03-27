#include "population.h"

typedef enum {
	QUITTER = 0,
	CLIQUE = 1,
	CARTE_ALEA = 2,
	VISITE_ALEA = 3,
	MUTATION = 4,
	GlOUTON = 5,
	CHARGER_CARTE = 6,
	CHARGER_VISITE = 7,
	SAUVEGARDER_CARTE = 8,
	SAUVEGARDER_VISITE = 9
}CHOIX;

void choisir_action (FILE* fichier, Carte *carte, Visite *visite, int choix){
	switch (choix){

		case QUITTER :
			printf("A bientôt\n");
			break;

		case CLIQUE :
			nettoyer_fenetre_graphique();
			creer_carte_click(carte);
			break;

		case CARTE_ALEA :
			nettoyer_fenetre_graphique();
			generer_carte_aleatoire(carte);
			afficher_carte(carte);
			afficher_graphique_carte(carte);
			break;

		case VISITE_ALEA :
			nettoyer_fenetre_graphique();
			initialiser_visite(visite);
			generer_visite_alea(carte, visite);
			afficher_visite(carte, visite);
			afficher_graphique_visite(carte, visite);
			break;

		case MUTATION :
			nettoyer_fenetre_graphique();
			mutation(visite);
			afficher_visite(carte, visite);
			afficher_graphique_visite(carte, visite);
			break;

		case GlOUTON :
			nettoyer_fenetre_graphique();
			calculer_visite_glouton(carte, visite);
			afficher_visite(carte, visite);
			afficher_graphique_visite(carte, visite);
			break;

		case CHARGER_CARTE :
			nettoyer_fenetre_graphique();
			initialiser_carte(carte);
			charger_carte(fichier, carte);
			afficher_carte(carte);
			afficher_graphique_carte(carte);
			fclose(fichier);
			break;

		case CHARGER_VISITE :
			charger_visite(fichier, carte, visite);
			fclose(fichier);
			break;

		case SAUVEGARDER_CARTE :
			sauvegarder_carte(fichier, carte);
			fclose(fichier);
			break;

		case SAUVEGARDER_VISITE :
			sauvegarder_visite(fichier, carte, visite);
			fclose(fichier);
			break;
	}
}

int main(int argc, char * const argv[]){
	FILE * fichier = NULL;
	FILE * fichier2 = NULL;
	Carte carte;
	Visite visite;
	Population population;
	Parametre_evolution parametre;

	int i=0;
	int opt;
	extern char * optarg ;
	int option_i=0;
	int option_t=0;
	int option_c=0;
	int option_g=0;
	int option_v=0;

	srand(time(NULL));

	initialiser_visite(&visite);
	initialiser_carte(&carte);
	initialiser_population(&population);
	initialiser_fenetre();


    

	if (argc < 2){
		printf("Option obligatoire\n");
		exit(EXIT_FAILURE);
	}

	fichier = fopen (argv[1], "w+");

	while ((opt = getopt(argc, argv, "t:i:c:g:v")) !=  -1){
		switch (opt){
			case 't' :

				if (option_c == 1){
					printf("option -c et -t imcompatible\n");
					exit (EXIT_FAILURE);
				}
				else if (option_i == 1){
					printf("option -i et -t imcompatible\n");
					exit (EXIT_FAILURE);
				}


                for (i= 0; optarg[i] != '\0'; i++){
                    if (optarg[i] < '0' || optarg[i] > '9'){
                        printf("Argument INCORRECT\n");
                        exit(EXIT_FAILURE);
                    } 
                }

				carte.nb_ville = atoi (optarg);
				if(carte.nb_ville <= 3 ){
					printf("ERREUR: Il faut que votre carte soit composée d'au moins 4villes\n ");
					exit(EXIT_FAILURE);
				}
				choisir_action(fichier, &carte, &visite, CARTE_ALEA);
				option_t=1;
				break;

			case 'i' :

				if (option_c == 1){
					printf("option -c et -i imcompatible\n");
					exit (EXIT_FAILURE);
				}
				else if (option_t == 1){
					printf("option -t et -i imcompatible\n");
					exit (EXIT_FAILURE);
				}

				fichier2 = fopen (optarg, "r");
				if (fichier2 == NULL){
					printf("ERREUR: LE FICHIER N'EXISTE PAS \n");
					exit (EXIT_FAILURE);
				}
				choisir_action(fichier2, &carte, &visite, CHARGER_VISITE);
				option_i = 1;
				break;

			case 'c' :

				if (option_t == 1){
					printf("option -t et -c imcompatible\n");
					exit (EXIT_FAILURE);
				}
				else if (option_i == 1){
					printf("option -i et -c imcompatible\n");
					exit (EXIT_FAILURE);
				}


                for (i= 0; optarg[i] != '\0'; i++){
                    if (optarg[i] < '0' || optarg[i] > '9'){
                        printf("Argument INCORRECT\n");
                        exit(EXIT_FAILURE);
                    } 
                }

				carte.nb_ville = atoi (optarg);
				choisir_action(fichier, &carte, &visite, CLIQUE);
				option_c = 1 ;
				break;

			case 'g' :

                for (i= 0; optarg[i] != '\0'; i++){
                    if (optarg[i] < '0' || optarg[i] > '9'){
                        printf("Argument INCORRECT\n");
                        exit(EXIT_FAILURE);
                    } 
                }

				population.nb_individus = atoi (optarg);
				option_g = 1;
				break;


			case 'v' :
				option_v = 1;
				break;

			default :
				exit(EXIT_FAILURE);
		}
	}
	if (option_i == 0 && option_t == 0 && option_c ==0){
		printf("Il faut au moins une de ces 3 options : -t -c -i \n");
		exit(EXIT_FAILURE);
	}


	if(option_g == 0)
 		population.nb_individus = TAILLE_POPULATION;

	parametre.proportion_de_clone = population.nb_individus / 3;
	parametre.proportion_de_croisee = (population.nb_individus / 6) -1;
	parametre.debut_mutation = population.nb_individus / 6;
	parametre.fin_mutation = population.nb_individus / 3;
	

	afficher_graphique_carte(&carte);

 	while( MLV_get_keyboard_state(MLV_KEYBOARD_RETURN) != MLV_PRESSED );

 	MLV_wait_milliseconds(500);



 	if(option_i == 1)
 		evolution (&carte, &population, &visite, &parametre, option_v);
 	else
		evolution(&carte, &population, NULL, &parametre, option_v);
	
	choisir_action (fichier, &carte, &(population.individus[0]), SAUVEGARDER_VISITE);
	choisir_action (fichier, &carte, &(population.individus[0]), QUITTER);

	supprimer_carte(&carte);
	supprimer_visite(&visite);
	supprimer_population(&population);

	MLV_free_window();

	return 0;
}
