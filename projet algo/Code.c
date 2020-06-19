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
				
				case 'Q': /* Pour sortir quelque peu proprement du programme */
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

	//début du timer

	while (erreurs != 7)
	{
		if (/* condition */) // si clic correspond a l'erreur --> partie Sam ?
		{
			erreurs++;

			// on affiche un cercle rouge de 3 de large et de 10 de diametre aux endroits du clic
		}
	}

	// arret du timer

	// partie "résultat" :

	int timer; // timer = la valeur à laquelle le timer s'est arreté

	if (timer < 30)
	{
		// 
	}
}