#include "header.h"
#define LargeurFenetre 1280
#define HauteurFenetre 800
#define PtDonneesImageRGB DonneesImageRGB*

/*fonctions utiles*/
void delay(int);



/*gfx*/
void gestionEvenement(EvenementGfx evenement);
/* fonction du clic bouton */
int onClic();
/*fonction affichage*/
void affichage();
/*prototype jeux*/
void jeucouleur();






//fenetre 
int largeurFenetrePrincipal = 1280;
int hauteurFenetrePrincipal = 800;
//scene
int scene=0;
//jeu de couleur
int i=0, juste=0, iteration=0, erreur=0, fauxbuffer=0, millisecondesEntreAppels=5000;
char rep[11]="salutation";




/* Image modifiée */
void cree3matrices(int matR[][256], int matV[][256],int matB[][256], DonneesImageRGB* dataRGB);
void creeImage(int matR[][256], int matV[][256],int matB[][256], DonneesImageRGB* dataRGB);
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
			rafraichisFenetre();
			demandeTemporisation(20);
			/*image = lisBMPRGB("bmp/flying.bmp");
			dataRGB = lisBMPRGB("bmp/flying.bmp");
			cree3matrices(matR, matV, matB, dataRGB);*/
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
				printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
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
		if (abscisseSouris() >= largeurFenetrePrincipal*2/20 && abscisseSouris() <= largeurFenetrePrincipal*8/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=1;
			return 0;
		}
		else if (abscisseSouris() >= largeurFenetrePrincipal*12/20 && abscisseSouris() <= largeurFenetrePrincipal*18/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=2;
			return 0;
		}
	}
	//bouton retour/quitter
	if (abscisseSouris() >= largeurFenetrePrincipal*17/20 && abscisseSouris() <= largeurFenetrePrincipal && ordonneeSouris() >= 0 && ordonneeSouris() <= hauteurFenetrePrincipal*2/20){
		if (scene==0){
			termineBoucleEvenements();
		}
		else if (scene==3 || scene==4){
			scene=scene-2;
			return 0;
		}
		else if (scene==5 || scene==7 || scene==9){
			scene=3;
			return 0;
		}
		else if (scene==6 || scene==8 || scene==10){
			scene=4;
			return 0;
		}
		else if (scene==1 || scene==2){
			scene=0;
			return 0;
		}
		
		return 0;
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
		if (abscisseSouris() >= largeurFenetrePrincipal*2/20 && abscisseSouris() <= largeurFenetrePrincipal*6/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=5;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*8/20 && abscisseSouris() <= largeurFenetrePrincipal*12/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=7;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*14/20 && abscisseSouris() <= largeurFenetrePrincipal*18/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=9;
			return 0;
		}
	}
	if (scene==4){
		if (abscisseSouris() >= largeurFenetrePrincipal*2/20 && abscisseSouris() <= largeurFenetrePrincipal*6/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=6;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*8/20 && abscisseSouris() <= largeurFenetrePrincipal*12/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=8;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*14/20 && abscisseSouris() <= largeurFenetrePrincipal*18/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=10;
			return 0;
		}
	}
	if (scene==9){
		if (abscisseSouris() >= largeurFenetrePrincipal*2/20 && abscisseSouris() <= largeurFenetrePrincipal*6/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=23;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*8/20 && abscisseSouris() <= largeurFenetrePrincipal*12/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=25;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*14/20 && abscisseSouris() <= largeurFenetrePrincipal*18/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=27;
			return 0;
		}
	}
	
	return 0;
}

/*sommaire scènes:
 * scène 0=selection de langue
 * scène 1=entrée prénom fr
 * scène 2=entrée prénom en
 * scène 3=choix apptitude fr
 * scène 4=choix apptitude en
 * 
 * scène 5=mémoire fr
 * scène 6=mémoire en
 * scène 7=synchro fr
 * scène 8=synchro en
 * scène 9=vitesse analyse fr
 * scène 10=vitesse analyse en
 * 
 * scène 11=jeu 1 mémoire fr
 * scène 12=jeu 1 mémoire en
 * scène 13=jeu 2 mémoire fr
 * scène 14=jeu 2 mémoire en
 * scène 15=résultats mémoire fr
 * scène 16=résultats mémoire en
 * scène 17=jeu 1 synchro fr
 * scène 18=jeu 1 synchro en
 * scène 19=jeu 2 synchro fr
 * scène 20=jeu 2 synchro en
 * scène 21=résultats synchro fr
 * scène 22=résultats synchro en
 * scène 23=jeu de couleur vitesse analyse fr
 * scène 24=jeu de couleur vitesse analyse en
 * scène 25=jeu 2 vitesse analyse fr
 * scène 26=jeu 2 vitesse analyse en
 * scène 27=résultats vitesse analyse fr
 * scène 28=résultats vitesse analyse en
 * 
 * 
*/


void affichage(){
	//bouton retour/quitter
	couleurCourante(200,200,200);
	rectangle(largeurFenetrePrincipal*17/20, 0, largeurFenetrePrincipal, hauteurFenetrePrincipal*2/20);
	
	if (scene!=0){
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Retour", 30, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal/25);
	}
	//-------------------------------------------------------------------------------------selections-------------------------------------------------------------------------------------//
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
		afficheChaine("Quitter", 30, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal/25);
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
	
	//-------------------------------------------------------------------------------------Menu par catégorie-------------------------------------------------------------------------------------//
	if (scene==5){//mémoire fr
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*6/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*8/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*12/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Selectionnez un test", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4);
		afficheChaine("Memory", 30, largeurFenetrePrincipal*3/20, hauteurFenetrePrincipal*5/12);
		afficheChaine("Simon", 30, largeurFenetrePrincipal*17/40, hauteurFenetrePrincipal*5/12);
		afficheChaine("Resultats", 30, largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*5/12);
	}
	if (scene==6){//mémoire en
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*6/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*8/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*12/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Select a test", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4);
		afficheChaine("concentration", 30, largeurFenetrePrincipal*3/20, hauteurFenetrePrincipal*5/12);
		afficheChaine("Simon", 30, largeurFenetrePrincipal*17/40, hauteurFenetrePrincipal*5/12);
		afficheChaine("Results", 30, largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*5/12);
	}
	if (scene==7){//synchro fr
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*6/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*8/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*12/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Selectionnez un test", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4);
		afficheChaine("jeu1", 30, largeurFenetrePrincipal*3/20, hauteurFenetrePrincipal*5/12);
		afficheChaine("jeu2", 30, largeurFenetrePrincipal*17/40, hauteurFenetrePrincipal*5/12);
		afficheChaine("Resultats", 30, largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*5/12);
	}
	if (scene==8){//synchro en
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*6/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*8/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*12/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Select a test", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4);
		afficheChaine("game1", 30, largeurFenetrePrincipal*3/20, hauteurFenetrePrincipal*5/12);
		afficheChaine("game2", 30, largeurFenetrePrincipal*17/40, hauteurFenetrePrincipal*5/12);
		afficheChaine("Results", 30, largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*5/12);
	}
	if (scene==9){//vitesse analyse fr
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*6/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*8/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*12/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Selectionnez un test", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4);
		afficheChaine("jeu1", 30, largeurFenetrePrincipal*3/20, hauteurFenetrePrincipal*5/12);
		afficheChaine("jeu2", 30, largeurFenetrePrincipal*17/40, hauteurFenetrePrincipal*5/12);
		afficheChaine("Resultats", 30, largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*5/12);
	}
	if (scene==10){//vitesse analyse en
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*6/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*8/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*12/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Select a test", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4);
		afficheChaine("game1", 30, largeurFenetrePrincipal*3/20, hauteurFenetrePrincipal*5/12);
		afficheChaine("game2", 30, largeurFenetrePrincipal*17/40, hauteurFenetrePrincipal*5/12);
		afficheChaine("Results", 30, largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*5/12);
	}
	//----------------------------------------------------------------------------------------règles---------------------------------------------------------------------------------------//
	/*
	if (scene==5||scene==7||scene==9){
		couleurCourante(200,200,200);
		rectangle(0, 0, largeurFenetrePrincipal*3/20, hauteurFenetrePrincipal*2/20);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Regles", 30, largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal/25);
	}
	if (scene==6||scene==8||scene==10){
		couleurCourante(200,200,200);
		rectangle(0, 0, largeurFenetrePrincipal*3/20, hauteurFenetrePrincipal*2/20);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Regles", 30, largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal/25);
	}
	*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//-------------------------------------------------------------------------------------scènes jeux-------------------------------------------------------------------------------------//
	if (scene==23){//jeu de couleur
		i=(rand()%3);
			couleurCourante(255,0,0);
			rectangle(400,250,880,550);
			if(i==0){
				couleurCourante(0,0,255);
				epaisseurDeTrait(6);
				afficheChaine("GRIS",60,580,380);
				}
			else if(i==1){
				couleurCourante(255,255,0);
				epaisseurDeTrait(6);
				afficheChaine("ROUGE",60,540,380);
				}
			else if(i==2){
				couleurCourante(255,255,255);
				epaisseurDeTrait(6);
				afficheChaine("BLEU",60,580,380);
				}
			jeucouleur();
		}

}





//-------------------------------------------------------------------------------------jeux-------------------------------------------------------------------------------------//
void jeucouleur(){
	//Zone fonction avec aléat sur couleur courante 
	//demandeTemporisation(5000);
	//i=(rand()%3); A chaque fois que scanf touche i change donc on a le putain de bloquant ENFIN !!!!
		if (fauxbuffer==0){
			fauxbuffer=1;
		 }
		else{
			if(i==0){
				scanf("%s",rep);
				if((strcmp(rep,"bleu"))==0){
					juste=juste+1;
					iteration=iteration+1;
					}
				else{erreur=erreur+1;}
				}
			else if(i==1){
				scanf("%s",rep);
				if((strcmp(rep,"jaune"))==0){
					juste=juste+1;
					iteration=iteration+1;
					}
				else{erreur=erreur+1;}
			}
			else if(i==2){
				scanf("%s",rep);
				if((strcmp(rep,"blanc"))==0){ 
					juste=juste+1;
					iteration=iteration+1;
					}
				else{erreur=erreur+1;}
			}
			printf("bonne reponses=%d\n", juste);
			printf("erreurs=%d\n", erreur);
		}
	}
