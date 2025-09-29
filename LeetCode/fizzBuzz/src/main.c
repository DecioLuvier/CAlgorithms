#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** fizzBuzz(int n, int* returnSize) {
    char **response = malloc(n * sizeof(char *));

    for(int i = 0; i < n; i++){
        char* _buffer = malloc(1 * sizeof(char));
        _buffer[0] = '\0';
        response[i] = _buffer;
    }

    *returnSize = 0;
    for(int i = 0; i < n; i++){
        char _buffer[8] = "";
        if(((i + 1) % 3 != 0) && ((i + 1) % 5 != 0)) 
            sprintf(_buffer, "%d", i + 1);
        if((i + 1) % 3 == 0)
            strcat(_buffer, "Fizz");
        if((i + 1) % 5 == 0)
            strcat(_buffer, "Buzz");

        int newStrLenght = (strlen(_buffer) + 1) * sizeof(char);
        *returnSize =  *returnSize + newStrLenght;

        response[i] = realloc(response[i], newStrLenght);
        memcpy(response[i], _buffer, newStrLenght);        
    }

    return response;
}

int main(int argc, char const *argv[])
{
    printf("Hello World!\n");

    return 0;
}
