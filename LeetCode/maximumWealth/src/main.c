#include <stdio.h>

int maximumWealth(int** accounts, int accountsSize, int* accountsColSize) {
    int response = 0;

    for(int i = 0; i < accountsSize; i++){
        int _wealth = 0;
        for(int j = 0; j < *accountsColSize; j++)
            _wealth += accounts[i][j];
        if(_wealth > response)
            response = _wealth;
    }

    return response;
}


int main(int argc, char const *argv[])
{
    printf("Hello World!\n");

    return 0;
}
