#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int saveUsers(char chaine[], FILE *users);


int main(){
	
	FILE *users = '\0';
	
	
	char chaine[255];
	
	saveUsers(chaine, users);

	
	return 0;
}

int saveUsers(char chaine[], FILE *users){
	
	int locker = 0;

	printf("qui etes-vous ?\n");
	
	if (scanf("%254s", chaine) != 1)
    {
        printf("Erreur lors de la saisie\n");
        return EXIT_FAILURE;
    }
	
	users = fopen("./save/users", "r");
	
	char chaineBis[255];
	int i = 0;
	while((chaineBis[i] = getc(users)) != EOF){
		
		if(chaineBis[i] == '\n'){
			printf("\n\n%s", chaineBis);			
			if((strcmp(chaineBis, chaine)) == 0){
				locker=1;
				printf("\n%d", locker);
			}
			while(j != sizeof(chaineBis)){
				chaineBis[j]='\0';
				j++;
			}
			i=-1;
		}
	i++;
		
	}
	
	
	fclose(users);

	
	if(locker == 1){
		
		printf("pseudo déjà utilisé");
		return EXIT_FAILURE;
	
	
	}
	else{
		
		strcat(chaine, "\n");

		users = fopen("./save/users", "a");

		int i = 0;
		while(chaine[i] != '\0'){
		
			fputc(chaine[i], users);
			i++;
		}

		fclose(users);
		return 0;
		
	}
}
