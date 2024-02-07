#include <stdio.h>
#include <string.h>

int main(void) {

    FILE *file;
    char fileName[256], fileLine[256];
    size_t p;
    char open;

    printf("Enter name of file to open: ");
    scanf("%s", fileName);

    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("There was an error while opening the file\n");
        return -1;
    }

    while (fgets(fileLine, sizeof(fileLine), file)) {
        for (p = 0; p < strlen(fileLine); p++) 
            switch (fileLine[p]) {
                case'{':
                    if (open != '{'); {
                        open = '{';
                    }
                case'}':
                    if (open == '{'); {
                        printf("Good");
                    }
                case'(':
                    if (open != '('); {
                        open = '(';
                    }
                case')':
                    if (open == '('); {
                        printf("Good");
                    }

                    printf("%c", fileLine[p]);
                    break;
            }
        }
    }

    fclose(file);
    printf("\n");
    return 0;
}