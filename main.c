#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_DEF 100
#define MAX_RESULT 5

typedef struct{
    char type[20];
    char value[1000];
}definitionType;

typedef struct{
    char name[50];
    definitionType definitions[200];
}wordType;

int beginningsAreTheSame(char *word1, char word2[]);
void printMatchingWords(char **wordsOfDictionary,char pattern[], int length, wordType result[]);
void toLowerCase(char wordsOfDictionary[]);
void lineBreak(char *wordsOfDictionary, char firstWordOfTheRow[], char definitionOfWord[], char** matrix);
void fillWordsStructure(char *wordsOfDictionary, char searchedWord[], wordType result[]);
void stepWordDynamically( char **wordsOfDictionary,char wordUser[], int lengthWordDiccionary, wordType result[]);


//Proyecto_dicionary.

int main()
{
    char **wordsOfDictionary;
    char wordRead[3000];
    int counter=0;
    int length=0;
    int counter1=0;
    char wordUser[50]; // palabra del usuario
    int same=1; // iguales
    int totalWords = 0;
    wordType result[10];



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

    wordsOfDictionary =(char**)malloc(counter*sizeof(char*));

    for(int i=0; !feof(f); i++){
        fgets(wordRead,3000,f);
        length=strlen(wordRead);
        wordsOfDictionary[i]=(char*)malloc(length*sizeof(char));
    }

    rewind(f);

    for(int i=0; !feof(f); i++){
        fgets(wordRead,3000,f);
        strcpy(wordsOfDictionary[i],wordRead);
    }

    fclose(f);

    counter1=0;

    for(int i=0; 1==1; i++){
        printf("Introduce a word\n");
        gets(wordUser);
        system("cls");
        printMatchingWords(wordsOfDictionary,wordUser, totalWords, result);
        //stepWordDynamically(wordsOfDictionary,wordUser,totalWords, result);
    }

    /*** Funciones recomendadas por Darwin ***/
    //1. Crear una función que me rellene el array de palabras (array de estructura 'word'). La función debería recibir
    //como parámetros el array de WORDS, el diccionario (el array bidimensional con todo el diccionario), y la palabra que se está buscando.
    //2. Una vez que el array de WORDS esté relleno, crear una función que imprima ese array de WORDS.

    return 0;
}

void stepWordDynamically(char **wordOfDictionary, char wordUser[], int lengthWordDiccionary,wordType result[]){


    int same =1;


    for(int i = 0; i < lengthWordDiccionary; i++){
        same=beginningsAreTheSame(wordOfDictionary[i],wordUser);
        if(same == 0){
            fillWordsStructure(wordOfDictionary[i], wordUser,result);
            if( i>=MAX_RESULT){
                break;
            }
        }
    }
}

void fillWordsStructure(char *wordsOfDictionary, char searchedWord[], wordType result[]){

   printf("wordsOfDictionary = %s\n\n", wordsOfDictionary);
   char rawResults[MAX_RESULT][3000];
   int wordLength=0;
   int i=0;





   wordLength=strlen(wordsOfDictionary);


    for(i=0; i<MAX_RESULT; i++){
        for(int j=0; j<wordLength; j++){
            rawResults[i][j]=wordsOfDictionary[j];
            if(wordLength==j){
                return;
            }
        }
    }

    // en la matriz me sale la misma fila repetida debe rellenarse con la siguiente palabra




    //int k=0;

    /*for(int j=0; wordsOfDictionary[j]!=' '; j++){
        result[k].name[j]=wordsOfDictionary[j];
    }  */





   // printf(">>>wordsOfDictionary<<<< = %s\n",    wordsOfDictionary);






}


void printMatchingWords(char **wordsOfDictionary,char pattern[], int length,wordType result[] ){

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
        stepWordDynamically(wordsOfDictionary, pattern,length,result );

        //stepWordDynamically(wordsOfDictionary,wordUser,totalWords, result);


        /*if(same == 0){
            //lineBreak(wordsOfDictionary[i],firstWordOfTheRow, definitionOfWord, definitionsMatrix);
           //fillWordsStructure(wordsOfDictionary[i], wordUser);
        }*/

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
void lineBreak(char *wordsOfDictionary, char firstWordOfTheRow[], char definitionOfWord[], char** matrix){

    int i=0;
    int length=0;
    int index=0;
    int j=0;
    int counter =0;
    char *p;
    char space[5]="    ";
    int g=0;

    for(i=0; wordsOfDictionary[i]!=' '; i++){
        firstWordOfTheRow[i]=wordsOfDictionary[i];
    }

    firstWordOfTheRow[i]='\0';
    index=i;

    for(int l=0; wordsOfDictionary[l]!='\0'; l++){
        definitionOfWord[l]=wordsOfDictionary[index];
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
            if(definitionOfWord[j-1]=='#'&& matrix[i][g]=='-'){
                matrix[i][k]=definitionOfWord[j];
                k++;
                j++;
            }
            for(int z=0; definitionOfWord[j]!='.'&& definitionOfWord[j+1]==' '; z++){
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
        if(definitionOfWord[j]=='.'){
            matrix[i][k]=definitionOfWord[j];
            k++;
            matrix[i][k]='\0';
            i++;
            k=0;
            for(int m=0; m<4; m++){
                matrix[i][k]=space[m];
                k++;
            }
            j++;
        }
        if(definitionOfWord[j]>=49 && definitionOfWord[j]<58){
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

/*
void lineBreak(char *wordsOfDictionary, char firstWordOfTheRow[], char definitionOfWord[], char** matrix){

    int i=0;
    int length=0;
    int index=0;
    int j=0;
    int counter =0;
    char *p;
    char space[5]="    ";
    int g=0;

    for(i=0; wordsOfDictionary[i]!=' '; i++){
        firstWordOfTheRow[i]=wordsOfDictionary[i];
    }

    firstWordOfTheRow[i]='\0';
    index=i;

    for(int l=0; wordsOfDictionary[l]!='\0'; l++){
        definitionOfWord[l]=wordsOfDictionary[index];
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
            if(definitionOfWord[j-1]=='#'&& matrix[i][g]=='-'){
                matrix[i][k]=definitionOfWord[j];
                k++;
                j++;
            }
            for(int z=0; definitionOfWord[j]!='.'&& definitionOfWord[j+1]==' '; z++){
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
        if(definitionOfWord[j]=='.'){
            matrix[i][k]=definitionOfWord[j];
            k++;
            matrix[i][k]='\0';
            i++;
            k=0;
            for(int m=0; m<4; m++){
                matrix[i][k]=space[m];
                k++;
            }
            j++;
        }
        if(definitionOfWord[j]>=49 && definitionOfWord[j]<58){
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
*/
/*********************************************************/
/************ IMPLEMENTATION OF FUNCTIONS ****************/
/*********************************************************/
void toLowerCase(char wordsOfDictionary[]){

    for(int i=0; wordsOfDictionary[i]!='\0'; i++){
        if(wordsOfDictionary[i]>=65 && wordsOfDictionary[i]<=90){
            wordsOfDictionary[i]=wordsOfDictionary[i]+32;
        }

        if(i==0){
            wordsOfDictionary[0]=wordsOfDictionary[0]-32;
        }
    }
}

int beginningsAreTheSame(char *word1,char word2[]){

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



