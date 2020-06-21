#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "../GFX_lib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../GFX_lib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "../GFX_lib/ESLib.h" // Pour utiliser valeurAleatoire()

#define LargeurFenetre 800
#define HauteurFenetre 600

void gestionEvenement(EvenementGfx evenement);
void afficheBouton1();
void gereClicBouton1();
void afficheBouton2();
void gereClicBouton2();
void AllInOne(int selecteur);
static DonneesImageRGB *canvas = NULL;
static DonneesImageRGB *image = NULL; 


int main(int argc, char **argv)
{
	
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("GFX", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	return 0;
}

void gestionEvenement(EvenementGfx evenement){
	
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	switch(evenement){
		
		case Initialisation:
			image = lisBMPRGB("bmp/flying.bmp");
			canvas = lisBMPRGB("bmp/flying.bmp");
			rafraichisFenetre();
			demandeTemporisation(20);
			break;
		
		case Temporisation:
			rafraichisFenetre();
			break;
			
		case Affichage:
			

			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier()){
				
				case 'Q':
					libereDonneesImageRGB(&image);
					termineBoucleEvenements();
					break; /* Pour sortir quelque peu proprement du programme */
				case 'q':
					libereDonneesImageRGB(&image); /* On libere la structure image,
					c'est plus propre, meme si on va sortir du programme juste apres */
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran; // Changement de mode plein ecran
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'R':
				case 'r':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 20 millisecondes (rapide)
					demandeTemporisation(20);
					break;

				case 'L':
				case 'l':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 100 millisecondes (lent)
					demandeTemporisation(100);
					break;

				case 'S':
				case 's':
					// Configure le systeme pour ne plus generer de message Temporisation
					demandeTemporisation(-1);
					break;
					
			}
			break;
			
		case ClavierSpecial:
			if (toucheClavier()==19){
				
				break;
			}
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye){
				
				printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			else if (etatBoutonSouris() == GaucheRelache){
				
				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;
	}
}

void afficheBouton1(){
	
	
}
void gereClicBouton1(){
	

}

void afficheBouton2(){
	
	
}

void gereClicBouton2(){

	
}

void AllInOne(selecteur){
	
	
}


void jeu_sept_erreurs()
{
	// on affiche les 2 images

	int erreurs = 0;

	int abscisses_des_erreurs[7] = {;;;;;;} // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
	int ordonnees_des_erreurs[7] = {;;;;;;}

	//début du timer

	while (erreurs != 7)
	{
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (abscisses_des_erreurs[i] - 10 <= abscisseSouris() <= abscisses_des_erreurs[i] + 10 && ordonnees_des_erreurs - 10 <= ordonneeSouris() <= ordonnees_des_erreurs - 10 && /*clic*/) // si clic correspond a l'erreur
				{
					erreurs++;

					couleurCourante(255, 0, 0);
					epaisseurTrait(2);
					afficheCercle(abscisses_des_erreurs[i], ordonnees_des_erreurs[j], 5);
				}
			}
		}

		/*
		il faudrait faire un test du genre:
		si timer > 120 --> arret du timer + on sort de la boucle pour attribuer une note de 1/5
		
		if ()
		{
			/
		}
		*/
	}

	// arret du timer

	// partie "résultat" :

	int timer; // timer = la valeur à laquelle le timer s'est arreté

	if (timer < 20)
	{
		// on attribue une note de 5/5
	}

	else if (20 < timer < 30)
	{
		// on attribue une note de 4/5
	}

	else if (30 < timer < 40)
	{
		// on attribue une note de 3/5
	}

	else if (40 < timer < 50)
	{
		// on attribue une note de 2/5
	}

	else
	{
		// on attribue une note de 1/5
		// on arrete le timer
	}

	// on retourne la note

}

void jeu_reflexe() // COORDONNEES A DETERMINER jeu où l'on doit cliquer le plus rapidement dans une case
{
	int x_alea = rand(20) % 780;
	int y_alea = rand(100) % 600;
	int temps_alea = rand() % 20;

	sleep(temps_alea);

	// affiche aléatoire du carré
	couleurCourante(255, 0, 0);
	rectangle(x_alea, y_alea, x_alea + 20, y_alea + 20);

	// zone cliquable

	// début du timer

	while (x_alea <= abscisseSouris() <= x_alea + 20 && y_alea <= ordonneeSouris() <= y_alea + 20 && ) // tant qu'il n'y a pas de clic et 
	//que les coordonnées de la souris n'appartiennet pas au carré, ne rien faire
	{
		sleep(0.01);
	}
	// double timer = temps du timer;
	
	// fin timer

	if (timer < 0.2)
	{
		// on attribue une note de 5/5
	}

	if (0.2 <= timer < 0.4)
	{
		// on attribue une note de 4/5
	}

	if (0.4 <= timer < 0.6)
	{
		// on attribue une note de 3/5
	}

	if (0.8 <= timer < 1.0)
	{
		// on attribue une note de 2/5
	}

	else
	{
		// on attribue une note de 1/5
	}

	// on retourne la note

}