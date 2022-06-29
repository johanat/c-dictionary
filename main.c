#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int benningAreTheSame(char *word1, char word2[]);
void printMatchingWords(char **words,char pattern[], int length, char primerWordFile[], char definicionWord[]);
void tolowerCase(char words[]);
void lineBreak(char *words, char primerWordFile[], char definicionWord[] );


/*ejercicio_1*/

int main()
{
    char **words;
    char auxWord[3000];
    int counter=0;
    int length=0;
    int counter1=0;
    char wordsX[50];
    int iguales=1;
    int totalWords = 0;
    char primerWordFile[50];
    char definicionWord[3000];


    FILE *f; // declaracion de un fichero
    f = fopen("english_dictionary.txt","r");


    if(f==NULL){
        printf("No se ha podido abrir el fichero.\n");
    }

    for(int i=0; !feof(f); i++){
        fgets(auxWord, 3000,f);
        counter++;
    }
    totalWords = counter;

    rewind(f);

    words =(char**)malloc(counter*sizeof(char*));

    for(int i=0; !feof(f); i++){
        fgets(auxWord,3000,f);
        length=strlen(auxWord);
        words[i]=(char*)malloc(length*sizeof(char));
    }

    rewind(f);

    for(int i=0; !feof(f); i++){
        fgets(auxWord,3000,f);
        strcpy(words[i],auxWord);
    }
    fclose(f);

    counter1=0;

    for(int i=0; 1==1; i++){
        printf("Introduce a word\n");
        gets(wordsX);
        system("cls");
        length=strlen(auxWord);
        //lineBreak(words[i],primerWordFile, definicionWord);
        printMatchingWords(words,wordsX, totalWords,primerWordFile, definicionWord);
    }

    return 0;
}

int benningAreTheSame(char *word1,char word2[]){

    tolowerCase(word2);

     for(int i=0; word1[i]!=0 && word2[i]!=0; i++){
        if(word1[i] == word2[i]){
            if(word2[i+1]=='\0') {
                // printf("hola1\n");
                return 0;

            }
        }
        else {
            return 1;
        }
    }

    return 1;
}

void printMatchingWords(char **words,char pattern[], int length, char primerWordFile[], char definicionWord[]){
    int counter=1;
    int iguales=1;
    int j=0;


    for(int i=0; i < length; i++){
        lineBreak(words[i],primerWordFile, definicionWord);
        iguales=benningAreTheSame(words[i],pattern);

        if(iguales ==0 ){
            counter++;
            // printf("hola2\n");
            printf("\n%d:%s\n",(j+1),primerWordFile);
            printf("%s",definicionWord);

            j++;
            if(counter > 10){
                printf("\n\n");
                break;

            }
        }
    }

    return 0;
}
void tolowerCase(char words[]){

    for(int i=0; words[i]!='\0'; i++){

        if(words[i]>=65 && words[i]<=90){
            words[i]=words[i]+32;
        }

        if(i==0){
            words[0]=words[0]-32;
        }
    }
    //printf("hola3\n");

}void lineBreak(char *words, char primerWordFile[], char definicionWord[]){


    int i=0;
    int length=0;
    int index=0;
    char separationDefinitionForLine[10][3000];

    for(i=0; words[i]!=' '; i++){
        primerWordFile[i]=words[i];
        length=strlen(words);
    }
    primerWordFile[i]='\0';

    index=i;

    for (int i=0; i<length; i++){
        definicionWord[i]=words[index];
        index++;
    }

    for (int i=0; i<10; i++){
        if(definicionWord[i]>=1 && definicionWord[i]<=10; i++){
            separationDefinitionForLine[i][i]=definicionWord[i];
        }
    }

}










