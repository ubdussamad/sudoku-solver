#include<stdio.h>
#include <string.h>


struct node {
	// The first ellemnt will be of 40 bytes , and the other two are 4 and 4 repectively.
	 //In this case the number of elements provided are the maximum that'll be required for our sudoku job
	int top; // You can always use malloc or some neat pointer trick to make this array happen with mutable list size
	int max;
	int array[5];
};

int push();
int find();
void int_memcpy();
int pop();


/*int main(void){
	struct node stack;
	stack.top = 0;
	stack.max = 5;

	while (1){
		printf("\nEnter (P)ush  , (D)elete , (T)raverse:");
		char will;
		scanf("%c",&will);

		if (will=='p'){
			int num;
			printf("\nEnter the number to be pushed on to the stack:");
			scanf("%d",&num);
			push(&stack,num);
		}

		else if (will == 'd'){
			pop(&stack);
		}

		else if (will == 't'){
			printf("\n[");
			for (int i = 0; i < stack.top; ++i)
			{
				printf("%d,", stack.array[i]);
			}
			printf("]\n");
		}

	}

	return(0);
}*/

int push(int * initial_struct_node_ptr,int value){

	if ((find(initial_struct_node_ptr,0)) >= find(initial_struct_node_ptr,4)){
		printf("OverPheloww!\n");
		return(-1);
	}

	int_memcpy(initial_struct_node_ptr , value , sizeof(int) , (8+(find (initial_struct_node_ptr , 0)*4)) );
	int_memcpy(initial_struct_node_ptr , find (initial_struct_node_ptr , 0) + 1 , sizeof(int) , 0);

	return(0);
}

int pop(int * initial_struct_node_ptr){
	if (!find(initial_struct_node_ptr ,0)){
		printf("UnderFlow\n");
		return(-1);
	}
	int_memcpy(initial_struct_node_ptr , find (initial_struct_node_ptr , 0) - 1 , sizeof(int) , 0);
	return(find(initial_struct_node_ptr , (8 + (find(initial_struct_node_ptr , 0))*4 )));
}

int find(int * addr,int bytes_to_skip){
	return (*((int *)((long unsigned int)addr + bytes_to_skip)));
}

void int_memcpy(int * reciever,int value,size_t bytes_to_copy,int bytes_to_skip){
	//Copies bytes from value to receiver
	memcpy( (int *)((long unsigned int)reciever+bytes_to_skip),&value,bytes_to_copy);
}