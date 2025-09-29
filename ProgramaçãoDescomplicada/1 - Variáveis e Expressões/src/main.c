#include <stdio.h>

/* 
    46. ​​Write a program that reads a positive integer.
    Generates another number formed by the inverted digits of the number read. Example:
        Number read: 123
        Number generated: 321
    Without converting the integer to a character.
*/

int mirrorInteger(int positiveNumber);
int getIntegerLength(int number);
int getIntegerIndex(int number, int index);
int shiftInteger(int number, int times);

int main(){
    int userInput = 0; 
    printf("Please, insert a number:\n");
    scanf("%d", &userInput);

    printf("-> shiftInteger | %d two times ->%d\n", userInput, shiftInteger(userInput,2));
    printf("-> getIntegerIndex | %d first ->%d last ->%d middle ->%d\n", userInput, getIntegerIndex(userInput, 0), getIntegerIndex(userInput, 2), getIntegerIndex(userInput, 1));
    printf("-> getIntegerLength | %d ->%d\n", userInput, getIntegerLength(userInput));
    printf("-> mirrorInteger | %d ->%d\n", userInput, mirrorInteger(userInput));
    return 0;
}

int mirrorInteger(int positiveNumber){
    int buffer = 0;
    int length = getIntegerLength(positiveNumber);
    for(int i = 0; i < length; i++)
        buffer += shiftInteger(getIntegerIndex(positiveNumber, i), length - i - 1);
    return buffer;
}

int getIntegerLength(int number){
    int buffer = 1;
    do{
        number /= 10;
        if(number == 0)
            return buffer;
        buffer++;
    } while(1);
}

int getIntegerIndex(int number, int index){
    for(int i = 0; i < index; i++)
        number /= 10;
    return number % 10;
}

int shiftInteger(int number, int times){
    for(int i = 0; i < times; i++)
        number *= 10;
    return number;
}