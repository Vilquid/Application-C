#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <unistd.h>


#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <time.h> //srand()
#include <string.h>


#include "./GFX_lib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "./GFX_lib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "./GFX_lib/ESLib.h" // Pour utiliser valeurAleatoire()



#define LargeurFenetre 1280
#define HauteurFenetre 800

void gestionEvenement(EvenementGfx evenement);

void repSimon();




//prendre tous ce qu'il y a en dessous jusqu'a la fin de la fonction plus ce qu'il y a dans affichage.


void simon();

void simon(){

	
	int sequences[10];
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
					couleurCourante(255,50,50);
					rectangle(140,300,340,500);
					demandeTemporisation(1000);
					break;
					
				case 2:
					couleurCourante(50,255,50);
					rectangle(390,300,590,500);
					demandeTemporisation(1000);
					break;
					
				case 3:
					couleurCourante(50,50,255);
					rectangle(640,300,840,500);
					demandeTemporisation(1000);
					break;
					
				case 4:
					couleurCourante(255,255,50);
					rectangle(890,300,1090,500);
					demandeTemporisation(1000);
					break;
					
			}
		}
	}

	scene=55;
}

void repSimon(){
	
	
	
}



int main(int argc, char **argv)
{


	
	//demandeTemporisation(5000);




	srand(time(NULL));
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
			couleurCourante(150,150,150);
			rectangle(140,300,340,500);
			rectangle(390,300,590,500);
			rectangle(640,300,840,500);
			rectangle(890,300,1090,500);
			demandeTemporisation(1000);
			//prescouleur
			
			presI++;

			if(presI ==4){
				simon();
				
			}
			
			
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
