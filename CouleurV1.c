#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()


#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <time.h> //srand()
#include <string.h>


#include "./GFX_lib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "./GFX_lib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "./GFX_lib/ESLib.h" // Pour utiliser valeurAleatoire()



#define LargeurFenetre 1280
#define HauteurFenetre 800
void cercle(float centreX, float centreY, float rayon);
void gestionEvenement(EvenementGfx evenement);




//prendre tous ce qu'il y a en dessous jusqu'a la fin de la fonction plus ce qu'il y a dans affichage.
int i=0;
int juste=0;
int iteration=0;
int erreur=0;

int fauxbuffer=0;


char rep[11]="salutation";
int millisecondesEntreAppels=5000;
void jeucouleur();
void repjeucouleur();


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
		}
	}

int main(int argc, char **argv)
{
	srand(time(NULL));
	i=(rand()%3);
	printf("%d\n",i);
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("GFX", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();

	return 0;
}



void gestionEvenement(EvenementGfx evenement)
{
	
	switch (evenement)
	{
		case Initialisation:
			rafraichisFenetre();
			demandeTemporisation(20);
			break;
		
		case Temporisation:
			rafraichisFenetre();
			break;
			
		case Affichage:
		
			// a implenter dans affichage
		
			effaceFenetre (255, 255, 255);
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
			
			//jusque la------------------------------------
			
			break;
			

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
				printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			else if (etatBoutonSouris() == GaucheRelache)
			{
				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			break;
		
		case Souris:
			break;
		
		case Inactivite: 
			break;
		}
	}

