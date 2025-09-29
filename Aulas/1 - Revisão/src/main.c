#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shiftString(char *adress, int bits);

int main(){
    char *database = malloc(1 * sizeof(char));
    memset(database, '\0', 1);
    int selectedOperation = 0;

    while(1){
        printf("\n\n");
        printf( "Welcome! Please, insert the operation:\n"
                "1) Add new person\n"
                "2) Remove person by name\n"
                "3) List all\n"
                "4) Exit\n\n");
        scanf(" %d", &selectedOperation);

        switch (selectedOperation){
            case 1: {
                char buffer[52] = "";
                printf("Insert the person name:(max 50 letters) \n");
                scanf(" %50[^\n]", buffer);
                shiftString(buffer, 1);
                buffer[0] = '-';
                buffer[strlen(buffer)] = '\n';
                database = (char *) realloc(database, strlen(buffer) + strlen(database) * sizeof(char));
                strcat(database, buffer);
                break;
            }
            case 2: {
                char buffer[52] = "";
                printf("Insert the person name:(max 50 letters) \n");
                scanf(" %50[^\n]", buffer);
                shiftString(buffer, 1);
                buffer[0] = '-';
                buffer[strlen(buffer)] = '\n';
                for(unsigned int i = 0; i < strlen(database); i++){
                    if(strncmp(database + i, buffer, strlen(buffer)) == 0){
                        shiftString(database + i + strlen(buffer), -strlen(buffer));
                        database = (char *) realloc(database, strlen(database) * sizeof(char));
                        break;
                    }
                }
                break;
            }
            case 3: {
                printf("%s", database);
                break;
            }
            case 4: {
                return 0;
                break;
            }
            default: {
                printf("invalid operation, try again:\n");
                break;
            }
        }
    }    
}

void shiftString(char *adress, int bits){
    memmove(adress + bits, adress, strlen(adress) + 1);
}