//source
//countLines : https://www.sanfoundry.com/c-program-number-lines-text-file/
//get_line de wzp : https://openclassrooms.com/forum/sujet/lire-la-seconde-ligne-dans-un-fichier-avec-fgets-67721
//Made by Quentin Hamonic
//V1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 2048

//enregistre un user dans la liste users.txt                            |   saveUsers(user_name, file);
void saveUsers(char chaine[], FILE *users);  
//permet d'obtenir le contenu d'une ligne demandée                      |   getLine(buffer_content_line, buffer size, file, line);
char *getLine(char *buf, int n, FILE *users, int line);  
//obtient le nombre le ligne d'un fichier                               |   countLines(file);
int countLines(FILE *users);
//créer un fichier au nom du user pour y mettre des scores              |   userGen(user_name, file);
void userGen(char chaine[], FILE *users);
//lie un user à son file user puis lance un session                     |   loginUser(user_name, file);
void loginUser(char chaine[], FILE *users);
//sauvegarde des scores dans le file user                               |   saveHist(user_name, test_name, score, file);
void saveHist(char chaine[], char nameTest[], int score, FILE *users);

int main(){
	
	FILE *users = '\0'; //créer un pointer pour cibler un file
	
	char chaine[255]; //chaine pour récupérer l'utilisateur

	//saveUsers(chaine, users); //fonction register
	//loginUser(chaine, users); //fonction login
	//saveHist(chaine, nameTest, score, users); //fonction historic
	
	return 0;
}

void saveUsers(char chaine[], FILE *users){

	//-------------^^^^demande de pseudo^^^^-------------
	
	printf("qui etes-vous ?\n");
	
	if (scanf("%254s", chaine) != 1)			//gestion erreur longueur de la saisie
    {
        printf("Erreur lors de la saisie ou pseudo trop long\n");
        exit(1);
    }
    
    //---------------------------------------------------
    
    
    //-------------^^^^verification de pseudo^^^^-------------
    int locker=0; // booleen
    char buf[BUF_SIZE]; //buffer du contenu d'une ligne lors de lecture
    
    int i=1;
    while(i<=countLines(users)){
		getLine(buf, BUF_SIZE, users, i);       
		if((strcmp(chaine, buf)) ==0){		//compare si le user demandé est présent ou non
			locker=1;						//si oui alors on verrouille la creation de user, booleen
		}
		i++;
	}
	if(locker ==1){
		printf("pseudo déjà utilisé");
		exit(1);		
	}    
	else{
		//-------------^^^^ecriture de pseudo^^^^-------------
		userGen(chaine, users);				//creation du fichier d'un user
		strcat(chaine, "\n");			

		users = fopen("./save/users", "a");

		int j = 0;
		while(chaine[j] != '\0'){
			fputc(chaine[j], users);		//on enregistre le pseudo dans le fichier
			j++;
		}
		

		fclose(users);
		//---------------------------------------------------
			
	}
	//---------------------------------------------------
	
}

void loginUser(char chaine[], FILE *users){
	
	//-------------^^^^demande de pseudo^^^^-------------
	
	printf("qui etes-vous ?\n");
	
	if (scanf("%254s", chaine) != 1)			//gestion erreur longueur de la saisie
    {
        printf("Erreur lors de la saisie\n");
        exit(1);
    }
    
    //---------------------------------------------------
	
	//-------------^^^^verification de pseudo^^^^-------------
    
    char buf[BUF_SIZE];
    
    int i=1;
    int result=0;
    
    while(i<=countLines(users)){
		getLine(buf, BUF_SIZE, users, i);       
		if((strcmp(chaine, "admin")) ==0){
			result=1;                             //login admin pas autorisé
		}
		else if((strcmp(chaine, buf)) ==0){
			result=2;							  //login existant, ouverture de la session
		}
		else{
			result=3;                             //login inexistant
		}
		i++;
	}
	switch (result){
		
		case 0:
			printf("error");
			break;
		case 1:
			printf("cette session ne vous est pas autorisée");
			break;
		case 2:
			//ici on est dans la session donc il faut lancer les menus etc... 
			printf("overture de la session"); //à configurer
			break;
		case 3:
			printf("cet utilisateur n'existe pas");
			break;
		
	
	}
	
	//---------------------------------------------------

}

void saveHist(char chaine[], char nameTest[], int score, FILE *users){
	
	char fileName[255] = "./save/";
	strcat(fileName, chaine);	//creation du chemin de sauvegarde
	users = fopen(fileName, "a");
	fprintf(users, "[%s]Votre score est de : %d/5\n", nameTest,score);  //print du score en fonction du test
	printf("sauvegarde des scores effectuée");

	fclose(users);
	
}

char *getLine(char *buf, int n, FILE *users, int line){
	users = fopen("./save/users", "rt");
	for(int i = 0; i < line; i++){
		if(fgets(buf, n, users) == NULL){  //gets dans buffer de taille n dans users
			return NULL;
		}
	}
	buf[strlen(buf) - 1] = '\0';   //mise du caractere NULL
	fclose(users);

	return buf;
}

int countLines(FILE *users){
	
	int lines=0;
	users = fopen("./save/users", "rt");
	char chr = getc(users);
    while (chr != EOF){
		
        //Count whenever new line is encountered
        if (chr == '\n')
        {
            lines = lines + 1;
        }
        //take next character from file.
        chr = getc(users);
    }
	fclose(users);
	return lines;
}

void userGen(char chaine[], FILE *users){
	
	char filename[255];

    sprintf(filename, "./save/%s", chaine);
    users = fopen(filename,"w");
	fclose(users);
	
}
