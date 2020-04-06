/*
Param Talwalkar
ECE 368
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char * * argv){
	if (argc < 4){
		printf("exit");
		return EXIT_FAILURE;
		}
	int size = 0; //size of file
	long comps = 0;
	long * data = NULL;
	Node * data2 = NULL;
	int sorted = 0;

	if(strcmp(argv[1], "-a") == 0){
		
		
		data = Array_Load_From_File(argv[2], &size);
		Array_Shellsort(data, size, &comps);
		sorted = Array_Save_To_File(argv[3], data, size);
		free(data);
	}	

	else if(strcmp(argv[1],"-l") == 0){

		data2 = List_Load_From_File(argv[2]);
		
		data2 = List_Shellsort(data2, &comps); //should now be sorted

		size = List_Save_To_File(argv[3], data2);

		printf("\nn_comp %ld", comps);
		printf("\nsize saved %d\n",size);
		//free the list
		Node * temp = NULL;
		
		while(data2 != NULL){
			temp = data2 -> next;
			free(data2);
			data2 = temp;
		}
	}

	if(sorted == size){
		printf("\nsorted:%d", sorted);
		printf("\nSame amount outputted\n");
	}

	
	return EXIT_SUCCESS;
}

