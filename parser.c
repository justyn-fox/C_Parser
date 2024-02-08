#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(void) {

    FILE *file;
    char fileName[256], fileLine[256];
    size_t p;

    int lineNum = 0;
    int open_brace = 0;
    int open_parenthesis = 0;
    int open_bracket = 0;
    int closed_parenthesis = 0;
    int closed_bracket = 0;

    bool parenthesis_caught = false;

    printf("Enter name of file to open: ");
    scanf("%s", fileName);

    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("There was an error while opening the file\n");
        return -1;
    }

    while (fgets(fileLine, sizeof(fileLine), file)) {
        lineNum++;
        for (p = 0; p < strlen(fileLine); p++) {
        
            if(fileLine[p] != '/' && fileLine[p + 1] != '/') {
                switch (fileLine[p]) {
                case'{':
                    open_brace++; 
                    break;

                case'(':
                    closed_parenthesis = lineNum; 
                    open_parenthesis++;
                    break;

                case '[':
                    open_bracket++;
                    closed_bracket = lineNum;
                    break;

                case'}':
                    if (open_brace == 0) {
                        printf("ERROR: Missing an open brace. At line: %d \n ", lineNum);
                    }
                    else {
                        open_brace--;
                    }
                    break;

                case')':
                    if (open_parenthesis == 0) {
                        printf("ERROR: Missing an open parenthesis. At line: %d \n", lineNum);
                    }
                    else {
                        open_parenthesis--;
                        
                    }
                    break;

                case']':
                    if (open_bracket == 0) {
                        printf("ERROR: Missing an open bracket. At line: %d \n ", lineNum);
                    }
                    else {
                        open_bracket--;
                    }
                    break;
            
                }
            }
        }
    }

    if (open_brace > 0 ) {
        printf("ERROR: Missing closing braces. At line: %d \n", lineNum);
        open_brace = 0;
    }

    if (open_parenthesis > 0 ) {
        printf("ERROR: Missing a closing parenthesis. At line: %d \n", closed_parenthesis);
        open_parenthesis = 0;
    }

    if (open_bracket > 0 ) {
        printf("ERROR: Missing closing brackets. At line: %d \n", lineNum);
        open_bracket = 0;
    }

    fclose(file);
    printf("\n");
    return 0;
}