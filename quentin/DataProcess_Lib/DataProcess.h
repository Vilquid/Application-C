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
