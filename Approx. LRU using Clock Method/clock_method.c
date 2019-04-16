#include <stdio.h>
#include <stdlib.h>

FILE *file;

void secondChance(int frame, int pages[], int size){
	int frames[2][frame]; 
	/*defining a 2d array to store the page and bit*/ 
	int pointer = 0;
	int h, i, j;
	int x = 0, faults = 0, found = 0, load = 0;
	for (i=0;i<2;i++){
		for (j=0;j<frame;j++){
			frames[i][j] = 0;
		}
	}
	while(x < size){
		for (h=0;h<frame;h++){
			if(frames[0][h] == pages[x]){
				frames[1][h] = 1;
				found = 1;
			}
		}
		if (found == 0){
			do{
				if(frames[1][pointer] == 0){
					frames[0][pointer] = pages[x];
					frames[1][pointer] = 0;
					faults++;
					load = 1;
				}
				else{
					frames[1][pointer] = 0;
				}
				pointer++;
				if(pointer == frame){
					pointer = 0;
				}
			}

			while(load != 1);
		}

		found = 0;
		load = 0;
		x++;
	}
	printf("Number of Second Chance Page faults: %d\n", faults);
}

void main(){
	int fNum, pages[99], i=0;
	printf("Enter the number of frames: ");
	scanf("%d", &fNum);
	file = fopen("pages.txt", "r");
	while(fscanf(file, "%d", &pages[i]) != EOF){
		i++;
		if(i == 99)
			break;
	}
	fclose(file);
	secondChance(fNum, pages, i);
	exit(0);
}

