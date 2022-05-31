#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int benningAreTheSame(char *word1, char word2[]);
void printMatchingWords(char **words,char pattern[], int length);
void tolowerCase(char words[]);
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
        printMatchingWords(words,wordsX, totalWords);
    }

    return 0;
}

int benningAreTheSame(char *word1,char word2[]){


    tolowerCase(word2);

     for(int i=0; word1[i]!=0 && word2[i]!=0; i++){
        if(word1[i] == word2[i]){
            if(word2[i+1]=='\0') {
                return 0;
            }
        }
        else {
            return 1;
        }
    }

    return 1;
}

void printMatchingWords(char **words,char pattern[], int length)
{
    int counter=1;
    int iguales=1;
    int j=0;

    for(int i=0; i < length; i++){
        iguales=benningAreTheSame(words[i],pattern);
        if(iguales ==0 ){
            counter++;
            printf("\n%d   :%s",(j+1),words[i]);
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

}
