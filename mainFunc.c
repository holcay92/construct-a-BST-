#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Haldun Halil OLCAY   150120056


struct BST {
	int data;
	struct BST* left;
	struct BST* right;
};
typedef struct BST bst;

// linked list for reading and keeping the numbers from input file.....
struct LinkedList{
	int number;
	struct LinkedList* next;
};
typedef struct LinkedList ll;


// sorting the linkedlist...    
void sort(ll **head){
	
    ll *temp1 = *head;
    ll *temp2 = NULL;
	int tempValue;
	
	   while(temp1 != NULL) {     
	                
	        temp2 = temp1->next;  
			               
	        while(temp2 != NULL) {   
			              
	            if(temp1->number > temp2->number){  
	                tempValue = temp1->number;  
	                temp1->number = temp2->number;  
	                temp2->number = tempValue;  
	            }  
	        	temp2 = temp2->next;  
	        }  
	   	temp1 = temp1->next;  
	    }   
}
// A function to create pre order array to keep tracking the element number...
void preOrderBst(bst *orderTree,int arr[]) {
	
	static int index = 0;
	
		if (orderTree!=NULL){	
			if( (orderTree->data)>0){
				//	printf("%d ",orderTree->data);
					arr[index]=orderTree->data;
					index++;
			}		
			preOrderBst(orderTree->left,arr);						
			preOrderBst(orderTree->right,arr);
		}
}
// A function to find 'th' element of the depth level
int findThElement(int n,bst* countTree,int userInput,int preOrderArray[]){		
			int z;
			int element = 0;//In depth level th element
			
			for(z = 0 ; z < n ; z++){
				if(depthLevel(countTree , userInput) == depthLevel(countTree , preOrderArray[z])){
					element++;
				if(userInput == preOrderArray[z])
					break;
				}
			}
			return element;
}

void inOrderBst(bst *orderTree) {
	
		if (orderTree!=NULL){						
			inOrderBst(orderTree->left);
			if( (orderTree->data)>0){
				//	printf("%d ",orderTree->data);
			}						
			inOrderBst(orderTree->right);
		}
}
// A function to find the depth level of the element
int depthLevel(bst* tree, int value){
	
	 int distance = -1;
	 
    if (tree != NULL){
    	if ((tree->data == value) )
        	return distance + 1;
        		if(( distance = depthLevel(tree->left , value)) >= 0)
				return distance + 1;
        				if((distance = depthLevel(tree->right , value)) >= 0)
						return distance + 1;
	}
	else
        return -1;

    
}
// creating balanced binary search tree.....
bst* makeBalancedTree(int array[], int startPoint, int endPoint){
	
	while (startPoint <= endPoint){
		
		bst* tree = malloc(sizeof(bst));
		tree->data = array[(startPoint + endPoint)/2] ; 		 
	  	tree->left = makeBalancedTree(array, startPoint , (startPoint + endPoint) / 2 - 1);
	   	tree->right = makeBalancedTree(array, (startPoint + endPoint) / 2 + 1 , endPoint);
		return tree;
	}	
  return NULL;
}

void arrangeBst(bst *arrangeTree,int arr[] , int length){
	
	bst* temp = arrangeTree;
	bst* current = temp;
	bst* prev = NULL;
	bst* pprev = NULL;
	
	while(temp!=NULL){
		
		pprev=prev;
		prev=current;
		current=temp;
		temp=temp->right;
	}
	int i;
			for( i = 0 ; i < length ; i++){
				
				bst* newNode=malloc(sizeof(bst));
				
				newNode->data=arr[i];
			//	printf("array %d i: %d\n",i,arr[i]);
				newNode->left=NULL;
				newNode->right=NULL;
				current->right=newNode;
			//	printf("current %d: %d\n",i,current->data);
			//	printf("current right %d: %d\n",i,current->right->data);
			
			//rotation...
						if(current->left!=NULL){
							
							bst* current1=current;
							
								int tempCurrentData=current1->data;
								int tempCurrentRightData = current1->left->data;
								int tempCurrentLeftData= current1->right->data;
							
									current1->data=current1->left->data;
									current1->left=NULL;
									current1->right->data=tempCurrentData;
							
										bst* newNode1=malloc(sizeof(bst));
										newNode1->data=tempCurrentLeftData;
										current->right->right=newNode1;
						}
													
				current = newNode;
			}
	
}
// Main function
int main(){
	
		int n;	//number of keys the input file consists...		
		int i,j; //index variables for loops...
		
		ll* list = NULL;
		bst* tree = NULL;
		FILE *fp  = fopen("input.txt","r" );
			if( fp == NULL ){
				printf("file cant be opened\n");exit(0);
			}
						
// numbers are readed into linked list...

	int value;
	
	while (fscanf(fp, "%d", &value) == 1) {  
	
		ll *newNode = (ll*)malloc(sizeof(ll));
			newNode->number = value;										
				newNode->next = list;			
					list = newNode;	
						n++;
	}	
// test print linkedlist	
/*	ll* tempPrintTest = list;
	printf("Inputs: ");
	while(tempPrintTest!=NULL){
		printf("%d ",tempPrintTest->number);
		tempPrintTest=tempPrintTest->next;
	}*/

// controling the requirement of at least 16 keys entered..
	
	bool isLengthLongerThan16 = false;
	
	if(n < 16){
		
		isLengthLongerThan16 = true;
		
			printf("\nThe BST should have at least 16 nonnegative nodes\n");		
	}	
	
// controling negative values..

	ll* checkListNegative = list;
	bool anyNegativeNumber = false;
	
	while(checkListNegative != NULL){	
		
		if((checkListNegative->number) <= 0){	
		
			anyNegativeNumber = true;
			
			printf("Negative number (%d) is not allowed for this BST\n" , checkListNegative->number);	
		}
		checkListNegative = checkListNegative->next;
	}	
	
// controling if any key is replicated..
	
	ll* checkListReplicated = list;
	bool anyReplicatedNumber = false;
	
	while(checkListReplicated){
		
		ll* checkListReplicatedNext = checkListReplicated->next;
			
		while(checkListReplicatedNext){	
					
			if(checkListReplicated->number == checkListReplicatedNext->number){
				
				printf("The number %d is replicated! The numbers must be distinct..\n" , checkListReplicatedNext->number);
				
				anyReplicatedNumber = true;
			} 
			checkListReplicatedNext = checkListReplicatedNext->next;
		}		
		checkListReplicated = checkListReplicated->next;
	}
	
// if primary requirements are not satisfied by the input file, program is terminated..	

	if(anyNegativeNumber || isLengthLongerThan16 || anyReplicatedNumber) {
		
		printf("\nProgram terminated..");
		
		exit(0);
	}	
	
// sorting input values in linkedList...	
	sort( &list );
	
// reading input numbers from linkedList to array
	ll* arrList = list;
	
	int arrayOfNumbers[n]; 
	
	for( i = 0 ; i < n ; i ++){
		arrayOfNumbers[i] = arrList->number;
			arrList = arrList->next;
	}
// test print array[]	
/*	printf("\nSorted Array: ");
	for(i = 0 ; i < n ; i++){
		printf("%d ", arrayOfNumbers[i]);
	}printf("\n");*/
	
// calculations.......		
	int bestCaseDepthLevel = floor((log(n) / log(2))) + 1;
	int _3log4NDepthLevel = 3 * floor( (log( n ) / log( 4 )) );
	int extraDepthLevels = _3log4NDepthLevel - bestCaseDepthLevel;
	int bestCaseDepthLevelExceptNodesForRequiredDepthLevels = floor((log( n - extraDepthLevels ) / log(2))) + 1;
	int requiredDepthLevels = _3log4NDepthLevel - bestCaseDepthLevelExceptNodesForRequiredDepthLevels ;
	int arrayOfDepthLevels[_3log4NDepthLevel];
	int numberOfNodesAtFullDepthLevels = pow( 2 , ( floor( (log(n)/log(2))) ) ) - 1 ;
	int numberOfFullDepthLevels = log( n ) / log( 2 );
	
//test	
	int arrangeBstArray[requiredDepthLevels];
	
	for(i = n-requiredDepthLevels,j=0 ; i < n,j<requiredDepthLevels ; i++,j++){
		arrangeBstArray[j]=arrayOfNumbers[i];
	//	printf("\n%d \n",arrangeBstArray[j]);
	}
	
	int newArrayOfNumbers[n-requiredDepthLevels];
	
	for(i=0;i<n-requiredDepthLevels;i++){
		newArrayOfNumbers[i]=arrayOfNumbers[i];
	}

	
	int numberOfLeafNodes = n - numberOfNodesAtFullDepthLevels ;	
	int nodesAtDeepestDepthLevel = n - pow(2,(floor(log(n)/log(2))))+1;
	int nodesAtDeepest = n - pow( 2 , (floor(( log( n ) / log( 2 )))) ) + 1 - 3 * floor((log( n )/log( 4 ))) + floor((log( n ) / log( 2 ))) + 1 ;
	
/*	printf("\n\nNumber Of Nodes: %d\n",n);
	printf("Best Case Depth Level((log 2 n) +1): %d\n",bestCaseDepthLevel);
	printf("Depth Levels Which (3 log 4 n) rule requires: %d \n" , _3log4NDepthLevel);
	printf("!BestCaseDepthLevelExceptNodesForRequiredDepthLevels: %d\n",bestCaseDepthLevelExceptNodesForRequiredDepthLevels);
	printf("Required Depth Levels: %d\n" , extraDepthLevels);
	printf("Number OF Full Depth Levels: %d\n" , numberOfFullDepthLevels);	
	printf("Number Of Nodes At Full Depth Levels: %d\n" , numberOfNodesAtFullDepthLevels);
	printf("Number Of Leaf Nodes: %d\n" , numberOfLeafNodes);
	printf("nodesAtDeepestDepthLevel: %d\n",nodesAtDeepestDepthLevel);*/
//  printf("Nodes At The Depth Level After The Deepest Full Depth Level: %d\n" , nodesAtDeepest);

		int arrayOfNumbersInFullDepthLevels[numberOfNodesAtFullDepthLevels];
		int arrayOfNumbersInLeafDepthLevels[n - numberOfNodesAtFullDepthLevels];
		
// Array of nodes at full depth levels which we directly insert to binary search tree to fill the depth levels which should be full..	
				
		for(i = 0 ; i < numberOfNodesAtFullDepthLevels ; i++){
			arrayOfNumbersInFullDepthLevels[i] = arrayOfNumbers[i];
		}
	/*	printf("arrayOfNumbersInFullDepthLevels: ");//test print
			for(i = 0 ; i < numberOfNodesAtFullDepthLevels ; i++){
				printf("%d ",arrayOfNumbersInFullDepthLevels[i]);
			
			}printf("\n");*/
			
// Array of nodes at bottom depth levels which we afterwards manipulate to maintain the rule of 3 log 4 n depth	levels...	
	
		for(i = 0 ; i <(n - numberOfNodesAtFullDepthLevels) ; i ++){
			arrayOfNumbersInLeafDepthLevels[i] = arrayOfNumbers[i+numberOfNodesAtFullDepthLevels];
		}
		/*	printf("arrayOfNumbersInLeafDepthLevels: ");//test print
		for(i = 0 ; i < (n - numberOfNodesAtFullDepthLevels) ; i++){
			printf("%d ",arrayOfNumbersInLeafDepthLevels[i]);
		}
		printf("\n\n");	*/	
			
//	constructing a balanced binary search tree....
		tree =	makeBalancedTree( newArrayOfNumbers , 0 , n - 1 - requiredDepthLevels );
		bst* preTree = tree;
		
		
//this is where balanced tree turns into 3log4n depth level tree.....	
	arrangeBst(tree,arrangeBstArray,requiredDepthLevels);


//	test print of binary search tree...
/*	printf("\ntestArray :");
	for(i=0;i<n-extraDepthLevels;i++){
		printf("%d ",newArrayOfNumbers[i]);
	}*/
/*	printf("\n\nextra array arrange:");
	for(i=0;i<requiredDepthLevels;i++){
			printf("%d ",arrangeBstArray[i]);
	}*/

		bst* countTree = tree;
		int preOrderArray[n];//pre order binary search tree to find which element of the depth level
		
	//	printf("\n\nPre order tree:");
	
		preOrderBst(tree,preOrderArray);
	//	printf("\n\nIn order tree:");
	//	inOrderBst(tree);	
			
	
//output information for user...
		int howManyElementInADepthLevel[_3log4NDepthLevel];
		
		printf("\n\nDepth level of BST is %d\n\n",_3log4NDepthLevel);
		
		for(i=0;i<_3log4NDepthLevel;i++){
		
			int countDepth=0;
			
			for(j=0;j<n;j++){
				
				if(i==depthLevel(countTree,preOrderArray[j]))
				countDepth++;
			}
			howManyElementInADepthLevel[i]=countDepth;
				printf("Depth level %d -> %d\n\n",i,howManyElementInADepthLevel[i]);
		}
				
//user interface....
		
		int userInput;
				
		while(1){
			
			printf("\nKey value to be searched (Enter 0 to exit) : ");
			scanf("%d" , &userInput);
			
			int result = depthLevel(tree,userInput);
			int thElement= findThElement( n, countTree , userInput , preOrderArray);
						
			if(userInput==0){
				printf("Exit\n");
				exit(0);
			}
			if(thElement==1 && result>=0) //1st
           		printf("At Depth level %d, %dst element\n",result , thElement);
           		 
       		else if (thElement<=2 && result>=0) //2nd
          		printf("At Depth level %d, %dnd element\n",result , thElement);
          		
        	else if (thElement<=3 && result>=0) //3rd
            	printf("At Depth level %d, %drd element\n",result , thElement);
            	
        	else if (thElement>=0 && result>=0) //else print th all
            	printf("At Depth level %d, %dth element\n",result , thElement);
            	
			else printf("%d is not found in BST\n", userInput);			
		}
			
//close file...	
	fclose(fp);
}	
