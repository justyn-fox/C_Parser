#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define size 1000

int main(void) {

    FILE *file;
    char fileName[256], fileLine[256];
    char stack [size];
    int errorLine;
    size_t p;

    int lineNum = 0;
    int top = -1;

    bool missing_op = false;
    bool missing_ob = false;

    printf("Enter name of file to open: ");
    scanf("%s", fileName);

    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("There was an error while opening the file\n");
        return -1;
    }

    while (fgets(fileLine, sizeof(fileLine), file)) {
        if (stack[top] != '\0' && top != -1){
            if (stack[top] == '(' && missing_op == false){
            missing_op = true;
            errorLine = lineNum;
            }
            else if (stack[top] == '[' && missing_ob == false) {
                missing_ob = true;
                errorLine = lineNum;
            }
        }
        lineNum++;
        for (p = 0; p < strlen(fileLine); p++) {
            if(fileLine[p] != '/' && fileLine[p + 1] != '/') {
                switch (fileLine[p]) {
                case'{':
                    if (stack[top] == '{'){
                        printf("ERROR: Missing closing brace. At line: %d\n", lineNum);
                    }
                    top++;
                    stack[top] = fileLine[p];
                    break;

                case'(':
                    if (stack[top] == '('){
                        missing_op = false;
                        errorLine = lineNum;
                    }
                    top++;
                    stack[top] = fileLine[p];
                    break;

                case '[':
                    if (stack[top] == '['){
                        missing_ob = false;
                        errorLine = lineNum;
                    }
                    top++;
                    stack[top] = fileLine[p];
                    break;

                case'}':
                    int start_brace = top;
                    for(top ; top > -1 ; top--){
                        if(top == 0 && stack[top] != '{'){
                            printf("ERROR: Missing open brace. At line: %d\n" , lineNum);
                        }
                        else if (stack[top] == '{')
                        {
                            stack[top] = '\0';
                            break;
                        }
                    }
                    top = start_brace;
                    break;

                case')':
                    int start_p = top;
                    for(top ; top > -1 ; top--){
                        if(top == 0 && stack[top] != '('){
                            printf("ERROR: Missing open parenthesis. At line: %d\n" , lineNum);
                        }
                        else if (stack[top] == '(')
                        {
                            if (missing_op == true){
                                missing_op = false;
                                errorLine = 0;
                            }
                            stack[top] = '\0';
                            break;
                        }
                    }
                    top = start_p;
                    break;

                case']':
                    int start_brack = top;
                    for(top ; top > -1 ; top--){
                        if(top == 0 && stack[top] != '['){
                            printf("ERROR: Missing open bracket. At line: %d\n" ,lineNum);
                        }
                        else if (stack[top] == '[')
                        {
                            if (missing_ob == true){
                                missing_ob = false;
                                errorLine = 0;
                            }
                            stack[top] = '\0';
                            break;
                        }
                    }
                    top = start_brack;
                    break;
            
                }
            }
        }
    }
    for(top ; top > -1 ; top--){
        if (stack[top] == '('){
            printf("ERROR: Missing closing parenthesis. At line: %d \n", errorLine);
        }
        else if (stack[top] == '['){
            printf("ERROR: Missing closing bracket. At line: %d \n", errorLine);
        }
        else if (stack[top] == '{'){
            printf("ERROR: Missing closing brace. At line: %d \n", lineNum);
        }
    }

    fclose(file);
    printf("\n");
    return 0;
}