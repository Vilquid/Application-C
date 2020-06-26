#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "../GFX_lib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../GFX_lib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "../GFX_lib/ESLib.h" // Pour utiliser valeurAleatoire()

#define LargeurFenetre 1200
#define HauteurFenetre 800

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


// PROTOYYPES
int jeu_sept_erreurs();
int jeu_reflexe();
void regles();

int jeu_sept_erreurs()
{
	// choix de l'image
	int nombre_alea = rand() % 100;

	if (nombre_alea <= 25) // image 1
	{
		int abscisses_des_erreurs[7] = {;;;;;;}; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
		int ordonnees_des_erreurs[7] = {;;;;;;};

		image = lisRGB("erreurs_1.jpg"); // chemins à redéterminer

		if (image != NULL) // Si l'image a pu etre lue
		{
			ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
		}
	}

	if (25 < nombre_alea <= 50) // image 2
	{
		int abscisses_des_erreurs[7] = {;;;;;;}; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
		int ordonnees_des_erreurs[7] = {;;;;;;};

		image = lisRGB("erreurs_2.jpg"); // chemins à redéterminer
		
		if (image != NULL) // Si l'image a pu etre lue
		{
			ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
		}
	}

	else if (50 < nombre_alea <= 75) // image 3
	{
		int abscisses_des_erreurs[7] = {;;;;;;}; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
		int ordonnees_des_erreurs[7] = {;;;;;;};

		image = lisRGB("erreurs_3.jpg"); // chemins à redéterminer
		
		if (image != NULL) // Si l'image a pu etre lue
		{
			ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
		}
	}

	else // image 4
	{
		int abscisses_des_erreurs[7] = {;;;;;;}; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
		int ordonnees_des_erreurs[7] = {;;;;;;};

		image = lisRGB("erreurs_4.jpg"); // chemins à redéterminer
		
		if (image != NULL) // Si l'image a pu etre lue
		{
			ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
		}
	}
	
	int erreurs = 0;
	int clic = 0;
	int note = 0;
	int timer; // timer = la valeur à laquelle le timer s'est arreté

	//début du timer

	while (erreurs != 7 || clic > 10)
	{
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (abscisses_des_erreurs[i] - 10 <= abscisseSouris() && abscisseSouris() <= abscisses_des_erreurs[i] + 10 && ordonnees_des_erreurs[j] - 10 <= ordonneeSouris() && ordonneeSouris() <= ordonnees_des_erreurs[j] - 10 && etatBoutonSouris() == GaucheAppuye) // si clic correspond a l'erreur
				{
					erreurs++;
					clic++;

					couleurCourante(255, 0, 0);
					epaisseurDeTrait(2);
					cercle(abscisses_des_erreurs[i], ordonnees_des_erreurs[j], 15);
				}
			}
		}
	}

	// arret du timer

	// partie "résultat" :

	if (timer < 20)
	{
		note = 5;
	}

	else if (20 < timer < 30)
	{
		note = 4;
	}

	else if (30 < timer < 40)
	{
		note = 3;
	}

	else if (40 < timer < 50)
	{
		note = 2;
	}

	else
	{
		note = 1;
	}

	return note;
}

int jeu_reflexe() // jeu où l'on doit cliquer le plus rapidement dans une case
{
	int x_alea = rand(20) % 780;
	int y_alea = rand(100) % 600;
	int temps_alea = rand() % 20;
	int note = 0;

	sleep(temps_alea);

	// affiche aléatoire du carré
	couleurCourante(255, 51, 0);
	rectangle(x_alea, y_alea, x_alea + 20, y_alea + 20);

	// début du timer

	while (x_alea <= abscisseSouris() && abscisseSouris() <= x_alea + 20 && y_alea <= ordonneeSouris() && ordonneeSouris() <= y_alea + 20 && etatBoutonSouris() == GaucheAppuye)
	// tant qu'il n'y a pas de clic et que les coordonnées de la souris n'appartiennet pas au carré, ne rien faire
	{
		sleep(0.01);
	}

	// double timer = temps du timer;
	
	// fin timer

	if (timer < 0.2)
	{
		note = 5;
	}

	if (0.2 <= timer < 0.4)
	{
		note = 4;
	}

	if (0.4 <= timer < 0.6)
	{
		note = 3;
	}

	if (0.8 <= timer < 1.0)
	{
		note = 2;
	}

	else
	{
		note = 1;
	}

	return note;
}

void regles()
{
	couleurCourante(200, 200, 200);
	rectangle(0, 0, 30, 10);

	couleurCourante(0, 0, 0);
	afficheChaine("Règles", 5, 0, 2);

	if (0 <= abscisseSouris() && abscisseSouris() <= 30 && 0 <= ordonneeSouris() && ordonneeSouris() <= 10 && etatBoutonSouris() == GaucheAppuye)
	{
		effacefenetre();

		epaisseurDeTrait(4);

		couleurCourante(200, 200, 200);
		rectangle(5, HauteurFenetre - 105, LargeurFenetre - 5, HauteurFenetre - 5);
		couleurCourante(0, 0, 0);
		afficheChaine("Test des réflexes", 20, 10, HauteurFenetre - 30); // taille ploice, a
		afficheChaine("Principe du jeu : il faut, le plus rapidement possible, cliquer dans le carré rouge qui apparait à l'écran.", 20, 10, HauteurFenetre - 80);


		couleurCourante(200, 200, 200);
		rectangle(5, HauteurFenetre - 210, LargeurFenetre - 5, HauteurFenetre - 110);
		couleurCourante(0, 0, 0);
		afficheChaine("Test des 7 différences", 20, 10, HauteurFenetre - 135);
		afficheChaine("Principe du jeu : ", 20, 10, HauteurFenetre - 185);

		couleurCourante(200, 200, 200);
		rectangle(5, HauteurFenetre - 325, LargeurFenetre - 5, HauteurFenetre - 225);
		couleurCourante(0, 0, 0);
		afficheChaine("Test du Simon", 20, 10, HauteurFenetre - 250);
		afficheChaine("Principe du jeu : une séquence de couleurs vous est montrée, à vous de la reproduire en cliquant sur des outons colorés.", 20, 10, HauteurFenetre - 300);

		couleurCourante(200, 200, 200);
		rectangle(5, HauteurFenetre - 430, LargeurFenetre - 5, HauteurFenetre - 330);
		couleurCourante(0, 0, 0);
		afficheChaine("Test Memory", 20, 10, HauteurFenetre - 355);
		afficheChaine("Principe du jeu : Cliquez sur 2 images retournées afin de rassembler les paires, attention aux mauvaises associations", 20, 10, HauteurFenetre - 405);

		couleurCourante(200, 200, 200);
		rectangle(5, HauteurFenetre - 535, LargeurFenetre - 5, HauteurFenetre - 435);
		couleurCourante(0, 0, 0);
		afficheChaine("Test des couleurs", 20, 10, HauteurFenetre - 460);
		afficheChaine("Principe du jeu : Détermiez le plus rapidement possible la couleur dans laquelle le mot est écrit.", 20, 10, HauteurFenetre - 510);

		couleurCourante(200, 200, 200);
		rectangle(5, HauteurFenetre - 640, LargeurFenetre - 5, HauteurFenetre - 540);
		couleurCourante(0, 0, 0);
		afficheChaine("Test de l'alphabet", 20, 10, HauteurFenetre - 565);
		afficheChaine("Principe du jeu : une lettre s'affiche à l'écran et vous devez appuyer sur la lettre qui la précède puis celle qui la suit dans l'alphabet.", 20, 10, HauteurFenetre - 615);
	}
}
