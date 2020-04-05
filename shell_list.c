#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include <stdbool.h>
#include <limits.h> //remove before submission

//header stuff:
typedef struct meg {
    Node *nextNode;
    struct meg *nextMega;
} megaNode;

//function to print linked list as non binary
static void printList(Node *);
static megaNode * divide(megaNode * mega, int kInitial, int kFinal, bool);
static int getLen(Node * curNode);
static Node * pushA(Node* head, Node* ins,long *n_comps);
static Node * pushD(Node* head, Node* ins,long *n_comps);
static Node* pop(Node** head);
static int computeK(int size){




Node * List_Load_From_File(char *filename){
    FILE * dataFile = fopen(filename, "rb");
	
	

	if(dataFile == NULL){
		fclose(dataFile);
		return NULL;
	}

    fseek(dataFile, 0, SEEK_END);
	unsigned long numBytes = (unsigned long)ftell(dataFile);
	fseek(dataFile, 0, SEEK_SET);
	int size = numBytes / (sizeof(long));
    
    if(size == 0){
        return NULL;
    }

    Node * head = malloc(sizeof(Node));
    fread(&(head->value),sizeof(long),1,dataFile);
    head -> next = NULL;
    
    
    int count = 0; //counter
    Node* temp = head;

    for(count = 1; count < size; count++){
        temp -> next = malloc(sizeof(Node));
        temp = temp -> next;
        fread(&(temp -> value),sizeof(long),1,dataFile);
        temp ->next = NULL;
    }

   
    fclose(dataFile);


    //printList(head); //for testing purposes

    return head;
}
/*
int List_Save_To_File(char *filename, Node *list){
    outFile = fopen(filename,'wb');
    //fwrite(list,)
}
*/

/***********************************************************
* NAME: List_shellsort
* PARAMETERS: 
* RETURN: 
* DESCRIPTION:   
*
************************************************************/

#if 1
Node * List_Shellsort(Node *list, long *n_comp) {
    if(list == NULL){
        return NULL;
    }
    else{

        int size = getLen(list);//placeholder
        int k = computeK(size);
        Node * head = NULL;
        divide
        while(k > 1){
            k = (k -1) / 3;


        }
        
        return head;
    }
    
}
#endif
/***********************************************************
* NAME: printList
* PARAMETERS: Node * 
* RETURN: void
* DESCRIPTION:   prints out the list
*
************************************************************/
static void printList(Node* temp){
    printf("\n values in the list:");

    while(temp != NULL){
        printf("\n%ld",temp->value );
        temp = temp ->next;
    }
}

/***********************************************************
* NAME: divide
* PARAMETERS: megaNode *, int kInit, next kFinal, bool direction
* RETURN: Node * 
* DESCRIPTION: takes in the megaNode containing the data. Transforms it into 
* the new k format. should sort it as it adds the nodes
*
*
************************************************************/

static megaNode * divide(megaNode * mega1, int kInitial, int kFinal, bool dir){
    printf("\nOriginal List:");
    printList(meag1 ->nextNode);
    
    // first case where the Ki is smaller than the Kf
    // creates all the megaNodes and assigns the proper lists to them
    if(kInitial > kFinal){
        
    }
    else{ //kInitial is smaller than kFinal
        int needMegas = kFinal - kInitial; // how many more megaNodes needed to split
        int counter = 0;

        megaNode * tempMega = mega1;
        Node * tHeadNode = mega1 -> nextNode;
        Node * tempNode = NULL;

        for(counter = 0, counter < needMegas;counter++){
            tempMega -> nextMega = malloc(sizeof(megaNode));
            tempMega = tempMega ->nextMega;
            tempMega -> nextMega = NULL;

            tempNode = pop(&tHeadNode);

            tempNode -> next = NULL;
            tempMega -> nextNode = tempNode;
        }

        tempNode = pop(&tHeadNode);
       
        tempMega = mega1;

        // first will be ascending
        while(tempNode != NULL){
            tempMega -> nextNode = pushA(tempMega ->nextNode, tempNode);
            tempNode = pop(&tHeadNode);
            if(tempNode == NULL){
                break;
            }
            tempNode -> next = NULL;  // updates the tempNode for the next run  
        }

    }

}

/***********************************************************
* NAME: getLen
* PARAMETERS: Node * 
* RETURN: int length
* DESCRIPTION:  gets the length of a linke list 
*
*
************************************************************/
static int getLen(Node * curNode){
    int length = 0;
    while(curNode != NULL){
        curNode = curNode -> next;
        length++;
    }

    return length;
}

/***********************************************************
* NAME: pushA
* PARAMETERS: node * head, node * ins
* RETURN: node* head
* DESCRIPTION:  pushes to the stack in ascending (enqueue)
*
************************************************************/
static Node * pushA(Node* head, Node* ins,long *n_comps){

    Node * temp = head;

    //edge case where the node to be inserted should be the new head
    (*n_comps)++;
    if(head -> value >= ins -> value){
        ins -> next = head;
        return ins;
    }

    while((temp -> next != NULL) && ((temp -> next -> value) < (ins -> value))){
        //printf("\nMoving past %ld to insert %ld", temp -> value, ins -> value);
        temp = temp -> next;
        (*n_comps)++;
        
    }
    ins -> next = temp -> next;
    temp -> next = ins;

    return head;

}

/***********************************************************
* NAME: pushD
* PARAMETERS: node * head, node * ins
* RETURN: node * head
* DESCRIPTION:   pushes to the stack in descending (enqueue)
*
************************************************************/
static Node * pushD(Node * head, Node* ins,long *n_comps){
    Node * temp = head;

    //edge case where the node to be inserted should be the new head
    (*n_comps)++;
    if(head -> value <= ins -> value){
        ins -> next = head;
        return ins;
    }

    while((temp -> next != NULL )&& (temp -> next ->value > ins -> value)){
        temp = temp -> next;
        (*n_comps)++;
    }

    ins -> next = temp -> next;
    temp -> next = ins;
    return head;

}

/***********************************************************
* NAME: pop
* PARAMETERS: node ** head
* RETURN: node * popped node
* DESCRIPTION: removes the head node and returns the removed  
*
************************************************************/
static Node* pop(Node** head){
    Node * temp = *head;
    
    if((*head) != NULL){
        *head = (*head) ->next;
        temp ->next = NULL;
    }

    return temp;
}

/***********************************************************
* NAME: computeK
* PARAMETERS: int size
* RETURN: k
* DESCRIPTION: computes k given the formula for a certain size  
*
************************************************************/
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

/***********************************************************
* NAME: Template
* PARAMETERS: 
* RETURN: 
* DESCRIPTION:   
*
************************************************************/