#include <stdio.h>
#include <stdlib.h>
#include "shell_array.h"

static int computeK(int size);

long *Array_Load_From_File(char *filename, int *size){

	FILE * dataFile = fopen(filename, "rb");
	long * retAdd = NULL;
	

	if(dataFile == NULL){
		fclose(dataFile);
		return retAdd;
	}

	fseek(dataFile, 0, SEEK_END);
	unsigned long numBytes = (unsigned long)ftell(dataFile);
	fseek(dataFile, 0, SEEK_SET);
	*size = numBytes / (sizeof(long));
		
	retAdd = malloc(*size * sizeof(long));
	
	fread(retAdd, sizeof(long), *size, dataFile);
	
	fclose(dataFile);
	//why all zeros	
	
	return retAdd;

}

int Array_Save_To_File(char *filename, long *array, int size){
	
	FILE * output = fopen(filename, "w");
	int val = fwrite(array, sizeof(long), size, output);
	fclose(output);
	return val;
}


void Array_Shellsort(long *array, int size, long *n_comp){
	int k = 0;
	if (array == NULL || size == 0){
		printf("Entered null");
		//? whats the condition		
	}
	else{
		int i = 0; //counter
		int j = 0; //counter 2
		printf("Size = %d", size);
		k = computeK(size);
		printf("\nk received= %d", k);
		long temp; //temporary swapping variable
		//shell sort algorithm	

		while(k > 1){
			k = (k - 1) / 3;
			printf("\nusing k: %d", k);
			//printf("\n in loop");
			
			for(i = k; i < size; i++){
				
				(*n_comp)++;
				j = i;
				while((j >= k) && (array[j] < array[j - k])){
					//printf("\nnow swapping: %ld <? %ld", array[j],array[j-k]);
					temp = array[j - k];
					array[j - k] = array[j];
					array[j] = temp;
					j -= k;
				}
			}  
			
		}

	}
}
#if 1
static int computeK(int size){
	int k = 1;
	//printf("\nsize rec in computeK = %d",size);
	while (k < size) {
		k = (k * 3) + 1;
		//printf("\n%d", k); 
				
	}
	//printf("\nk returning = %d",k);
	return k; 
}
#endif



