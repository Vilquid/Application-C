#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "./GFX_lib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "./GFX_lib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "./GFX_lib/ESLib.h" // Pour utiliser valeurAleatoire()
#include <time.h> //srand()
#include <string.h>
#include <unistd.h>

#define LargeurFenetre 1280
#define HauteurFenetre 800
#define PtDonneesImageRGB DonneesImageRGB*

void gestionEvenement(EvenementGfx evenement);
// Fonction de trace de cercle
void cercle(float centreX, float centreY, float rayon);
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
// PROTOYYPES
void jeu_sept_erreurs();
int jeu_reflexe();
void regles();
//simon
/*int simon(int sequences[10], int tour);
void repSimon(int sequences[10], int tour);
int sequences[10];
int tour=0;
int locker=0;*/
//scene
int scene=0;
//who
void who();
int buffer=0;
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
static DonneesImageRGB *image = NULL; 




int main(int argc, char **argv)
{
	srand(time(NULL));
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("GFX", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	return 0;
}

void gestionEvenement(EvenementGfx evenement){
	
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	switch(evenement){
		
		case Initialisation:
			rafraichisFenetre();
			demandeTemporisation(20);
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
				ecrisImage((LargeurFenetre-image->largeurImage*2)/4,  HauteurFenetre*2/3-(image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
				ecrisImage((LargeurFenetre*3-dataRGB->largeurImage*2)/4,  HauteurFenetre*2/3-(dataRGB->hauteurImage)/2, dataRGB->largeurImage, dataRGB->hauteurImage, dataRGB->donneesRGB);
			}*/

			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier()){
				
				case 'Q': /* Pour sortir quelque peu proprement du programme */
				case 'q':
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
				onClic();
				rafraichisFenetre();
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

void who(){
	int i=1;
	
	//i = rand() % (3-1+1)+1;
	if(i==1){
		image = lisBMPRGB("./lion.bmp"); // chemins à redéterminer

		if (image != NULL) // Si l'image a pu etre lue
		{
			ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
		}
	}
	else if(i==2){
		image = lisBMPRGB("./oiseau.bmp"); // chemins à redéterminer

		if (image != NULL) // Si l'image a pu etre lue
		{
			ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
		}
	}
	else if(i==3){
		image = lisBMPRGB("./eau.bmp"); // chemins à redéterminer

		if (image != NULL) // Si l'image a pu etre lue
		{
			ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
		}
	}
	
	
	scene=230;
	
}
/*int simon(int sequences[10], int tour){

	

	int sequence=0;

	for(int i=0; i<10; i++){
		sequence = (rand() % (4 - 1 + 1)) + 1;
		sequences[i]=sequence;
		printf("\ni=%d", i);
		printf("\nsequence=%d", sequence);
		for(int j=0;j<=i;j++){
			printf("\nj=%d", j);
			printf("\nsequence[%d]=%d", j, sequences[j]);
			switch (sequences[j]){
	
				case 1:
					demandeTemporisation(1000);
					couleurCourante(255,50,50);
					rectangle(140,300,340,500);
					break;
					
				case 2:
					demandeTemporisation(1000);
					couleurCourante(50,255,50);
					rectangle(390,300,590,500);
					break;
					
				case 3:
					demandeTemporisation(1000);
					couleurCourante(50,50,255);
					rectangle(640,300,840,500);
					break;
					
				case 4:
					demandeTemporisation(1000);
					couleurCourante(255,255,50);
					rectangle(890,300,1090,500);
					break;
					
			}
			scene=55;
		}
			
	}
	tour=i;

	return tour;
}

void repSimon(int sequences[10], int tour){
	
	locker=1;
	int repSequences[10];
	
	for(int i=0; i<=tour;i++){
		
	

		if(140 <= abscisseSouris() && abscisseSouris() <= 340 && 300 <= ordonneeSouris() && ordonneeSouris() <= 500 && etatBoutonSouris() == GaucheAppuye){
			
			repSequences[i]=1;
			
		}
		else if(390 <= abscisseSouris() && abscisseSouris() <= 590 && 300 <= ordonneeSouris() && ordonneeSouris() <= 500 && etatBoutonSouris() == GaucheAppuye){
			
			repSequences[i]=2;
		}
		else if(640 <= abscisseSouris() && abscisseSouris() <= 840 && 300 <= ordonneeSouris() && ordonneeSouris() <= 500 && etatBoutonSouris() == GaucheAppuye){
			
			repSequences[i]=3;
		}
		else if(890 <= abscisseSouris() && abscisseSouris() <= 1090 && 300 <= ordonneeSouris() && ordonneeSouris() <= 500 && etatBoutonSouris() == GaucheAppuye){
			
			repSequences[i]=4;
		}
		if(repSequences[i]!= sequences[i]){
			
			couleurCourante(255,50,50);
			afficheChaine("FAUX", 200, LargeurFenetre/4, HauteurFenetre/2);
			demandeTemporisation(1000);
			
		
		}
		else{
			locker=0;
		}
	}
	
	
	scene=13;
}*/

int onClic(){
	//selection de langue
	if (scene==0){
		if (abscisseSouris() >= LargeurFenetre*2/20 && abscisseSouris() <= LargeurFenetre*8/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=1;
			return 0;
		}
		else if (abscisseSouris() >= LargeurFenetre*12/20 && abscisseSouris() <= LargeurFenetre*18/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=2;
			return 0;
		}
	}
	//bouton retour/quitter
	if (abscisseSouris() >= LargeurFenetre*17/20 && abscisseSouris() <= LargeurFenetre && ordonneeSouris() >= 0 && ordonneeSouris() <= HauteurFenetre*2/20){
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
		if (abscisseSouris() >= LargeurFenetre*2/20 && abscisseSouris() <= LargeurFenetre*6/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=5;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*8/20 && abscisseSouris() <= LargeurFenetre*12/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=7;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*14/20 && abscisseSouris() <= LargeurFenetre*18/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=9;
			return 0;
		}
	}
	if (scene==4){
		if (abscisseSouris() >= LargeurFenetre*2/20 && abscisseSouris() <= LargeurFenetre*6/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=6;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*8/20 && abscisseSouris() <= LargeurFenetre*12/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=8;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*14/20 && abscisseSouris() <= LargeurFenetre*18/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=10;
			return 0;
		}
	}
	if (scene==5){
		if (abscisseSouris() >= LargeurFenetre*2/20 && abscisseSouris() <= LargeurFenetre*6/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=11;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*8/20 && abscisseSouris() <= LargeurFenetre*12/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=13;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*14/20 && abscisseSouris() <= LargeurFenetre*18/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=15;
			return 0;
		}
	}
	if (scene==6){
		if (abscisseSouris() >= LargeurFenetre*2/20 && abscisseSouris() <= LargeurFenetre*6/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=12;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*8/20 && abscisseSouris() <= LargeurFenetre*12/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=14;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*14/20 && abscisseSouris() <= LargeurFenetre*18/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=16;
			return 0;
		}
	}
	if (scene==7){
		if (abscisseSouris() >= LargeurFenetre*2/20 && abscisseSouris() <= LargeurFenetre*6/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=17;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*8/20 && abscisseSouris() <= LargeurFenetre*12/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=19;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*14/20 && abscisseSouris() <= LargeurFenetre*18/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=15;
			return 0;
		}
	}
	if (scene==8){
		if (abscisseSouris() >= LargeurFenetre*2/20 && abscisseSouris() <= LargeurFenetre*6/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=18;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*8/20 && abscisseSouris() <= LargeurFenetre*12/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=20;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*14/20 && abscisseSouris() <= LargeurFenetre*18/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=16;
			return 0;
		}
	}
	if (scene==9){
		if (abscisseSouris() >= LargeurFenetre*2/20 && abscisseSouris() <= LargeurFenetre*6/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=23;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*8/20 && abscisseSouris() <= LargeurFenetre*12/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=25;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*14/20 && abscisseSouris() <= LargeurFenetre*18/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=15;
			return 0;
		}
	}
	if (scene==10){
		if (abscisseSouris() >= LargeurFenetre*2/20 && abscisseSouris() <= LargeurFenetre*6/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=24;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*8/20 && abscisseSouris() <= LargeurFenetre*12/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=26;
			return 0;
		}
		if (abscisseSouris() >= LargeurFenetre*14/20 && abscisseSouris() <= LargeurFenetre*18/20 && ordonneeSouris() >= HauteurFenetre*2/6 && ordonneeSouris() <= HauteurFenetre*3/6){
			scene=16;
			return 0;
		}
	}
	if (abscisseSouris() >= 0 && abscisseSouris() <= LargeurFenetre*3/20 && ordonneeSouris() >= 0 && ordonneeSouris() <= HauteurFenetre*2/20){
		if (scene==5 || scene==7 || scene==9){
			scene=29;
			return 0;
		}
		else if (scene==6 || scene==8 || scene==10){
			scene=30;
			return 0;
		}
	
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

/* Fonction de trace de cercle */
void cercle(float centreX, float centreY, float rayon)
{
	const int Pas = 20; // Nombre de secteurs pour tracer le cercle
	const double PasAngulaire = 2.*M_PI/Pas;
	int index;
	
	for (index = 0; index < Pas; ++index) // Pour chaque secteur
	{
		const double angle = 2.*M_PI*index/Pas; // on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
				 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
				 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
			// On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
	
}

void affichage(){
	//bouton retour/quitter
	couleurCourante(200,200,200);
	rectangle(LargeurFenetre*17/20, 0, LargeurFenetre, HauteurFenetre*2/20);
	
	if (scene!=0){
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Retour", 30, LargeurFenetre*18/20, HauteurFenetre/25);
	}
	//-------------------------------------------------------------------------------------selections-------------------------------------------------------------------------------------//
	if (scene==0){//selection de langue
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*2/6, LargeurFenetre*8/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*12/20, HauteurFenetre*2/6, LargeurFenetre*18/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Selectionnez votre langue", 30, LargeurFenetre/3, HauteurFenetre*3/4-16);
		afficheChaine("Select your language", 30, LargeurFenetre/3, HauteurFenetre*3/4+16);
		afficheChaine("Francais", 30, LargeurFenetre*4/20, HauteurFenetre*5/12);
		afficheChaine("Anglais", 30, LargeurFenetre*14/20, HauteurFenetre*5/12);
		afficheChaine("Quitter", 30, LargeurFenetre*18/20, HauteurFenetre/25);
		
	}
	if (scene==110){//login
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*2/6, LargeurFenetre*8/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*12/20, HauteurFenetre*2/6, LargeurFenetre*18/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Voulez vous vous inscrire ou vous connecter?", 30, LargeurFenetre/3, HauteurFenetre*3/4-16);
		afficheChaine("Inscription", 30, LargeurFenetre*4/20, HauteurFenetre*5/12);
		afficheChaine("connection", 30, LargeurFenetre*14/20, HauteurFenetre*5/12);
		afficheChaine("Quitter", 30, LargeurFenetre*18/20, HauteurFenetre/25);
	}
	if (scene==1){//entrée prénom fr
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Entrez votre nom", 30, LargeurFenetre/3, HauteurFenetre*3/4);
	}
	if (scene==2){//entrée prénom en
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Enter your name", 30, LargeurFenetre/3, HauteurFenetre*3/4);
	}
	if (scene==3){//choix apptitude fr
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*2/6, LargeurFenetre*6/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*8/20, HauteurFenetre*2/6, LargeurFenetre*12/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*14/20, HauteurFenetre*2/6, LargeurFenetre*18/20, HauteurFenetre*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Selectionnez l'aptitude a evaluer", 30, LargeurFenetre/3, HauteurFenetre*3/4);
		afficheChaine("Memoire", 30, LargeurFenetre*3/20, HauteurFenetre*5/12);
		afficheChaine("Synchronisation", 30, LargeurFenetre*17/40-20, HauteurFenetre*5/12);
		afficheChaine("Vitesse d'analyse", 30, LargeurFenetre*14/20, HauteurFenetre*5/12);
	}
	if (scene==4){//choix apptitude en
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*2/6, LargeurFenetre*6/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*8/20, HauteurFenetre*2/6, LargeurFenetre*12/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*14/20, HauteurFenetre*2/6, LargeurFenetre*18/20, HauteurFenetre*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Select the ability to assess", 30, LargeurFenetre/3, HauteurFenetre*3/4);
		afficheChaine("Memory", 30, LargeurFenetre*3/20, HauteurFenetre*5/12);
		afficheChaine("Synchronization", 30, LargeurFenetre*17/40, HauteurFenetre*5/12);
		afficheChaine("Analysis speed", 30, LargeurFenetre*14/20, HauteurFenetre*5/12);
	}
	
	//-------------------------------------------------------------------------------------Menu par catégorie-------------------------------------------------------------------------------------//
	if (scene==5){//mémoire fr
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*2/6, LargeurFenetre*6/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*8/20, HauteurFenetre*2/6, LargeurFenetre*12/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*14/20, HauteurFenetre*2/6, LargeurFenetre*18/20, HauteurFenetre*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Selectionnez un test", 30, LargeurFenetre/3, HauteurFenetre*3/4);
		afficheChaine("Memory", 30, LargeurFenetre*3/20, HauteurFenetre*5/12);
		afficheChaine("Simon", 30, LargeurFenetre*17/40, HauteurFenetre*5/12);
		afficheChaine("Resultats", 30, LargeurFenetre*14/20, HauteurFenetre*5/12);
	}
	if (scene==6){//mémoire en
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*2/6, LargeurFenetre*6/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*8/20, HauteurFenetre*2/6, LargeurFenetre*12/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*14/20, HauteurFenetre*2/6, LargeurFenetre*18/20, HauteurFenetre*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Select a test", 30, LargeurFenetre/3, HauteurFenetre*3/4);
		afficheChaine("concentration", 30, LargeurFenetre*3/20, HauteurFenetre*5/12);
		afficheChaine("Simon", 30, LargeurFenetre*17/40, HauteurFenetre*5/12);
		afficheChaine("Results", 30, LargeurFenetre*14/20, HauteurFenetre*5/12);
	}
	if (scene==7){//synchro fr
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*2/6, LargeurFenetre*6/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*8/20, HauteurFenetre*2/6, LargeurFenetre*12/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*14/20, HauteurFenetre*2/6, LargeurFenetre*18/20, HauteurFenetre*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Selectionnez un test", 30, LargeurFenetre/3, HauteurFenetre*3/4);
		afficheChaine("jeu1", 30, LargeurFenetre*3/20, HauteurFenetre*5/12);
		afficheChaine("jeu2", 30, LargeurFenetre*17/40, HauteurFenetre*5/12);
		afficheChaine("Resultats", 30, LargeurFenetre*14/20, HauteurFenetre*5/12);
	}
	if (scene==8){//synchro en
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*2/6, LargeurFenetre*6/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*8/20, HauteurFenetre*2/6, LargeurFenetre*12/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*14/20, HauteurFenetre*2/6, LargeurFenetre*18/20, HauteurFenetre*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Select a test", 30, LargeurFenetre/3, HauteurFenetre*3/4);
		afficheChaine("game1", 30, LargeurFenetre*3/20, HauteurFenetre*5/12);
		afficheChaine("game2", 30, LargeurFenetre*17/40, HauteurFenetre*5/12);
		afficheChaine("Results", 30, LargeurFenetre*14/20, HauteurFenetre*5/12);
	}
	if (scene==9){//vitesse analyse fr
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*2/6, LargeurFenetre*6/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*8/20, HauteurFenetre*2/6, LargeurFenetre*12/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*14/20, HauteurFenetre*2/6, LargeurFenetre*18/20, HauteurFenetre*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Selectionnez un test", 30, LargeurFenetre/3, HauteurFenetre*3/4);
		afficheChaine("jeu1", 30, LargeurFenetre*3/20, HauteurFenetre*5/12);
		afficheChaine("jeu2", 30, LargeurFenetre*17/40, HauteurFenetre*5/12);
		afficheChaine("Resultats", 30, LargeurFenetre*14/20, HauteurFenetre*5/12);
	}
	if (scene==10){//vitesse analyse en
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*2/6, LargeurFenetre*6/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*8/20, HauteurFenetre*2/6, LargeurFenetre*12/20, HauteurFenetre*3/6);
		rectangle(LargeurFenetre*14/20, HauteurFenetre*2/6, LargeurFenetre*18/20, HauteurFenetre*3/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Select a test", 30, LargeurFenetre/3, HauteurFenetre*3/4);
		afficheChaine("game1", 30, LargeurFenetre*3/20, HauteurFenetre*5/12);
		afficheChaine("game2", 30, LargeurFenetre*17/40, HauteurFenetre*5/12);
		afficheChaine("Results", 30, LargeurFenetre*14/20, HauteurFenetre*5/12);
	}
	//-------------------------------------------------------------------------------------resultats---------------------------------------------------------------------------------------//
	if (scene==15){//résultats fr
		couleurCourante(200,200,200);
		rectangle(LargeurFenetre*2/20, HauteurFenetre*4/6, LargeurFenetre*18/20, HauteurFenetre*5/6);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Resultats", 30, LargeurFenetre/3, HauteurFenetre*3/4);
	}
	//----------------------------------------------------------------------------------------règles---------------------------------------------------------------------------------------//
	
	if (scene==5||scene==7||scene==9){
		couleurCourante(200,200,200);
		rectangle(0, 0, LargeurFenetre*3/20, HauteurFenetre*2/20);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Regles", 30, LargeurFenetre*2/20, HauteurFenetre/25);
	}
	if (scene==6||scene==8||scene==10){
		couleurCourante(200,200,200);
		rectangle(0, 0, LargeurFenetre*3/20, HauteurFenetre*2/20);
		couleurCourante(0,0,0);
		epaisseurDeTrait(4);
		afficheChaine("Rules", 30, LargeurFenetre*2/20, HauteurFenetre/25);
	}
	if (scene==29){
	}
	if (scene==30){
	}
	
	//-------------------------------------------------------------------------------------scènes jeux-------------------------------------------------------------------------------------//
	if (scene==23){
			//jeucouleur();// fonctionne parce que j'ai mit un buffer !!!! donc un qui part dans le vide
			who();
			scene=230; 
		}
	if (scene==230){
		//jeu de couleur
			
			/*effaceFenetre(255,255,255);

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
			}*/
			char rep[255];
			if(buffer==0){
				buffer=1;
				scene=23;
			}
			else{
				printf("qu'avez-vous vu ?");
				scanf("%s", rep);
				if(i==1){
					if((strcmp(rep, "lion"))==0){
						printf("bravo");
					}
				}
				else if(i==2){
					if((strcmp(rep, "oiseau"))==0){
						printf("bravo");
					}
				}
				else if(i==3){
					if((strcmp(rep, "eau"))==0){
						printf("bravo");
					}
				}
				scene=23;
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
	
	/*if(scene==13){
		if(buffer==0){
			buffer=1;
		}
		else{
			printf("qu'avez-vous vu ?");
			scanf("%s", rep);
			if(i==1){
				if((strcmp(rep, "lion"))==0){
					printf("bravo");
				}
			}
			else if(i==2){
				if((strcmp(rep, "oiseau"))==0){
					printf("bravo");
				}
			}
			else if(i==3){
				if((strcmp(rep, "eau"))==0){
					printf("bravo");
				}
			}
		}
		scene=55;
	}
	if(scene==55){
		who();
		
	}
	/*if(scene==13){
		couleurCourante(150,150,150);
		rectangle(140,300,340,500);
		rectangle(390,300,590,500);
		rectangle(640,300,840,500);
		rectangle(890,300,1090,500);
		if(locker==0){	
			simon(sequences, tour);
		}
	}
	if(scene==55){
		repSimon(sequences, tour);
		
	}*/
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
	int abscisses_des_erreurs2[7]; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
	int ordonnees_des_erreurs2[7];

	if (nombre_alea <= 25) // image 1
	{
		int abscisses_des_erreurs[7] = {527,565,661,673,707,697,868}; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
		int ordonnees_des_erreurs[7] = {119,264,463,320,225,157,137};
		memcpy(abscisses_des_erreurs2,abscisses_des_erreurs, sizeof(abscisses_des_erreurs));
		memcpy(ordonnees_des_erreurs2,ordonnees_des_erreurs, sizeof(ordonnees_des_erreurs));
		image = lisBMPRGB("./image/erreurs_1.bmp"); // chemins à redéterminer

		if (image != NULL) // Si l'image a pu etre lue
		{
			ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
		}
	}

	else if (25 < nombre_alea  && nombre_alea <= 50) // image 2
	{
		int abscisses_des_erreurs[7] = {803,1021,1118,1160,884,917,1207}; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
		int ordonnees_des_erreurs[7] = {566,625,459,354,240,138,226};
		memcpy(abscisses_des_erreurs2,abscisses_des_erreurs, sizeof(abscisses_des_erreurs));
		memcpy(ordonnees_des_erreurs2,ordonnees_des_erreurs, sizeof(ordonnees_des_erreurs));
		image = lisBMPRGB("./image/erreurs_2.bmp"); // chemins à redéterminer
		
		if (image != NULL) // Si l'image a pu etre lue
		{
			ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
		}
	}

	else if (50 < nombre_alea &&  nombre_alea<= 75) // image 3
	{
		int abscisses_des_erreurs[7] = {272,31,140,335,429,538,520}; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
		int ordonnees_des_erreurs[7] = {354,204,128,307,301,234,79};
		memcpy(abscisses_des_erreurs2,abscisses_des_erreurs, sizeof(abscisses_des_erreurs));
		memcpy(ordonnees_des_erreurs2,ordonnees_des_erreurs, sizeof(ordonnees_des_erreurs));
		image = lisBMPRGB("./image/erreurs_3.bmp"); // chemins à redéterminer
		
		if (image != NULL) // Si l'image a pu etre lue
		{
			ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
		}
	}

	else // image 4
	{
		int abscisses_des_erreurs[7] = {58,193,248,266,334,433,444}; // x puis y IL FAUT D2TERMINER LES COORDONNEES DES ERREURS
		int ordonnees_des_erreurs[7] = {25,179,96,201,266,225,278};
		memcpy(abscisses_des_erreurs2,abscisses_des_erreurs, sizeof(abscisses_des_erreurs));
		memcpy(ordonnees_des_erreurs2,ordonnees_des_erreurs, sizeof(ordonnees_des_erreurs));
		image = lisBMPRGB("./image/erreurs_4.bmp"); // chemins à redéterminer
		
		if (image != NULL) // Si l'image a pu etre lue
		{
			ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
		}
	}
	
	int erreurs = 0;
	int clic = 0;
	int timer; // timer = la valeur à laquelle le timer s'est arreté

	//début du timer
	debutChrono();

	while (erreurs != 7 || clic > 10)
	{
		for (int i = 0; i < 7; i++)
		{
			if ((abscisses_des_erreurs2[i] - 10) <= abscisseSouris() && abscisseSouris()<= (abscisses_des_erreurs2[i] + 10) && (ordonnees_des_erreurs2[i] - 10) <= ordonneeSouris() && ordonneeSouris()<= (ordonnees_des_erreurs2[i] - 10) && etatBoutonSouris() == GaucheAppuye) // si clic correspond a l'erreur
			{
				erreurs++;
				clic++;
				couleurCourante(255, 0, 0);
				epaisseurDeTrait(2);
				cercle(abscisses_des_erreurs2[i], ordonnees_des_erreurs2[i], 5);
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

	timer=temps2-temps1; // timer = la valeur à laquelle le timer s'est arreté

	if (timer < 24)
	{
		note6=5;
	}

	else if (24 <= timer &&  timer< 48)
	{
		note6=4;
	}

	else if (48 <= timer &&  timer< 72)
	{
		note6=3;
	}

	else if (72 <= timer &&  timer< 96)
	{
		note6=2;
	}

	else
	{
		note6=1;
	}
	scene=9;

}
	
void debutChrono(){
	temps1=time(NULL);
}
void finChrono(){
	temps2=time(NULL);
}

void regles()
{
	couleurCourante(200, 200, 200);
	rectangle(0, 0, 30, 10);

	couleurCourante(0, 0, 0);
	afficheChaine("Règles", 5, 0, 2);

	if (0 <= abscisseSouris() && abscisseSouris() <= 30 && 0 <= ordonneeSouris() && ordonneeSouris() <= 10 && etatBoutonSouris() == GaucheAppuye)
	{
		effaceFenetre (230, 230, 230);

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


int jeu_reflexe() // jeu où l'on doit cliquer le plus rapidement dans une case
{
	int x_alea = rand() % ((LargeurFenetre-20)-20+1)+20;
	int y_alea = rand() % ((HauteurFenetre-100)-100+1)+100;
	int temps_alea = rand() % 20;
	int note = 0;
	

	sleep(temps_alea);

	// affiche aléatoire du carré
	couleurCourante(255, 51, 0);
	rectangle(x_alea, y_alea, x_alea + 20, y_alea + 20);

	// début du timer
	debutChrono();

	while (x_alea <= abscisseSouris() && abscisseSouris() <= x_alea + 20 && y_alea <= ordonneeSouris() && ordonneeSouris() <= y_alea + 20 && etatBoutonSouris() == GaucheAppuye)
	// tant qu'il n'y a pas de clic et que les coordonnées de la souris n'appartiennet pas au carré, ne rien faire
	{
		sleep(0.01);
	}

	// double timer = temps du timer;
	
	// fin timer
	finChrono();
	int timer=temps2-temps1;
	
	
	if (timer < 0.2)
	{
		note = 5;
	}

	if (0.2 <= timer && timer< 0.4)
	{
		note = 4;
	}

	if (0.4 <= timer && timer< 0.6)
	{
		note = 3;
	}

	if (0.8 <= timer && timer< 1.0)
	{
		note = 2;
	}

	else
	{
		note = 1;
	}

	return note;
}

