#include "DataProcess.h"

int main(){
	
	FILE *users = '\0'; //créer un pointer pour cibler un file
	
	char chaine[255]; //chaine pour récupérer l'utilisateur

	saveUsers(chaine, users); //fonction register
	//loginUser(chaine, users); //fonction login
	//saveHist(chaine, nameTest, score, users); //fonction historic
	
	return 0;
}
