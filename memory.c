#include "header.h"

#define LargeurFenetre 1280
#define HauteurFenetre 800

#define PtDonneesImageRGB DonneesImageRGB*

void gestionEvenement(EvenementGfx evenement);

/* fonction du clic bouton */
int onClic();

//________________________________________________________________________________________________________________mes prototypes
void memory1();
void memory();
int score = 0;
DonneesImageRGB *image = NULL;


int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	
	prepareFenetreGraphique("GfxLib", LargeurFenetre, HauteurFenetre);
	
	lanceBoucleEvenements();
	
	return 0;
}



void gestionEvenement(EvenementGfx evenement){
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	
	switch ( evenement){
		case Initialisation:
			dos = lisBMPRGB("../image/carte.bmp");
			image1 = lisBMPRGB("../image/as.bmp");
			image2 = lisBMPRGB("../image/2.bmp");
			image3 = lisBMPRGB("../image/3.bmp");
			image4 = lisBMPRGB("../image/4.bmp");
			image5 = lisBMPRGB("../image/5.bmp");
			debutChrono();
		break;
		
		case Temporisation:
			rafraichisFenetre();
			break;

		case Affichage:
			//affichage d'une fenetre grise clair
			effaceFenetre (230, 230, 230);
			memory1();//______________________________________________________________________________________________truc à mettre dans la scene du jeu
		break;
			

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye){
				onClic();
				rafraichisFenetre();
			}
		break;
		
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());
			switch (caractereClavier())
			{
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
			printf("ASCII %d\n", toucheClavier());
			break;

		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;

		case Souris:
			break;
	
	}
	

}


/* -------------------------- Clic ------------------------ */

int onClic(){
	if (scene== ) {  //_________________________________________________________________________________________________________________________________rajouter la scène du jeu en conditions
		if (abscisseSouris() >= 62 && abscisseSouris() <= 194 && ordonneeSouris() >= HauteurFenetre * 2 / 3 && ordonneeSouris() <= HauteurFenetre * 2 / 3 + 185) {
			return 1;
		}

		else if (abscisseSouris() >= 62 + 256 && abscisseSouris() <= 194 && ordonneeSouris() >= HauteurFenetre * 2 / 3 && ordonneeSouris() <= HauteurFenetre * 2 / 3 + 185) {
			return 2;
		}

		else if (abscisseSouris() >= 62 + (256 * 2) && abscisseSouris() <= 194 && ordonneeSouris() >= HauteurFenetre * 2 / 3 && ordonneeSouris() <= HauteurFenetre * 2 / 3 + 185) {
			return 3;
		}

		else if (abscisseSouris() >= 62 + (256 * 3) && abscisseSouris() <= 194 && ordonneeSouris() >= HauteurFenetre * 2 / 3 && ordonneeSouris() <= HauteurFenetre * 2 / 3 + 185) {
			return 4;
		}

		else if (abscisseSouris() >= 62 + (256 * 4) && abscisseSouris() <= 194 && ordonneeSouris() >= HauteurFenetre * 2 / 3 && ordonneeSouris() <= HauteurFenetre * 2 / 3 + 185) {
			return 5;
		}

		else if (abscisseSouris() >= 62 && abscisseSouris() <= 194 && ordonneeSouris() >= HauteurFenetre / 3 && ordonneeSouris() <= HauteurFenetre * 2 / 3 + 185) {
			return 6;
		}

		else if (abscisseSouris() >= 62 + 256 && abscisseSouris() <= 194 && ordonneeSouris() >= HauteurFenetre / 3 && ordonneeSouris() <= HauteurFenetre * 2 / 3 + 185) {
			return 7;
		}

		else if (abscisseSouris() >= 62 + (256 * 2) && abscisseSouris() <= 194 && ordonneeSouris() >= HauteurFenetre / 3 && ordonneeSouris() <= HauteurFenetre * 2 / 3 + 185) {
			return 8;
		}

		else if (abscisseSouris() >= 62 + (256 * 3) && abscisseSouris() <= 194 && ordonneeSouris() >= HauteurFenetre / 3 && ordonneeSouris() <= HauteurFenetre * 2 / 3 + 185) {
			return 9;
		}

		else if (abscisseSouris() >= 62 + (256 * 4) && abscisseSouris() <= 194 && ordonneeSouris() >= HauteurFenetre / 3 && ordonneeSouris() <= HauteurFenetre * 2 / 3 + 185) {
			return 10;
		}
	}

	return 0;
}

void memory1() { //________________________________________________________________________________________________________________________________________________________truc appelé dans la scene du jeu (genre dans la scene tu met juste ça)
	if (image != NULL) 
	{
		score = 0;
		effaceFenetre(230, 230, 230);
		// On affiche l'image
		ecrisImage((LargeurFenetre - dos->largeurImage * 7) / 5, HauteurFenetre * 2 / 3 - (dos->hauteurImage) / 2, dos->largeurImage, dos->hauteurImage, dos->donneesRGB);
		ecrisImage((LargeurFenetre - dos->largeurImage * 7) * 2 / 5, HauteurFenetre * 2 / 3 - (dos->hauteurImage) / 2, dos->largeurImage, dos->hauteurImage, dos->donneesRGB);
		ecrisImage((LargeurFenetre - dos->largeurImage * 7) * 3 / 5, HauteurFenetre * 2 / 3 - (dos->hauteurImage) / 2, dos->largeurImage, dos->hauteurImage, dos->donneesRGB);
		ecrisImage((LargeurFenetre - dos->largeurImage * 7) * 4 / 5, HauteurFenetre * 2 / 3 - (dos->hauteurImage) / 2, dos->largeurImage, dos->hauteurImage, dos->donneesRGB);
		ecrisImage((LargeurFenetre - dos->largeurImage * 7), HauteurFenetre * 2 / 3 - (dos->hauteurImage) / 2, dos->largeurImage, dos->hauteurImage, dos->donneesRGB);
		ecrisImage((LargeurFenetre - dos->largeurImage * 7) / 5, HauteurFenetre / 3 - (dos->hauteurImage) / 2, dos->largeurImage, dos->hauteurImage, dos->donneesRGB);
		ecrisImage((LargeurFenetre - dos->largeurImage * 7) * 2 / 5, HauteurFenetre / 3 - (dos->hauteurImage) / 2, dos->largeurImage, dos->hauteurImage, dos->donneesRGB);
		ecrisImage((LargeurFenetre - dos->largeurImage * 7) * 3 / 5, HauteurFenetre / 3 - (dos->hauteurImage) / 2, dos->largeurImage, dos->hauteurImage, dos->donneesRGB);
		ecrisImage((LargeurFenetre - dos->largeurImage * 7) * 4 / 5, HauteurFenetre / 3 - (dos->hauteurImage) / 2, dos->largeurImage, dos->hauteurImage, dos->donneesRGB);
		ecrisImage((LargeurFenetre - dos->largeurImage * 7), HauteurFenetre / 3 - (dos->hauteurImage) / 2, dos->largeurImage, dos->hauteurImage, dos->donneesRGB);
	}
	else {
		couleurCourante(0, 0, 0);
		epaisseurDeTrait(4);
		afficheChaine("Erreur", 30, LargeurFenetre / 3, HauteurFenetre * 3 / 4 + 16);
	}
	memory();
}


void memory() {//____________________________________________________________________________________________________________________________________________________________________appelé tout seul dans la scene du jeu
	int click1 = onclick();
	if (click1 == 1) {
		ecrisImage((LargeurFenetre - image2->largeurImage * 7) / 5, HauteurFenetre * 2 / 3 - (image2->hauteurImage) / 2, image2->largeurImage, image2->hauteurImage, image2->donneesRGB);
	}
	if (click1 == 2) {
		ecrisImage((LargeurFenetre - image1->largeurImage * 7) * 2 / 5, HauteurFenetre * 2 / 3 - (image1->hauteurImage) / 2, image1->largeurImage, image1->hauteurImage, image1->donneesRGB);
	}
	if (click1 == 3) {
		ecrisImage((LargeurFenetre - image5->largeurImage * 7) * 3 / 5, HauteurFenetre * 2 / 3 - (image5->hauteurImage) / 2, image5->largeurImage, image5->hauteurImage, image5->donneesRGB);
	}
	if (click1 == 4) {
		ecrisImage((LargeurFenetre - image2->largeurImage * 7) * 4 / 5, HauteurFenetre * 2 / 3 - (image2->hauteurImage) / 2, image2->largeurImage, image2->hauteurImage, image2->donneesRGB);
	}
	if (click1 == 5) {
		ecrisImage((LargeurFenetre - image4->largeurImage * 7), HauteurFenetre * 2 / 3 - (image4->hauteurImage) / 2, image4->largeurImage, image4->hauteurImage, image4->donneesRGB);
	}
	if (click1 == 6) {
		ecrisImage((LargeurFenetre - image3->largeurImage * 7) / 5, HauteurFenetre / 3 - (image3->hauteurImage) / 2, image3->largeurImage, image3->hauteurImage, image3->donneesRGB);
	}
	if (click1 == 7) {
		ecrisImage((LargeurFenetre - image4->largeurImage * 7) * 2 / 5, HauteurFenetre / 3 - (image4->hauteurImage) / 2, image4->largeurImage, image4->hauteurImage, image4->donneesRGB);
	}
	if (click1 == 8) {
		ecrisImage((LargeurFenetre - image1->largeurImage * 7) * 3 / 5, HauteurFenetre / 3 - (image1->hauteurImage) / 2, image1->largeurImage, image1->hauteurImage, image1->donneesRGB);
	}
	if (click1 == 9) {
		ecrisImage((LargeurFenetre - image5->largeurImage * 7) * 4 / 5, HauteurFenetre / 3 - (image5->hauteurImage) / 2, image5->largeurImage, image5->hauteurImage, image5->donneesRGB);
	}
	if (click1 == 10) {
		ecrisImage((LargeurFenetre - image3->largeurImage * 7), HauteurFenetre / 3 - (image3->hauteurImage) / 2, image3->largeurImage, image3->hauteurImage, image3->donneesRGB);
	}


	int click2 = onclick();
	if (click2 == 1) {
		ecrisImage((LargeurFenetre - image2->largeurImage * 7) / 5, HauteurFenetre * 2 / 3 - (image2->hauteurImage) / 2, image2->largeurImage, image2->hauteurImage, image2->donneesRGB);
	}
	if (click2 == 2) {
		ecrisImage((LargeurFenetre - image1->largeurImage * 7) * 2 / 5, HauteurFenetre * 2 / 3 - (image1->hauteurImage) / 2, image1->largeurImage, image1->hauteurImage, image1->donneesRGB);
	}
	if (click2 == 3) {
		ecrisImage((LargeurFenetre - image5->largeurImage * 7) * 3 / 5, HauteurFenetre * 2 / 3 - (image5->hauteurImage) / 2, image5->largeurImage, image5->hauteurImage, image5->donneesRGB);
	}
	if (click2 == 4) {
		ecrisImage((LargeurFenetre - image2->largeurImage * 7) * 4 / 5, HauteurFenetre * 2 / 3 - (image2->hauteurImage) / 2, image2->largeurImage, image2->hauteurImage, image2->donneesRGB);
	}
	if (click2 == 5) {
		ecrisImage((LargeurFenetre - image4->largeurImage * 7), HauteurFenetre * 2 / 3 - (image4->hauteurImage) / 2, image4->largeurImage, image4->hauteurImage, image4->donneesRGB);
	}
	if (click2 == 6) {
		ecrisImage((LargeurFenetre - image3->largeurImage * 7) / 5, HauteurFenetre / 3 - (image3->hauteurImage) / 2, image3->largeurImage, image3->hauteurImage, image3->donneesRGB);
	}
	if (click2 == 7) {
		ecrisImage((LargeurFenetre - image4->largeurImage * 7) * 2 / 5, HauteurFenetre / 3 - (image4->hauteurImage) / 2, image4->largeurImage, image4->hauteurImage, image4->donneesRGB);
	}
	if (click2 == 8) {
		ecrisImage((LargeurFenetre - image1->largeurImage * 7) * 3 / 5, HauteurFenetre / 3 - (image1->hauteurImage) / 2, image1->largeurImage, image1->hauteurImage, image1->donneesRGB);
	}
	if (click2 == 9) {
		ecrisImage((LargeurFenetre - image5->largeurImage * 7) * 4 / 5, HauteurFenetre / 3 - (image5->hauteurImage) / 2, image5->largeurImage, image5->hauteurImage, image5->donneesRGB);
	}
	if (click2 == 10) {
		ecrisImage((LargeurFenetre - image3->largeurImage * 7), HauteurFenetre / 3 - (image3->hauteurImage) / 2, image3->largeurImage, image3->hauteurImage, image3->donneesRGB);
	}

	finChrono();
	temps = 240 - (temps2 - temps1);
	if (temps == 0) {
		score=5; //c'est pas le cas mais comme ça on sort du truc sans avoir une autre variable
	}

	if (click1 == click2) {
		score = score + 1;
	}
	else {
		memory1();
	}

	if (score == 5) {
		// arret du timer
		finChrono();
		// partie "résultat" :

		timer = temps2 - temps1; // timer = la valeur à laquelle le timer s'est arreté

		if (timer < 48)
		{
			note1 = 5;
		}

		else if (48 <= timer && timer < 96)
		{
			note1 = 4;
		}

		else if (96 <= timer && timer < 144)
		{
			note1 = 3;
		}

		else if (144 <= timer && timer < 192)
		{
			note1 = 2;
		}

		else
		{
			note1 = 1;
		}
		scene = 11;
	}
}

void debutChrono() {
	temps1 = time(NULL);
}
void finChrono() {
	temps2 = time(NULL);
}
