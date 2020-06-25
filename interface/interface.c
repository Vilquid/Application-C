#include "header.h"
#define LargeurFenetre 1280
#define HauteurFenetre 800
#define PtDonneesImageRGB DonneesImageRGB*

void gestionEvenement(EvenementGfx evenement);
/* fonction du clic bouton */
int onClic();
/*fonction affichage*/
void affichage();
/*timer*/
void debutChrono();
void finChrono();
/*jeux*/
void jeucouleur();
void jeuAlphabet();
void jeu_sept_erreurs();
//fenetre 
int largeurFenetrePrincipal = 1280;
int hauteurFenetrePrincipal = 800;
//scene
int scene=0;

//jeu de couleur
int i=0;
int i2=0;
int i3=0;
int i4=0;
int i5=0;
int juste=0;
int juste2=0;
int erreur2=0;
int iteration=0;
int iteration2=0;
int erreur=0;
int fauxbuffer=0;
int fauxbuffer3=0;
char rep[11]="salutation";
char possibilite[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char rep2[2];
char reptemp[2];
int millisecondesEntreAppels=5000;
char pk[0];
int note1=0,note2=0,note3=0,note4=0,note5=0,note6=0;
time_t temps1, temps2;
int temps;

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
	srand(time(NULL));
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
	if (scene==5){
		if (abscisseSouris() >= largeurFenetrePrincipal*2/20 && abscisseSouris() <= largeurFenetrePrincipal*6/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=11;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*8/20 && abscisseSouris() <= largeurFenetrePrincipal*12/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=13;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*14/20 && abscisseSouris() <= largeurFenetrePrincipal*18/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=15;
			return 0;
		}
	}
	if (scene==6){
		if (abscisseSouris() >= largeurFenetrePrincipal*2/20 && abscisseSouris() <= largeurFenetrePrincipal*6/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=12;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*8/20 && abscisseSouris() <= largeurFenetrePrincipal*12/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=14;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*14/20 && abscisseSouris() <= largeurFenetrePrincipal*18/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=16;
			return 0;
		}
	}
	if (scene==7){
		if (abscisseSouris() >= largeurFenetrePrincipal*2/20 && abscisseSouris() <= largeurFenetrePrincipal*6/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=17;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*8/20 && abscisseSouris() <= largeurFenetrePrincipal*12/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=19;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*14/20 && abscisseSouris() <= largeurFenetrePrincipal*18/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=15;
			return 0;
		}
	}
	if (scene==8){
		if (abscisseSouris() >= largeurFenetrePrincipal*2/20 && abscisseSouris() <= largeurFenetrePrincipal*6/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=18;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*8/20 && abscisseSouris() <= largeurFenetrePrincipal*12/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=20;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*14/20 && abscisseSouris() <= largeurFenetrePrincipal*18/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=16;
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
			scene=15;
			return 0;
		}
	}
	if (scene==10){
		if (abscisseSouris() >= largeurFenetrePrincipal*2/20 && abscisseSouris() <= largeurFenetrePrincipal*6/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=24;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*8/20 && abscisseSouris() <= largeurFenetrePrincipal*12/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=26;
			return 0;
		}
		if (abscisseSouris() >= largeurFenetrePrincipal*14/20 && abscisseSouris() <= largeurFenetrePrincipal*18/20 && ordonneeSouris() >= hauteurFenetrePrincipal*2/6 && ordonneeSouris() <= hauteurFenetrePrincipal*3/6){
			scene=16;
			return 0;
		}
	}
	if (abscisseSouris() >= 0 && abscisseSouris() <= largeurFenetrePrincipal*3/20 && ordonneeSouris() >= 0 && ordonneeSouris() <= hauteurFenetrePrincipal*2/20){
		if (scene==5 || scene==7 || scene==9){
			scene=29;
			return 0;
		}
		else if (scene==6 || scene==8 || scene==10){
			scene=30;
			return 0;
		}
	
	return 0;
}

/*sommaire scènes:
 * scène 0=selection de langue
 * scène 110= choix login/register fr
 * scène 1&111=entrée prénom fr
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
 * scène 15=résultats fr
 * scène 16=résultats en
 * scène 17&170=jeu 1 synchro fr
 * scène 18=jeu 1 synchro en
 * scène 19=jeu 2 synchro fr
 * scène 20=jeu 2 synchro en

 * scène 23&230=jeu de couleur vitesse analyse fr
 * scène 24=jeu de couleur vitesse analyse en
 * scène 25=jeu 2 vitesse analyse fr
 * scène 26=jeu 2 vitesse analyse en

 * scene 29=règles fr
 * scène 30=règles en
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
	if (scene==110){//login
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*8/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*12/20, hauteurFenetrePrincipal*2/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*3/6);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Voulez vous vous inscrire ou vous connecter?", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4-16);
		afficheChaine("Inscription", 30, largeurFenetrePrincipal*4/20, hauteurFenetrePrincipal*5/12);
		afficheChaine("connection", 30, largeurFenetrePrincipal*14/20, hauteurFenetrePrincipal*5/12);
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
	//-------------------------------------------------------------------------------------resultats---------------------------------------------------------------------------------------//
	if (scene==15){//résultats fr
		couleurCourante(200,200,200);
		rectangle(largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal*4/6, largeurFenetrePrincipal*18/20, hauteurFenetrePrincipal*5/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Resultats", 30, largeurFenetrePrincipal/3, hauteurFenetrePrincipal*3/4);
	}
	//----------------------------------------------------------------------------------------règles---------------------------------------------------------------------------------------//
	
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
		afficheChaine("Rules", 30, largeurFenetrePrincipal*2/20, hauteurFenetrePrincipal/25);
	}
	if (scene==29){
	}
	if (scene==30){
	}
	
	//-------------------------------------------------------------------------------------scènes jeux-------------------------------------------------------------------------------------//
	if (scene==23){
			jeucouleur();// fonctionne parce que j'ai mit un buffer !!!! donc un qui part dans le vide
			scene=230; 
		}
	if (scene==230){//jeu de couleur
			
			effaceFenetre(255,255,255);

			i3=(rand()%255);
			i4=(rand()%255);
			i5=(rand()%255);
			i=(rand()%8);
			couleurCourante(i3,i4,i5);
			rectangle(400,250,880,550);
			
			if(i==0){
				couleurCourante(0,0,255);
				epaisseurDeTrait(6);
				afficheChaine("GRIS",60,580,380);
			}
				
			if(i==1){
				couleurCourante(255,255,0);
				epaisseurDeTrait(6);
				afficheChaine("ROUGE",60,540,380);
			}
				
			if(i==2){
				couleurCourante(255,255,255);
				epaisseurDeTrait(6);
				afficheChaine("BLEU",60,580,380);
			}
				
			if(i==3){
				couleurCourante(96,96,96);
				epaisseurDeTrait(6);
				afficheChaine("MARRON",60,580,380);
			}
				
			if(i==4){
				couleurCourante(237,127,16);
				epaisseurDeTrait(6);
				afficheChaine("NOIR",60,540,380);
			}
				
			if(i==5){
				couleurCourante(253,108,158);
				epaisseurDeTrait(6);
				afficheChaine("BLEU",60,580,380);
			}
				
			if(i==6){
				couleurCourante(102,0,153);
				epaisseurDeTrait(6);
				afficheChaine("ROSE",60,580,380);
			}
				
			if(i==7){
				couleurCourante(0,255,0);
				epaisseurDeTrait(6);
				afficheChaine("VIOLET",60,540,380);
			}
				
			if(i==8){
				couleurCourante(255,255,255);
				epaisseurDeTrait(6);
				afficheChaine("BLANC",60,580,380);
			}
						
			scene=23;
		}
	if (scene==17){
		jeuAlphabet();
	}
	
	if(scene==170){
			i2=(rand()%25);

			switch(i2){
				
				case 0:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("A",60,580,380);
				break;
				
				case 1:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("B",60,580,380);
				break;
				
				case 2:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("C",60,580,380);
				break;
				
				case 3:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("D",60,580,380);
				break;
				
				case 4:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("E",60,580,380);
				break;
				
				case 5:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("F",60,580,380);
				break;
				
				case 6:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("G",60,580,380);
				break;
				
				case 7:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("H",60,580,380);
				break;
				
				case 8:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("I",60,580,380);
				break;
				
				case 9:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("J",60,580,380);
				break;
				
				case 10:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("K",60,580,380);
				break;
				
				case 11:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("L",60,580,380);
				break;
				
				case 12:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("M",60,580,380);
				break;
				
				case 13:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("N",60,580,380);
				break;
				
				case 14:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("O",60,580,380);
				break;
				
				
				case 15:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("P",60,580,380);
				break;
				
				case 16:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("Q",60,580,380);
				break;
				
				case 17:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("R",60,580,380);
				break;
				
				case 18:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("S",60,580,380);
				break;
				
				case 19:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("T",60,580,380);
				break;
				
				case 20:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("U",60,580,380);
				break;
				
				case 21:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("V",60,580,380);
				break;
				
				case 22:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("W",60,580,380);
				break;
				
				case 23:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("X",60,580,380);
				break;
				
				case 24:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("Y",60,580,380);
				break;
				
				case 25:
					couleurCourante(255,0,0);
					epaisseurDeTrait(6);
					afficheChaine("Z",60,580,380);
				break;
			}
			iteration2=iteration2+1;
			scene=17;
	}
	if (scene==25){
		jeu_sept_erreurs();
	}
}
	




//-------------------------------------------------------------------------------------jeux-------------------------------------------------------------------------------------//
void jeuAlphabet(){
	
	if(fauxbuffer3==0){
		fauxbuffer3=1;
		printf("Appuez sur r puis entrée pour démarrer :");
		scanf("%c",pk);
		scene=17;
		}
		
	else if(fauxbuffer3!=0){
		if(iteration2<10){
			printf("%c : ",possibilite[i2]);
			
			scanf("%s",rep2);
			reptemp[0]=possibilite[i2-1];
			reptemp[1]=possibilite[i2+1];
			
			
			if((strcmp(rep2,reptemp))==0){
				printf("Bien vu ! \n");
				juste2=juste2+1;
			}
			
			else{
				erreur2=erreur2+1;
				}
			scene=170;
		}
		else{
			printf("Vous avez %d bonnes reponses : ",juste2);
		}

	}
}

void jeucouleur(){
	//Zone fonction avec aléat sur couleur courante 

		if (fauxbuffer==0){
			fauxbuffer=1;
			printf("Appuez sur r puis entrée pour démarrer :");
			scanf("%c",pk);
		 }
		
		else if (fauxbuffer!=0){
			
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
			
			else if(i==3){
				scanf("%s",rep);

				if((strcmp(rep,"gris"))==0){ 
					juste=juste+1;
					iteration=iteration+1;
					}
				else{erreur=erreur+1;}
			}
			
			else if(i==4){
				scanf("%s",rep);

				if((strcmp(rep,"orange"))==0){ 
					juste=juste+1;
					iteration=iteration+1;
					}
				else{erreur=erreur+1;}
			}
			
			else if(i==5){
				scanf("%s",rep);

				if((strcmp(rep,"rose"))==0){ 
					juste=juste+1;
					iteration=iteration+1;
					}
				else{erreur=erreur+1;}
			}
			
			else if(i==6){
				scanf("%s",rep);

				if((strcmp(rep,"violet"))==0){ 
					juste=juste+1;
					iteration=iteration+1;
					}
				else{erreur=erreur+1;}
			}
			
			else if(i==7){
				scanf("%s",rep);

				if((strcmp(rep,"vert"))==0){ 
					juste=juste+1;
					iteration=iteration+1;
					}
				else{erreur=erreur+1;}
			}
			
			else if(i==8){
				scanf("%s",rep);

				if((strcmp(rep,"blanc"))==0){ 
					juste=juste+1;
					iteration=iteration+1;
					}
				else{erreur=erreur+1;}
			}

			
		}
		printf("\nbonne reponses=%d\n", juste);
		printf("erreurs=%d\n", erreur);
}

void jeu_sept_erreurs()
{
	// choix de l'image
	int nombre_alea = rand() % 100;

	if (nombre_alea <= 25) // image 1
	{
		int abscisses_des_erreurs[7] = {;;;;;;}; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
		int ordonnees_des_erreurs[7] = {;;;;;;};

		// on affiche l'image
	}

	if (25 < nombre_alea <= 50) // image 2
	{
		int abscisses_des_erreurs[7] = {;;;;;;}; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
		int ordonnees_des_erreurs[7] = {;;;;;;};

		// on affiche l'image
	}

	else if (50 < nombre_alea <= 75) // image 3
	{
		int abscisses_des_erreurs[7] = {;;;;;;}; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
		int ordonnees_des_erreurs[7] = {;;;;;;};

		// on affiche l'image
	}

	else // image 4
	{
		int abscisses_des_erreurs[7] = {;;;;;;}; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
		int ordonnees_des_erreurs[7] = {;;;;;;};

		// on affiche l'image
	}
	
	int erreurs = 0;

	//début du timer
	débutChrono();

	while (erreurs != 7)
	{
		for (int i = 0; i < 7; i++)
		{
			if (abscisses_des_erreurs[i] - 10 <= abscisseSouris() <= abscisses_des_erreurs[i] + 10 && ordonnees_des_erreurs - 10 <= ordonneeSouris() <= ordonnees_des_erreurs - 10 && etatBoutonSouris() == GaucheAppuye) // si clic correspond a l'erreur
			{
				erreurs++;
				couleurCourante(255, 0, 0);
				epaisseurDeTrait(2);
				cercle(abscisses_des_erreurs[i], ordonnees_des_erreurs[j], 5);
			}
			
		}
		finChrono();
		temps=120-(temps2-temps1);
		if (temps==0){
			erreurs=7; //c'est pas le cas mais comme ça on sort du truc sans avoir une autre variable
		}
	}

	// arret du timer
	finChrono();
	// partie "résultat" :

	int timer=temps2-temps1; // timer = la valeur à laquelle le timer s'est arreté

	if (timer < 24)
	{
		note6=5;
	}

	else if (24 <= timer < 48)
	{
		note6=4;
	}

	else if (48 <= timer < 72)
	{
		note6=3
	}

	else if (72 <= timer < 96)
	{
		note6=2
	}

	else
	{
		note6=1
	}
	scene=9;
}
	
	void debutChrono(){
		temps1=time(NULL);
	}
	void finChrono(){
		temps2=time(NULL);
	}
	
