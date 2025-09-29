#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize) {
    int *response = malloc(numsSize * sizeof(int));
    response[0] = nums[0];

    for(int i = 1; i < numsSize; i++){
        response[i] = response[i - 1] + nums[i];
    }

    *returnSize = numsSize;

    return response;
}

int main(int argc, char const *argv[])
{
    printf("Hello World!\n");

    return 0;
}
