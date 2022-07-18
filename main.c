#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_DEF 100

int benningAreTheSame(char *word1, char word2[]);
void printMatchingWords(char **wordOfFile,char pattern[], int length);
void toLowerCase(char wordOfFile[]);
void lineBreak(char *wordOfFile, char firstWordOfTheRow[], char definitionOfWord[], char** matrix);

// proyecto_dicionary.

int main()
{
    char **wordOfFile;
    char wordRead[3000];
    int counter=0;
    int length=0;
    int counter1=0;
    char wordUser[50]; // palabra del usuario
    int same=1; // iguales
    int totalWords = 0;

    FILE *f; // declaracion de un fichero
    f = fopen("english_dictionary.txt","r");


    if(f==NULL){
        printf("No se ha podido abrir el fichero.\n");
    }

    for(int i=0; !feof(f); i++){
        fgets(wordRead, 3000,f);
        counter++;
    }

    totalWords = counter;

    rewind(f);

    wordOfFile =(char**)malloc(counter*sizeof(char*));

    for(int i=0; !feof(f); i++){
        fgets(wordRead,3000,f);
        length=strlen(wordRead);
        wordOfFile[i]=(char*)malloc(length*sizeof(char));
    }

    rewind(f);

    for(int i=0; !feof(f); i++){
        fgets(wordRead,3000,f);
        strcpy(wordOfFile[i],wordRead);
    }

    fclose(f);

    counter1=0;

    for(int i=0; 1==1; i++){
        printf("Introduce a word\n");
        gets(wordUser);
        system("cls");
        printMatchingWords(wordOfFile,wordUser, totalWords);
    }

    return 0;
}

int benningAreTheSame(char *word1,char word2[]){

     toLowerCase(word2);

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

void printMatchingWords(char **wordOfFile,char pattern[], int length){

    char firstWordOfTheRow[50];
    char definitionOfWord[3000];
    int counter=0;
    int same=1;
    char** definitionsMatrix;
    int i=0; // recorre filas
    int j=0; // recorre columnas

    definitionsMatrix =(char**)malloc(MAX_DEF*sizeof(char*));
    if(definitionsMatrix==NULL){
        printf("No se ha podido reservar espacio en la memoria\n");
    }

    for(int i=0; i<MAX_DEF; i++){
        definitionsMatrix[i]=(char*)malloc(3000*sizeof(char));
    }

    j=0;

    for(int i=0; i < length; i++){
        same=benningAreTheSame(wordOfFile[i],pattern);

        if(same == 0){
            lineBreak(wordOfFile[i],firstWordOfTheRow, definitionOfWord, definitionsMatrix);
        }

        if(same == 0 ){
            counter++;
            printf("<<<< %s >>>>  \n",firstWordOfTheRow);
            j++;

            for(int m=0; m < MAX_DEF; m++){
                if(strcmp(definitionsMatrix[m], "johana.") == 0){
                    break;
                }

                printf("%s\n", definitionsMatrix[m]);

                if(counter==10){
                    printf("\n\n");
                    return;

                }
            }
        }

    }

    //Liberar memoria
    for(int i=0; i<10; i++) {
        free(definitionsMatrix[i]);
    }
    free(definitionsMatrix);

    return 0;
}

void toLowerCase(char wordOfFile[]){

    for(int i=0; wordOfFile[i]!='\0'; i++){
        if(wordOfFile[i]>=65 && wordOfFile[i]<=90){
            wordOfFile[i]=wordOfFile[i]+32;
        }

        if(i==0){
            wordOfFile[0]=wordOfFile[0]-32;
        }
    }
}

void lineBreak(char *wordOfFile, char firstWordOfTheRow[], char definitionOfWord[], char** matrix){

    int i=0;
    int length=0;
    int index=0;
    int j=0;
    int counter =0;
    char *p;
    char space[5]="    ";

    for(i=0; wordOfFile[i]!=' '; i++){
        firstWordOfTheRow[i]=wordOfFile[i];
    }

    firstWordOfTheRow[i]='\0';
    index=i;

    for(int l=0; wordOfFile[l]!='\0'; l++){
        definitionOfWord[l]=wordOfFile[index];
        index++;
    }

    length=strlen(definitionOfWord);

    int k=0;

    i=0;


    for(j=0;  j<length; j++){
        if(definitionOfWord[j]=='#'){
            k=0;
            matrix[i][k]='\0';
            i++;
            matrix[i][k]='-';
            k++;
            j++;
            matrix[i][k]='\0';
            for(int z=0; definitionOfWord[j]!='.'; z++){
                matrix[i][k]=definitionOfWord[j];
                k++;
                j++;
                if(definitionOfWord[j]=='.'&&definitionOfWord[j+1]==' '){
                    matrix[i][k]=definitionOfWord[j];
                    k++;
                    matrix[i][k]='\0';
                    j++;
                    j++;
                    k=0;
                    if(definitionOfWord[j]==49){
                        break;
                    }
                }
            }
        }
        if(definitionOfWord[j]>=49 && definitionOfWord[j]<58){
            i++;
            k=0;
            for(int r=0; r<4; r++){
                matrix[i][k]=space[r];
                k++;
            }
                matrix[i][k]=definitionOfWord[j];
        }
        if(definitionOfWord[j]==' '&& definitionOfWord[j+1]=='#'){
            k=0;
            matrix[i][k]='-';
            k++;
            matrix[i][k]=definitionOfWord[j];
        }
        matrix[i][k]=definitionOfWord[j];
        k++;
        if(definitionOfWord[j]=='\n'){
            matrix[i][k]='\0';
            i++;
            strcpy(matrix[i], "johana.");
            break;
        }
    }
}
