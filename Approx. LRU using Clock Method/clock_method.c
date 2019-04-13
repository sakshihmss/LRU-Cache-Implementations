#include <stdio.h>
#include <stdlib.h>

void secondChance(int frame, int pages[], int size);
void clockPRA(int n, int page[], int size);
void optPRA(int n, int page[], int size);

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
	printf("Number of Second Chance faults: %d\n", faults);
}

void clockPRA(int n, int page[], int size){
	int frames[n], use[n], found;
	for (int i=0;i<n;i++){
		frames[i] = 0;
		use[i] = 0;
	}

	int fault = 0, locate = 0;
	for (int i=0;i<size;i++){
		found = 0;
		for (int j=0;j<n;j++){
			if(page[i] == frames[j]){
				found = 1;
				use[j] = 1;
			}
		}
		if(found == 0){
			do{
				if(use[locate] == 0){
					frames[locate] = page[i];
					use[locate] = 1;
					found = 1;
					fault++;
				}
				else{
					use[locate] = 0;
				}
				locate++;
				if(locate == n)
					locate = 0;
			}
			while(found != 1);
		}
	}
	printf("Number of Clock faults: %d\n", fault);
}

void optPRA(int n, int page[], int size){
	int frames[n], fault = 0, found, replace, empty = n, z = 0, i, j, x;
	for (i=0;i<n;i++){
		frames[i] = 0;
	}
	for(i=0;i<size;i++){
		found = 0;
		replace = 0;
		for (j=0;j<n;j++){
			if(page[i] == frames[j]){
				found = 1;
			}
		}
		if(found == 0){
			if(empty != 0){
				frames[z] = page[i];
				z++;
				fault++;
				empty--;
			}
			else{
				for(j=0;j<n;j++){
					for(x=i;x<size;x++){
						if(frames[j] == page[x]){
							if(x > replace){
								replace = j;
							}
							break;
						}
						if(x == size-1)
							replace = j;
					}
				}
				frames[replace] = page[i];
				fault++;
			}
		}
	}
	printf("Number of Optimal faults: %d\n", fault);
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
	clockPRA(fNum, pages, i);
	optPRA(fNum, pages, i);
	exit(0);
}

