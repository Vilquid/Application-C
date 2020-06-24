//source
//countLines : https://www.sanfoundry.com/c-program-number-lines-text-file/
//get_line de wzp : https://openclassrooms.com/forum/sujet/lire-la-seconde-ligne-dans-un-fichier-avec-fgets-67721

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 2048

void saveUsers(char chaine[], FILE *users);
char *get_line(char *buf, int n, FILE *users, int line);
int countLines(FILE *users);
void userGen(char chaine[], FILE *users);
void loginUser(char chaine[], FILE *users);

int main(){
	
	FILE *users = '\0'; //créer un pointer pour cibler un file
	
	char chaine[255]; //chaine pour récupérer l'utilisateur
	
	saveUsers(chaine, users); //fonction register
	loginUser(chaine, users); //ofnction login
	
	return 0;
}


void saveUsers(char chaine[], FILE *users){

	//-------------^^^^demande de pseudo^^^^-------------
	
	printf("qui etes-vous ?\n");
	
	if (scanf("%254s", chaine) != 1)			//gestion erreur longueur de la saisie
    {
        printf("Erreur lors de la saisie\n");
        exit(1);
    }
    
    //---------------------------------------------------
    
    
    //-------------^^^^verification de pseudo^^^^-------------
    int locker=0; // booleen
    char buf[BUF_SIZE];
    
    int i=1;
    while(i<=countLines(users)){
		get_line(buf, BUF_SIZE, users, i);       //get_line(chaine de réception, taille de la chaine, file, line);
		if((strcmp(chaine, buf)) ==0){
			locker=1;
		}
		i++;
	}
	if(locker ==1){
		printf("pseudo déjà utilisé");
		exit(1);		
	}    
	else{
		//-------------^^^^ecriture de pseudo^^^^-------------
		userGen(chaine, users);
		strcat(chaine, "\n");			

		users = fopen("./save/users", "a");

		int j = 0;
		while(chaine[j] != '\0'){
			fputc(chaine[j], users);		//sinon on enregistre le pseudo dans le fichier
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
    
    while(i<=countLines(users)){
		get_line(buf, BUF_SIZE, users, i);       //get_line(chaine de réception, taille de la chaine, file, line);
		if((strcmp(chaine, "admin")) ==0){
			printf("cette session ne vous est pas autorisée");
		}
		else if((strcmp(chaine, buf)) ==0){
			//open file
			printf("overture de la session"); //à configurer
		}
		else{
			printf("cet utilisateur n'existe pas");
		}
		i++;
	}    
	
	//---------------------------------------------------
}

char *get_line(char *buf, int n, FILE *users, int line){
	users = fopen("./save/users", "r");
	for(int i = 0; i < line; i++){
		if(fgets(buf, n, users) == NULL){
			return NULL;
		}
	}
	buf[strlen(buf) - 1] = '\0';
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
