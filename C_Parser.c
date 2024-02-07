#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define max_stack 1000

typedef enum {
    none,
    open_brace,
    open_parenthesis,
    open_bracket,
} BracketType;

char *errorMessages[] = {
    "missing closing brace '}'",
    "missing closing parenthesis ')'.",
    "missing closing bracket ']'."
};

int main(void) {

    FILE *file;
    char fileName[256], fileLine[256];
    size_t p;
    int lineNum = 0;

    printf("Enter name of file to open: ");
    scanf("%s", fileName);

    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("There was an error while opening the file\n");
        return -1;
    }

    bool comment = false;
    BracketType stack[max_stack];
    int top = -1; 
    
    while (fgets(fileLine, sizeof(fileLine), file)) {
        bool ignoreSpaces = false;
        for (p = 0; p < strlen(fileLine); p++) {
            if (isspace(fileLine[p])) {
                ignoreSpaces = false;
                continue;
            } 
            if (!comment && fileLine[p] == '/' && fileLine[p + 1] == '/') {
                comment = true;
                continue;
            }
            if (comment && fileLine[p] == '\n') {
                comment = false;
            }
            if (comment) {
                continue;
            }
            if (ignoreSpaces) {
                continue;
            }

            switch (fileLine[p]) {
                case'{':
                    if (top != -1 && stack[top] != none) {
                        printf("syntax error on line %d: %s\n", lineNum + 1, errorMessages[top]);
                        fclose(file);
                        return 1;
                    }
                    stack[++top] = open_brace;
                    ignoreSpaces = true;
                    break;

                case'(':
                    if (top != -1 && stack[top] != none) {
                        printf("syntax error on line %d: %s\n", lineNum + 1, errorMessages[top]);
                        fclose(file);
                        return 1;
                    }
                    stack[++top] = open_parenthesis;
                    ignoreSpaces = true;
                    break;
                
                case '[':
                    if (top != -1 && stack[top] != none) {
                        printf("Syntax error on line %d: %s\n", lineNum +  1, errorMessages[top]);
                        fclose(file);
                        return  1;
                    }
                    stack[++top] = open_bracket;
                    ignoreSpaces = true;
                    break;

                case'}':
                    if (top == -1 || stack[top] != open_brace) {
                        printf("syntax error on line %d: missing opening brace '{'. \n", lineNum + 1);
                        fclose(file);
                        return 1;
                    }
                    top--;
                    break;

                case')':
                    if (top == -1 || stack[top] != open_parenthesis) {
                        printf("syntax error on line %d: missing opening parenthesis '('. \n", lineNum + 1);
                        fclose(file);
                        return 1;
                    }
                    top--;
                    break;
                
                case']':
                    if (top == -1 || stack[top] != open_bracket) {
                        printf("syntax error on line %d: missing opening bracket '['. \n", lineNum + 1);
                        fclose(file);
                        return 1;
                    }
                    top--;
                    break;
            }
        }
        lineNum++;
    }

    if (top != -1) {
        printf("syntax error on line %d: %s\n", lineNum, errorMessages[top]);
        fclose(file);
        return 1;
    }

    fclose(file);
    printf("\n");
    return 0;
}