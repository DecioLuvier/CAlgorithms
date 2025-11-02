#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n) {
	int flowersPlaced = 0;
	for(int i = 0; i < flowerbedSize; i++){
		if(flowerbed[i] == 0){	//If plot are not planted.
			int	previous = i - 1;	
			if(previous >= 0 && flowerbed[previous] == 1)	//If there's a left adjacent flowerbed.
				continue;	//ignore		
			int next = i + 1;							
			if(next < flowerbedSize && flowerbed[next] == 1)	//If there's a right adjacent flowerbed.
				continue;	//Ignore

			flowerbed[i] = 1;	//Place a flower.
			flowersPlaced++;
		}
	}
	if(flowersPlaced >= n)
		return true;
	return false;
}

//Test case

int main(){
	int flowerbed[6] = {1,0,0,0,0,1};

	printf("%d\n\n\n", canPlaceFlowers(flowerbed, 6, 2));

	for(int i = 0; i < 6; i++){
		printf("%d \n", flowerbed[i]);
	}

	return 0;
}