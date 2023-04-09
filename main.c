#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char word[20];
    int lineNum;
    int colNum;
    struct Node *next;
};

void printList(struct Node *n) {
    while(n != NULL){
        for (int i = 0; n->word[i] != '\0'; i++) {
            printf("%c", n->word[i]);
        }
        printf(" %d:%d", n->lineNum, n->colNum);
        n = n->next;
        printf("\n");
    }
}


int colNum = 1;
int lineNum = 1;
int letter;

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    struct Node *head = NULL;
    struct Node *currNode = NULL;

    letter = fgetc(file);

    while (letter != EOF) {

        //NEW LINE IDENTIFIER
        if (letter == '\n') {
            lineNum++;
            colNum = 0;
        }


            //FOR SPECIAL CHARACTERS
        else if (letter == '(' || letter == ')' || letter == '[' || letter == ']' || letter == '{' || letter == '}') {
            struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
            if (letter == '(') {
                strcpy(newNode->word, "LEFTPAR");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            else if (letter == ')') {
                strcpy(newNode->word, "RIGHTPAR");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            else if (letter == '[') {
                strcpy(newNode->word, "LEFTSQUAREB");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            else if (letter == ']') {
                strcpy(newNode->word, "RIGHTSQUAREB");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            else if (letter == '{') {
                strcpy(newNode->word, "LEFTCURLYB");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            else if (letter == '}') {
                strcpy(newNode->word, "RIGHTCURLYB");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }


            newNode->next = NULL;

            if (head == NULL) {
                head = newNode;
                currNode = newNode;
            }
            else {
                currNode->next = newNode;
                currNode = newNode;
            }
        }

            //IDENTIFIER
        else if ((letter >= 'a' && letter <= 'z') || letter == '!' || letter == '*' || letter == '/' || letter == ':' ||
                 letter == '<' || letter == '=' || letter == '>' || letter == '?') {
            struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
            char tempWord[20];
            tempWord[0] = letter;
            int iteration = 1;
            int i = 1;
            while (((letter = fgetc(file)) != EOF) && (letter != ' ' && letter != '(' && letter != ')' && letter != '[' && letter != ']' && letter != '{' && letter != '}' && letter != '\n' && letter != '\t' && letter != '\r')) {
                if ((letter >= 'a' && letter <= 'z') || (letter >= '0' && letter <= '9') || letter == '.' ||
                    letter == '+' || letter == '-') {
                    tempWord[i] = letter;
                    i++;
                    iteration++;
                }
                else {
                    tempWord[i] = letter;
                    i++;
                    tempWord[i] = '\0';
                    iteration++;
                    printf("LEXICAL ERROR [%d:%d]: Invalid token '%s'", lineNum, colNum, tempWord);
                    exit(1);
                }
            }

            tempWord[i] = '\0';

            if(strcmp(tempWord, "define") == 0){
                strcpy(newNode->word, "DEFINE");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            else if(strcmp(tempWord, "let") == 0){
                strcpy(newNode->word, "LET");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            else if(strcmp(tempWord, "cond") == 0){
                strcpy(newNode->word, "COND");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            else if(strcmp(tempWord, "if") == 0){
                strcpy(newNode->word, "IF");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            else if(strcmp(tempWord, "begin") == 0){
                strcpy(newNode->word, "BEGIN");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            else if(strcmp(tempWord, "true") == 0){
                strcpy(newNode->word, "BOOLEAN");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            else if(strcmp(tempWord, "false") == 0){
                strcpy(newNode->word, "BOOLEAN");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            else {
                strcpy(newNode->word, "IDENTIFIER");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
            }
            newNode->next = NULL;

            if (head == NULL) {
                head = newNode;
                currNode = newNode;
            } else {
                currNode->next = newNode;
                currNode = newNode;
            }
            colNum += iteration;
            continue;
        }

        //CHAR DAHA ERROR KISIMLARI YAPILMADI !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        else if(letter == '\''){
            struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
            int iteration = 0;
            while ((letter = fgetc(file)) != EOF){
                iteration++;
                if(letter == '\''){
                    strcpy(newNode->word, "CHAR");
                    newNode->colNum = colNum;
                    newNode->lineNum = lineNum;
                    break;
                }

            }
            newNode->next = NULL;

            if (head == NULL) {
                head = newNode;
                currNode = newNode;
            } else {
                currNode->next = newNode;
                currNode = newNode;
            }
            colNum += iteration;
        }

        //STRING DAHA ERROR KISIMLARI YAPILMADI !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        else if(letter == '\"'){
            struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
            int iteration = 0;
            while ((letter = fgetc(file)) != EOF){
                iteration++;
                if(letter == '\"'){
                    strcpy(newNode->word, "STRING");
                    newNode->colNum = colNum;
                    newNode->lineNum = lineNum;
                    break;
                }

            }
            newNode->next = NULL;

            if (head == NULL) {
                head = newNode;
                currNode = newNode;
            } else {
                currNode->next = newNode;
                currNode = newNode;
            }
            colNum += iteration;
        }

            //NUMBERS
        else if(letter == '-' || letter == '+' || (letter >= '0' && letter <= '9')){
            struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
            char tempWord[20];
            tempWord[0] = letter;
            int iteration = 1;
            int i = 1;
            if(letter == '+' || letter == '-'){
                while (((letter = fgetc(file)) != EOF) && (letter != ' ' && letter != '(' && letter != ')' && letter != '[' && letter != ']' && letter != '{' && letter != '}' && letter != '\n' && letter != '\t' && letter != '\r')) {
                    if ((letter >= '0' && letter <= '9') || letter == '.') {
                        tempWord[i] = letter;
                        i++;
                        iteration++;
                    }
                    else {
                        tempWord[i] = letter;
                        i++;
                        tempWord[i] = '\0';
                        iteration++;
                        printf("LEXICAL ERROR [%d:%d]: Invalid token '%s'", lineNum, colNum, tempWord);
                        exit(1);
                    }
                }
                strcpy(newNode->word, "NUMBER");
                newNode->colNum = colNum;
                newNode->lineNum = lineNum;
                continue;
            }
            else if(letter == '0'){
                letter = fgetc(file);
                iteration++;
                if(letter == 'x'){

                }
                else if(letter == 'b'){

                }
                else{
                    while ((letter != EOF) && (letter != ' ' && letter != '(' && letter != ')' && letter != '[' && letter != ']' && letter != '{' && letter != '}' && letter != '\n' && letter != '\t' && letter != '\r')) {
                        if ((letter >= '0' && letter <= '9') || letter == '.') {
                            tempWord[i] = letter;
                            i++;
                            iteration++;
                            letter = fgetc(file);
                        }
                        else {
                            tempWord[i] = letter;
                            i++;
                            tempWord[i] = '\0';
                            iteration++;
                            printf("LEXICAL ERROR [%d:%d]: Invalid token '%s'", lineNum, colNum, tempWord);
                            exit(1);
                        }
                    }
                    strcpy(newNode->word, "NUMBER");
                    newNode->colNum = colNum;
                    newNode->lineNum = lineNum;
                    continue;
                }
            }
            else{

            }

            newNode->next = NULL;

            if (head == NULL) {
                head = newNode;
                currNode = newNode;
            }
            else {
                currNode->next = newNode;
                currNode = newNode;
            }
            colNum += iteration;
        }







        colNum++;
        letter = fgetc(file);
    }


    if (head == NULL) {
        printf("Input file is empty\n");
        return 1;
    }

    printList(head);




    fclose(file);
    return 0;
}