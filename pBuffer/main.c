#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Área reservada para variveis de controle
#define LOOP_COUNTER            *(unsigned short int*)(buffer)                                      
#define COUNTER_CHAR            *(unsigned short int*)(buffer + (sizeof(unsigned short int) * 1))   
#define TARGET_GET              *(unsigned short int*)(buffer + (sizeof(unsigned short int) * 2))
#define WORD_COUNTER_TBN        *(unsigned short int*)(buffer + (sizeof(unsigned short int) * 3))
#define WORD_LIST_LENGTH        *(unsigned short int*)(buffer + (sizeof(unsigned short int) * 4))
#define OPERATION_INPUT         *(unsigned short int*)(buffer + (sizeof(unsigned short int) * 5))
// Área reservada para input temporário (até 79 chars + '\0')
#define WORD_INPUT_BASE         (sizeof(unsigned short int) * 6)   
#define WORD_INPUT              ((char*)((char*)(buffer) + WORD_INPUT_BASE))
// Área onde fica a lista de datas
// No formato: [len_nome][nome][len_email][email][idade]
#define WORD_LIST_BASE          (WORD_INPUT_BASE + (sizeof(char) * 80)) 
#define WORD_LIST               ((char*)((char*)(buffer) + WORD_LIST_BASE))

char *buffer = NULL;    

void pushInfo() {
    printf("Insert a name:\n");
    scanf(" %78[^\n]", WORD_INPUT + 1);
    WORD_INPUT[0] = (char) strlen(WORD_INPUT + 1);
    buffer = realloc(buffer, WORD_LIST_BASE + (sizeof(char) * (strlen(WORD_LIST) + strlen(WORD_INPUT) + 1)));
    strcat(WORD_LIST, WORD_INPUT);

    printf("Insert an email:\n");
    scanf(" %78[^\n]", WORD_INPUT + 1);
    WORD_INPUT[0] = (char) strlen(WORD_INPUT + 1);
    buffer = realloc(buffer, WORD_LIST_BASE + (sizeof(char) * (strlen(WORD_LIST) + strlen(WORD_INPUT) + 1)));
    strcat(WORD_LIST, WORD_INPUT);

    printf("Insert an age:\n");
    scanf(" %1[^\n]", WORD_INPUT); 
    buffer = realloc(buffer,WORD_LIST_BASE + (sizeof(char) * (strlen(WORD_LIST) + strlen(WORD_INPUT) + 1)));
    strcat(WORD_LIST, WORD_INPUT);

    WORD_LIST_LENGTH = WORD_LIST_LENGTH + 1; 
    WORD_INPUT[0] = '\0';
}

void skipPerson() {
    WORD_COUNTER_TBN = WORD_COUNTER_TBN + 1 + (unsigned char) WORD_LIST[WORD_COUNTER_TBN];
    WORD_COUNTER_TBN = WORD_COUNTER_TBN + 1 + (unsigned char) WORD_LIST[WORD_COUNTER_TBN];
    WORD_COUNTER_TBN = WORD_COUNTER_TBN + 1;
}

void printPersonByTarget() {
    if (TARGET_GET == 0 || TARGET_GET > WORD_LIST_LENGTH)
        return;

    WORD_COUNTER_TBN = 0;
    LOOP_COUNTER = 1;

    while (LOOP_COUNTER < TARGET_GET) {
        skipPerson();
        LOOP_COUNTER = LOOP_COUNTER + 1;
    }

    COUNTER_CHAR = (unsigned char)WORD_LIST[WORD_COUNTER_TBN];
    WORD_COUNTER_TBN = WORD_COUNTER_TBN + 1;
    printf("Name: %.*s\n", COUNTER_CHAR, WORD_LIST + WORD_COUNTER_TBN);
    WORD_COUNTER_TBN = WORD_COUNTER_TBN + COUNTER_CHAR;
    COUNTER_CHAR = (unsigned char)WORD_LIST[WORD_COUNTER_TBN];
    WORD_COUNTER_TBN = WORD_COUNTER_TBN + 1;
    printf("Email: %.*s\n", COUNTER_CHAR, WORD_LIST + WORD_COUNTER_TBN);
    WORD_COUNTER_TBN = WORD_COUNTER_TBN + COUNTER_CHAR;
    printf("Age: %c\n", WORD_LIST[WORD_COUNTER_TBN]);
}

// Procura pessoa pelo nome e guarda a posição em TARGET_GET (Se não achar -> SHRT_MAX)
void searchPersonByName() {
    printf("Search name:\n");
    scanf(" %78[^\n]", WORD_INPUT + 1);
    WORD_INPUT[0] = (char)strlen(WORD_INPUT + 1);

    TARGET_GET = SHRT_MAX;      
    LOOP_COUNTER = 0;
    WORD_COUNTER_TBN = 0;

    while (LOOP_COUNTER < WORD_LIST_LENGTH) {
        COUNTER_CHAR = (unsigned char) WORD_LIST[WORD_COUNTER_TBN];
        if (COUNTER_CHAR == (unsigned char) WORD_INPUT[0]) {
            if (strncmp(WORD_LIST + WORD_COUNTER_TBN + 1, WORD_INPUT + 1, COUNTER_CHAR) == 0) {
                TARGET_GET = LOOP_COUNTER + 1;
                return;
            }
        }
        skipPerson();
        LOOP_COUNTER = LOOP_COUNTER + 1;
    }
}


// Remove uma pessoa pelo nome, compactando o vetor com memmove
void removePersonByName() {
    searchPersonByName();

    if (TARGET_GET == SHRT_MAX) 
        printf("Person not found.\n");
    else{
        printf("Person removed.\n");

        WORD_COUNTER_TBN = 0;
        LOOP_COUNTER = 1;
        while (LOOP_COUNTER < TARGET_GET) {
            skipPerson();              
            LOOP_COUNTER = LOOP_COUNTER + 1;
        }

        TARGET_GET = WORD_COUNTER_TBN; 

        WORD_COUNTER_TBN = TARGET_GET;
        skipPerson();                         
        OPERATION_INPUT = WORD_COUNTER_TBN - TARGET_GET;  

        WORD_COUNTER_TBN = strlen(WORD_LIST) + 1;         
        WORD_COUNTER_TBN = WORD_COUNTER_TBN - TARGET_GET; 
        WORD_COUNTER_TBN = WORD_COUNTER_TBN - OPERATION_INPUT; 

        memmove(WORD_LIST + TARGET_GET, WORD_LIST + TARGET_GET + OPERATION_INPUT, WORD_COUNTER_TBN);

        WORD_LIST_LENGTH = WORD_LIST_LENGTH - 1;
    }
}

void printAllInfo() {
    WORD_COUNTER_TBN = 0;  
    LOOP_COUNTER = 1;       

    while (LOOP_COUNTER <= WORD_LIST_LENGTH) {

        printf("Person %hu:\n", LOOP_COUNTER);
        COUNTER_CHAR = (unsigned char) WORD_LIST[WORD_COUNTER_TBN];
        WORD_COUNTER_TBN = WORD_COUNTER_TBN + 1;

        printf("Name: %.*s\n", COUNTER_CHAR, WORD_LIST + WORD_COUNTER_TBN);
        WORD_COUNTER_TBN = WORD_COUNTER_TBN + COUNTER_CHAR;
        COUNTER_CHAR = (unsigned char) WORD_LIST[WORD_COUNTER_TBN];
        WORD_COUNTER_TBN = WORD_COUNTER_TBN + 1;

        printf("Email: %.*s\n", COUNTER_CHAR, WORD_LIST + WORD_COUNTER_TBN);
        WORD_COUNTER_TBN = WORD_COUNTER_TBN + COUNTER_CHAR;

        printf("Age: %c\n\n", WORD_LIST[WORD_COUNTER_TBN]);
        WORD_COUNTER_TBN = WORD_COUNTER_TBN + 1;
        LOOP_COUNTER = LOOP_COUNTER + 1;
    }
}



int main() {
    buffer = malloc(WORD_LIST_BASE + 1);
    WORD_LIST_LENGTH = 0;
    TARGET_GET = 0;
    WORD_INPUT[0] = '\0'; 
    WORD_LIST[0] = '\0';

    do{
        printf( "1- Add Person\n"
                "2- Remove Person\n"
                "3- Search Person\n"
                "4- List All\n"
                "5- Exit\n\n");
        
        scanf(" %hu", &OPERATION_INPUT);

        switch (OPERATION_INPUT) {
            case 1: { 
                pushInfo();
            } break;
            case 2: { 
                if (WORD_LIST_LENGTH == 0)
                    printf("List is empty.\n");
                else
                  removePersonByName();
            } break;

            case 3: { 
                if (WORD_LIST_LENGTH == 0) 
                    printf("List is empty.\n");
                else {
                    searchPersonByName();
                    if (TARGET_GET == SHRT_MAX)
                        printf("Person not found.\n");
                    else
                        printPersonByTarget();
                }
            } break;

            case 4: { 
                if (WORD_LIST_LENGTH == 0) 
                    printf("List is empty.\n");
                else 
                    printAllInfo();  
            } break;

            case 5: {
                printf("Exiting...\n");
            } break;
            
            default: {
                printf("Invalid Entry. Please, try again.\n\n");
            } break;
        }
    } while (OPERATION_INPUT != 5);

    free(buffer);
    return 0;
}