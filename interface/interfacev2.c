#include "header.h"
#define LargeurFenetre 1280
#define HauteurFenetre 800
#define PtDonneesImageRGB DonneesImageRGB*

void gestionEvenement(EvenementGfx evenement);

/* Image modifiée */
void cree3matrices(int matR[][256], int matV[][256],int matB[][256], DonneesImageRGB* dataRGB);
void creeImage(int matR[][256], int matV[][256],int matB[][256], DonneesImageRGB* dataRGB);

/* fonction du clic bouton */
int onClic();

/*fonction affichage*/
void affichage();

//fenetre 
int largeurFenetrePrincipal = 1280;
int hauteurFenetrePrincipal = 800;
//scene
int scene=0;
//matrices
int matR[256][256];
int matV[256][256];
int matB[256][256];
int matGris[256][256];

DonneesImageRGB *image = NULL;
DonneesImageRGB *dataRGB = NULL;

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
			image = lisBMPRGB("bmp/flying.bmp");
			dataRGB = lisBMPRGB("bmp/flying.bmp");
			cree3matrices(matR, matV, matB, dataRGB);
		break;
		
		
		case Temporisation:
			rafraichisFenetre();
			break;

		case Affichage:
			//affichage d'une fenetre grise clair
			effaceFenetre (230, 230, 230);
			affichage();
			/*creeImage(matR, matV, matB, dataRGB);
			if (image != NULL) // Si l'image a pu etre lue
			{
				// On affiche l'image
				ecrisImage((largeurFenetrePrincipal-image->largeurImage*2)/4,  hauteurFenetrePrincipal*2/3-(image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
				ecrisImage((largeurFenetrePrincipal*3-dataRGB->largeurImage*2)/4,  hauteurFenetrePrincipal*2/3-(dataRGB->hauteurImage)/2, dataRGB->largeurImage, dataRGB->hauteurImage, dataRGB->donneesRGB);
			}*/
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
			// Donc le systeme nous en informe
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;
		case Souris:
			break;
	}
}

//fonction matrices RGB
void cree3matrices(int matR[][256], int matV[][256],int matB[][256], DonneesImageRGB* dataRGB){
	int line, col;
	for(line=0; line < dataRGB->hauteurImage; line++){
		for(col=0; col < dataRGB->largeurImage; col++){
			matR[line][col] = dataRGB->donneesRGB[(line*dataRGB->largeurImage+col)*3];
			matV[line][col] = dataRGB->donneesRGB[((line*dataRGB->largeurImage+col)*3)+1];
			matB[line][col] = dataRGB->donneesRGB[((line*dataRGB->largeurImage+col)*3)+2];
		}
	}
}

//fonction 
void creeImage(int matR[][256], int matV[][256],int matB[][256], DonneesImageRGB* dataRGB){
	int line, col;
	for(line=0; line < dataRGB->hauteurImage; line++){
		for(col=0; col < dataRGB->largeurImage; col++){
			dataRGB->donneesRGB[(line*dataRGB->largeurImage+col)*3] = matR[line][col];
			dataRGB->donneesRGB[((line*dataRGB->largeurImage+col)*3)+1] = matV[line][col];
			dataRGB->donneesRGB[((line*dataRGB->largeurImage+col)*3)+2] = matB[line][col];
		}
	}
}

int onClic(){
	//selection de langue
	if (scene==0){
		if (abscisseSouris() >= largeurFenetrePrincipal*2/20 && abscisseSouris() <= largeurFenetrePrincipal*8/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/5 && ordonneeSouris() <= hauteurFenetrePrincipal*3/5){
			scene=1;
			return 0;
		}
		else if (abscisseSouris() >= largeurFenetrePrincipal*12/20 && abscisseSouris() <= largeurFenetrePrincipal*18/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/5 && ordonneeSouris() <= hauteurFenetrePrincipal*3/5){
			scene=2;
			return 0;
		}
	}
	//acceuil
	if (scene==1){
		scene=3;
		return 0;
	}
	if (scene==2){
		scene=4;
		return 0;
	}
	//selection d'apptitude
	if (scene==3){
		if (abscisseSouris() >= largeurFenetrePrincipal*2/20 && abscisseSouris() <= largeurFenetrePrincipal*6/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/5 && ordonneeSouris() <= hauteurFenetrePrincipal*3/5){
			scene=5;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*8/20 && abscisseSouris() <= largeurFenetrePrincipal*12/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/5 && ordonneeSouris() <= hauteurFenetrePrincipal*3/5){
			scene=7;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*14/20 && abscisseSouris() <= largeurFenetrePrincipal*18/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/5 && ordonneeSouris() <= hauteurFenetrePrincipal*3/5){
			scene=9;
			return 0;
		}
	}
	if (scene==4){
		if (abscisseSouris() >= largeurFenetrePrincipal*2/20 && abscisseSouris() <= largeurFenetrePrincipal*6/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/5 && ordonneeSouris() <= hauteurFenetrePrincipal*3/5){
			scene=6;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*8/20 && abscisseSouris() <= largeurFenetrePrincipal*12/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/5 && ordonneeSouris() <= hauteurFenetrePrincipal*3/5){
			scene=8;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*14/20 && abscisseSouris() <= largeurFenetrePrincipal*18/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/5 && ordonneeSouris() <= hauteurFenetrePrincipal*3/5){
			scene=10;
			return 0;
		}
	}
	
	return 0;
}

void affichage(){
	if (scene==0){//selection de langue
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*8/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*12/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Selectionnez votre langue", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4-16);
		afficheChaine("Select your language", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4+16);
		afficheChaine("Francais", 30, largeurFenetrePrincipal*4/20, hauteurFenetrePrincipal*5/12);
		afficheChaine("Anglais", 30, largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*5/12);
	}
	if (scene==1){//entrée prénom fr
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Entrez votre nom", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4);
	}
	if (scene==2){//entrée prénom en
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Enter your name", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4);
	}
	if (scene==3){//choix apptitude fr
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*6/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*8/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*12/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Selectionnez l'aptitude a evaluer", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4);
		afficheChaine("Memoire", 30, largeurFenetrePrincipal*3/20, hauteurFenetrePrincipal*5/12);
		afficheChaine("Synchronisation", 30, largeurFenetrePrincipal*17/40, hauteurFenetrePrincipal*5/12);
		afficheChaine("Vitesse d'analyse", 30, largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*5/12);
	}
	if (scene==4){//choix apptitude en
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*6/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*8/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*12/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Select the ability to assess", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4);
		afficheChaine("Memory", 30, largeurFenetrePrincipal*3/20, hauteurFenetrePrincipal*5/12);
		afficheChaine("Synchronization", 30, largeurFenetrePrincipal*17/40, hauteurFenetrePrincipal*5/12);
		afficheChaine("Analysis speed", 30, largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*5/12);
	}

}

