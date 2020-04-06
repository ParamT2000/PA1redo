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
static megaNode * divide(megaNode * mega, int, bool);
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

        megaNode * megaHead = malloc(sizeof(megaNode));
        megaHead -> nextNode = list;
        megaHead -> nextMega = megaNode; // creates a circular list
        
        Node * head = NULL;
        
        while(k > 1){
            k = (k -1) / 3;


        }
        
        head = megaHead -> nextNode;
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

static megaNode * divide(megaNode * mega1, int gap, bool dir){
    //dir = 1 means to sort ascendingly and dir = 0 means to sort descendingly

    // printf("\nOriginal List:");
    // printList(mega1 ->nextNode);
    
    
    // creates all the megaNodes and assigns the proper lists to them
    megaNode * oldMega = mega1; // used to be the head but isn't anymore

    megaNode * newMegaHead = malloc(sizeof(megaNode));
    newMegaHead ->nextMega = NULL;
    megaNode * newTempMega = newMegaHead;

    Node * tempNode = NULL;

    int counter = 0;
    for(counter = 0, counter < gap; counter++){ //creates new megas for new gap
        newTempMega -> nextMega = malloc(sizeof(megaNode));
        newTempMega = newTempMega ->nextMega; //update temp 
        newTempMega -> nextMega = NULL;

        tempNode = pop(&(oldMega -> nextNode));
        oldMega = oldMega ->nextMega; //updates location of oldmega
        if(tempNode == NULL){// breaks out of loop. indicates that all values have been added
            break; //this statement should never run because k should always be less than n
        }
        tempNode -> next = NULL;
        newTempMega -> nextNode = tempNode;
    }

    newTempMega -> nextMega = newMegaHead; //creates the circular linked list

    // at this point all the new megaNode should have atleast a value.
    tempNode = pop(&(oldMega -> nextNode));

    newTempMega = newTempMega -> nextMega; // should be equal to newMegaHead

    //start loading the remaining nodes into the new one
    if(dir){//ascending

        while((tempNode != NULL)){//keep adding until you are out of nodes

            newTempMega -> nextNode = pushA(newTempMega ->nextNode, tempNode);
            oldMega = oldMega -> next;

            tempNode = pop(&(oldMega -> nextNode));

            if(tempNode == NULL){
                break;
            }
            tempNode -> next = NULL;  // updates the tempNode for the next run  
            newTempMega = newTempMega -> nextMega;
        }
    }
    else{ //descending

        while((tempNode != NULL)){//keep adding until you are out of nodes

            newTempMega -> nextNode = pushD(newTempMega ->nextNode, tempNode);
            oldMega = oldMega -> next;

            tempNode = pop(&(oldMega -> nextNode));
            
            if(tempNode == NULL){
                break;
            }
            tempNode -> next = NULL;  // updates the tempNode for the next run  
            newTempMega = newTempMega -> nextMega;
        }
    }

    freeMega(oldMega);
    return newMegaHead;

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
* NAME: freeMega
* PARAMETERS: megaNode *
* RETURN: void
* DESCRIPTION: takes in any meganode assuming it is circularly linke
* saves the next value and as long as it isnt equal to itself
*proceeds with a normal freeing algorithm   
*
************************************************************/
static void freeMega(megaNode * curMega){
    if(curMega == NULL){
        return;
    }

    megaNode * tempMega = curMega -> nextMega;
    if(tempMega == curMega){
        free(curMega);
    }
    else{
        megaNode * temp2 = NULL;
        while((tempMega != curMega) &&){ //frees everything up till curNode
            temp2 = tempMega;
            tempMega = tempMega -> nextMega;
            free(temp2);
        }
        free(curNode);
    }
    return;
}

/***********************************************************
* NAME: Template
* PARAMETERS: 
* RETURN: 
* DESCRIPTION:   
*
************************************************************/