#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_DEF 100
#define MAX_RESULT 5
#define MAX_DEFINITION 5
#define KEYWORD "$%&"

typedef struct{
    char type[100];
    char values[MAX_DEFINITION][500];
}definitionType;

typedef struct{
    char name[30];
    definitionType definitions[20];
}wordType;

int beginningsAreTheSame(char *word1, char word2[]);
void toLowerCase(char wordsOfDictionary[]);
void lineBreak(char *wordsOfDictionary, char firstWordOfTheRow[], char definitionOfWord[], char** matrix);
void fillWordsStructure(char **rawResults, char searchedWord[], wordType result[]);
void stepWordDynamically( char **wordsOfDictionary,char wordUser[], int lengthWordDiccionary, wordType result[]);
void tableTypeAndDefinitions(char * rawString, char** typesAndDefinitions);
void fillFromTableToStructure(wordType* structure, char** typesAndDefinitions);
void removeHashtag(char* hashtag);
void removeFirstWord(char* removeNumbers);
void printStructure(wordType structure);
void fillStructureFromPhrase( char* phrase, wordType* structure);
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
    wordType result[MAX_RESULT];

    FILE *f; // declaracion de un fichero
    f = fopen("english_dictionary.txt","r");


    if(f==NULL){
        printf("Can't open \n");
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
        printf("\n\nIntroduce a word\n");
        gets(wordUser);
        system("cls");
        stepWordDynamically(wordsOfDictionary,wordUser,totalWords,result);
        for(int j=0; strcmp(result[j].name,KEYWORD)!=0 && j<MAX_RESULT; j++){
                printStructure(result[j]);
        }
    }

    return 0;
}
void fillStructureFromPhrase( char* phrase, wordType* structure){

    char ** typesAndDefinitions;

    //Memory allocation
    typesAndDefinitions = (char**)malloc(sizeof(char*)*100);
    for(int i=0; i<100; i++){
        typesAndDefinitions[i] = malloc(sizeof(char)*500);
    }
   tableTypeAndDefinitions( phrase, typesAndDefinitions);
   fillFromTableToStructure(structure, typesAndDefinitions);

   //Free memory
    for(int i=0; i<100; i++){
        free(typesAndDefinitions[i]);
    }
    free(typesAndDefinitions);

}

void stepWordDynamically(char **wordOfDictionary, char wordUser[], int lengthWordDiccionary, wordType result[] ){

    int same =1;
    int i=0;
    int j=0;


    for(i = 0; i < lengthWordDiccionary; i++){
        same=beginningsAreTheSame(wordOfDictionary[i],wordUser);
        if(same == 0){
            if(j<MAX_RESULT){
                fillStructureFromPhrase(wordOfDictionary[i],&result[j]);
                j++;
            }

        }
    }
    if(j<MAX_RESULT){
        strcpy(result[j].name,KEYWORD);
    }
}

void tableTypeAndDefinitions(char *rawString, char** typesAndDefinitions){

    int col = 0;    //Columna
    int row = 0;  // row

    for(int i=0; rawString[i]!='\0'; i++){

        if(rawString[i]==' ' && rawString[i+1]=='#'){
            typesAndDefinitions[row][col]='\0';
            col=0;
            row++;
        }
        else if(rawString[i]==' ' && (rawString[i+1]>=49 && rawString[i+1]<58)){
            typesAndDefinitions[row][col]='\0';
            row++;
            col=0;
        }
        else{
            typesAndDefinitions[row][col]=rawString[i];
            col++;
        }
        if(row>=100){
            return;
        }
        if(rawString[i+1]=='\0'){
            row++;
            strcpy(typesAndDefinitions[row],KEYWORD);
        }
    }
}

void removeHashtag(char* hashtag){

    int j=0;
    for(int i=0; hashtag[i]!='\0'; i++){
        if(hashtag[i]=='#'){
            i++;
        }
        hashtag[j]=hashtag[i];
        j++;
    }
    hashtag[j]='\0';

}
void removeFirstWord(char* removeNumber){

    int j=0;

    for(int i=0; removeNumber[i]!='\0'; i++){
        if(removeNumber[i]>=49 && removeNumber[i]<58){
          i++;
        }
        else{
            removeNumber[j]=removeNumber[i];
            j++;
        }
    }
    removeNumber[j]='\0';
}

void fillFromTableToStructure( wordType* structure, char** typesAndDefinitions){

    int p=0;
    int m=0;
    int counter=0;
    int k=0;

       for(int i=0; strcmp(typesAndDefinitions[i],KEYWORD)!=0 && i<MAX_DEFINITION;   i++){
            if(i==0){
                strcpy(structure->name,typesAndDefinitions[i]);
            }
            else if(typesAndDefinitions[i][0]=='#'){
                removeHashtag(typesAndDefinitions[i]);
                typesAndDefinitions[i][99]=0;
                strcpy(structure->definitions[k].type,typesAndDefinitions[i]);
                m=0;
            }
            else if(typesAndDefinitions[i][0]>=49 && typesAndDefinitions[i][0]<58 ){
                if(m < MAX_DEFINITION){
                    removeFirstWord(typesAndDefinitions[i]);
                    strcpy(structure->definitions[k].values[m],typesAndDefinitions[i]);
                    m++;
                }
                if( m <MAX_DEFINITION){
                    strcpy(structure->definitions[k].values[m],KEYWORD);
                }

                if(m >= MAX_DEFINITION || strcmp(typesAndDefinitions[i+1],KEYWORD)==0 || i == (MAX_DEFINITION-1)){
                    k++;
                }
            }
            else {
                if(m < MAX_DEFINITION){
                    strcpy(structure->definitions[k].values[m],typesAndDefinitions[i]);
                    m++;
                }
                if( m <MAX_DEFINITION){
                    strcpy(structure->definitions[k].values[m],KEYWORD);
                }
                if(m >= MAX_DEFINITION || strcmp(typesAndDefinitions[i+1],KEYWORD)==0){
                    k++;
                }
            }

        }

        if(k<MAX_DEFINITION){
            strcpy(structure->definitions[k].type,KEYWORD);
        }
}
void printStructure(wordType structure){

    int i=0;
    int j=0;
    int m=0;

    printf("\n\n<<<<<%s>>>>>\n ",structure.name);

    for(i=0;  i < MAX_DEFINITION &&  strcmp(structure.definitions[i].type,KEYWORD)!=0 ; i++){
    printf("\n-%s", structure.definitions[i].type);
    if(i>0){
        m++;
    }
    for(j=0; j< MAX_DEFINITION && strcmp(structure.definitions[m].values[j],KEYWORD)!=0; j++){
        printf("\n\t%s\n",structure.definitions[m].values[j]);
       }
   }

}


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



