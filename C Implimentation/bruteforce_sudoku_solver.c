#include<stdio.h>
#include<stdlib.h>
#include <string.h>

/* ---------------------------------------------
* 9x9 Sudoku Solver in C
* 07SEP2018
* Author: Mohammed S. Haque <ubdussamad@gmail.com>
* Primarily Built for GCC Compiler but it should
* work on most other compilers too.

* All arrays end at element having value -1
* The compiler must have integer size of 4 bytes
* ... or the code will break into pieces.
* You can solve this simply by replacing (Ctrl/Cmd + H) 
* ... 4 with the integer size in your machine.
*///---------------------------------------------

struct node {
	// The first element will be of 40 bytes , and the other two are 4 and 4 respectively.
	 //In this case the number of elements provided are the maximum that'll be required for our sudoku job
	int top; // You can always use malloc or some neat pointer trick to make this node with mutable list size
	int max;
	int array[10];};
int push();
int find();
void int_memcpy();
int pop();
void file_handler();
int chr_to_int();
void print_sudoku_ref();
int count_empty_indices();
int get_empty_indices();
int set_index();
void print_list();
void get_arms();
struct indices {
	int r;
	int c; };
struct indices next();
struct indices previous();
struct indices current();
void get_grid_members();
void int_memcpy();
void get_options();
void parse_to_stack();
int solve();
int step_counter = 0;

int main(int argc, char **argv) {
	int dim = 9;
    int sudoku[dim][dim]; //Initialize a 9x9 array
    file_handler(&sudoku,dim,argv);
    //sprint_sudoku_ref(&sudoku,dim,8,0);

    int empty_indices = count_empty_indices(&sudoku,8);
    
    struct indices pos [empty_indices];
    
    get_empty_indices(&sudoku,&pos);

    int current_index = -1;

    //printf("The ptr to sudoku outside is:%x\n",&sudoku[0][0]);
    //printf("The number of empty indices are:%d\n", empty_indices);
    printf("\nHi your sudoku dimention is: 9x9 and Complexity is:%f\n",(float)((float)empty_indices/(float)81));
    int z = solve(&sudoku , &current_index , empty_indices , &pos );

    if (z==-1){
    	printf("Could Not Solve you grid, please check for errors in your grid.\n");
    }
    else {
    	printf("It took %d steps to complete your task.\n",step_counter);
    }
	print_sudoku_ref(&sudoku,dim,8,0); 

	//printf("\n");   

	return(0);
}


int solve( int * sudoku_ptr[9][9] , int * current_index  , int empty_indices , struct indices ** pos){
	//Code

	//Checking for termination state
	step_counter++;
	struct indices coord = next(current_index , pos , empty_indices);

	if (coord.r == -1){
		return(0);
	}

	// Done.

	// Getting Options
	int options[10];
	//printf("Good before this.\n");
	get_options( coord , sudoku_ptr , &options);

	printf("Current Position is: [%d,%d] and current options are: ",coord.r,coord.c);
	print_list(options,9);

	struct node stack;
	stack.top = 0;
	stack.max = 10;

	parse_to_stack(options,&stack);

	//Done Getting Options and options are stored in stack

	//Rolling back if there are no options.
	
	if ( stack.top == 0 ){
		printf("Rolling Back!. No choice is there.\n");

		set_index ( previous( current_index , pos , empty_indices ) , current_index , pos , 8 );
		
		return(-1);
	}

	//Done Rolling back stuff

	while (1){

	printf("Top was: %d\n",stack.top);


	if ( stack.top == 0 ){
		
		printf("Rolling back! No Choices Left.\n");
		int_memcpy(sudoku_ptr,0,4, ((coord.r*36)+(coord.c*4)) );
		set_index ( previous( current_index , pos , empty_indices ) , current_index , pos , 8 );
		return(-1);
	}

	int ch = pop(&stack);

	printf("We chose:%d\n",ch);
	
	//printf("The ptr to sudoku inside is:%x\n",sudoku_ptr);

	int_memcpy(sudoku_ptr,ch,4, ((coord.r*36)+(coord.c*4)) );
	
	//*sudoku_ptr[coord.r][coord.c] = ch;

	//printf("We assigned the value at that index!\n");

	int call = solve(sudoku_ptr , current_index , empty_indices , pos);

	if (call == 0){
		return(0);
	}

	else if (call == -1) {
		continue;
	}

	else {
		printf("Error Occurred!\n");
	}
}

}


void parse_to_stack(int list[] , struct node * struct_ptr){
	int counter;
	for (int i = 0; i < 10; i++)
	{
		if (list[i] == -1){
			counter= i;
			break;
		}

	}

	int_memcpy(struct_ptr , counter , 4 , 4); //Modifying the max value of struct to the length of the list.

	for (int i = 0; i < counter; i++)
	{
		//printf("Val:%d\n",list[i]);
		//int_memcpy( struct_ptr , list[i] , 4 , (8+(i*4)) );
		push(struct_ptr , list[i]);
	}
}
void get_options(struct indices pos,int sudoku[9][9],int * list_ptr){
	long unsigned int dref_ptr = (long unsigned int) list_ptr;
	//printf("\nAt Position: %d:%d\n",pos.r,pos.c);
	int grid[8];
	int arms[17];
	get_grid_members(pos,sudoku,&grid[0]);
	get_arms(pos,sudoku,&arms[0]);
	//Plug and chug all the values.
	int parent_list[9] = {1,2,3,4,5,6,7,8,9};
	
	for (int i = 0; i < 9; i++)
	{
		int used = 0;
		for (int j = 0; j < 10; j++){
			if (grid[j] == -1) {break;}
			if (parent_list[i] == grid[j]){
				used =1;
			}}
		for (int j = 0; j < 17; j++){
			if (arms[j] == -1) {break;}
			if (parent_list[i] == arms[j]){
				used =1;
			}}

		if (!used){
			memcpy((int *)dref_ptr , &parent_list[i] , 4);
			dref_ptr += 4;
			//printf("Option: %d\n",parent_list[i]);
		}
	}
	int_memcpy((int *) dref_ptr , -1 , 4 , 0);
}
void get_grid_members(struct indices pos,int sudoku[9][9],int * list_ptr){
	long unsigned int  dref_ptr = (long unsigned int) list_ptr;

	void get_range(int coord,int * ptr){
		
		long unsigned int sub_dref_ptr  = (long unsigned int) ptr;
		
		if (coord >= 0 && coord <= 2) {
			int_memcpy((int *)sub_dref_ptr,0,4,0);
			sub_dref_ptr += 4;
			int_memcpy((int *)sub_dref_ptr,2,4,0);
		}
		else if (coord >= 3 && coord <= 5) {
			int_memcpy((int *)sub_dref_ptr,3,4,0);
			sub_dref_ptr += 4;
			int_memcpy((int *)sub_dref_ptr,5,4,0);
		}
		else if (coord >= 6 && coord <= 8) {
			int_memcpy((int *)sub_dref_ptr,6,4,0);
			sub_dref_ptr += 4;
			int_memcpy((int *)sub_dref_ptr,8,4,0);
		}
		else{
			printf("Locha 404! Bad Coordinates.\n");
		}
	}
	int rrange[2],crange[2];
	get_range(pos.r,&rrange[0]);
	get_range(pos.c,&crange[0]);
	for (int i = rrange[0]; i < (rrange[1]+1); i++) {
			for (int j = crange[0]; j < (crange[1]+1); j++) {
				if (sudoku[i][j]) {
					memcpy((int *) dref_ptr,&sudoku[i][j],4);
					dref_ptr += 4;
				}
			}
		}
	int_memcpy((int *) dref_ptr,-1,4,0);	
}
void get_arms(struct indices pos,int sudoku[9][9],int * list_ptr){
	long unsigned int  dref_ptr = (long unsigned int) list_ptr;
	for (int i = 0; i < 9; i++)
	{
		if ((sudoku[i][pos.c])){
			int * ref_ptr = (int *) dref_ptr;
			memcpy(ref_ptr,&sudoku[i][pos.c],4);
			dref_ptr += 4; 
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if ((sudoku[pos.r][i])){
			int * ref_ptr = (int *) dref_ptr;
			memcpy(ref_ptr,&sudoku[pos.r][i],4);
			dref_ptr += 4; 
		}
	}
	int * ref_ptr = (int *) dref_ptr;
	int tmp = -1;
	memcpy(ref_ptr,&tmp,4);
}
struct indices current(int current_index,struct indices indices_list[]){
	//Doing nothing just flappin in the breeze!
	return(indices_list[current_index]);
}
struct indices previous(int *current_index,struct indices list[],int max){
	if (*current_index >= 1) {
		
		*current_index -=1;
		return(list[*current_index]);	
	}
	struct indices err;
    err.r = -1;
    err.c = -1;
	return(err);
}
struct indices next(int *current_index,struct indices list[],int max){
	if (*current_index < (max-1)) {
		
		*current_index +=1;
		return(list[*current_index]);	
	}
	struct indices err;
    err.r = -1;
    err.c = -1;
	return(err);
}
int set_index(struct indices pos, int * current_index , struct indices list[] ,int dim){
	for (int i = 0; i < dim; i++)
	{
		if (list[i].r == pos.r && list[i].c == pos.c) {
			memcpy(current_index,&i,4);
			return(0);
		}
	}
	return(-1);
}
int get_empty_indices(int * sudoku_ptr , int * struct_ptr){
	
	long unsigned int dref_ptr = (long unsigned int) sudoku_ptr;
	long unsigned int int_unref_ptr = (long unsigned int) struct_ptr;

	void modify (long unsigned int unref_ptr,int bytes_to_push,int data){
					int * ref_ptr = (int *) unref_ptr;
					memcpy(ref_ptr,&data,bytes_to_push);
				}
	for (int i=0;i<9;i++){

		for (int j=0;j<9;j++){
			int * ref_ptr = (int *)dref_ptr;
			int value = (int)*ref_ptr;
			if (!value) {
				/* Pointer Magic Happens */
				modify(int_unref_ptr,4,i);
				int_unref_ptr += 4;
				modify(int_unref_ptr,4,j);
				int_unref_ptr += 4;
			}
			dref_ptr += 4;
		}
	}
	int end=-1;
	modify(int_unref_ptr,4,end);
	int_unref_ptr += 4;
	modify(int_unref_ptr,4,end);
	int_unref_ptr += 4;
	return(0);
}
int count_empty_indices(int * sudoku_ptr,int dim){
	long unsigned int dref_ptr = (long unsigned int) sudoku_ptr;
	short count = 0;
	for (int i=0;i<81;i++){
		int * ref_ptr = (int *)dref_ptr;
		int value = (int)*ref_ptr;
		if (!value) {
			count++;
		}
		dref_ptr += 4;
	}
	return(count);
}
void print_sudoku_ref(int *sudoku_ptr,int dim){
	long unsigned int dref_ptr = (long unsigned int)sudoku_ptr;
	for (int i=0;i<(dim*dim);i++){
		if (i%9==0){printf("\n");}
		int * ref_ptr = (int *)dref_ptr;
		printf("%d|",*ref_ptr);
		dref_ptr = dref_ptr  + 4;
	}
}
int chr_to_int(int ch){
	/* Maps integer character bytes to actual
	   integers values using ASCII standard.*/ 
	int list[10] = {48,49,50,51,52,53,54,55,56,57};
	
	int get_index(int sch,int * arr){

		int counter = 0;
		while (counter < 10){

			if (arr[counter] == sch) {
				return(counter);
			}
			counter++;
		}
		return(-1); // Returns -1 if the given input doesn't corresponds to any ASCII integer mapping.
	}
	return(get_index(ch,list));
}
void file_handler(int * arr,int dim, char **argv){
	long unsigned int start_ptr = (long unsigned int)arr;
    FILE *sudoku_ptr;
	sudoku_ptr = fopen (argv[1], "r");
  	if (sudoku_ptr == NULL) {
  		exit (EXIT_FAILURE);
  	}

    for (int i = 0; i<dim; i++) {
    	for (int j = 0; j<(dim+1); j++){
    		char ch = getc(sudoku_ptr);
    		if (ch != '\n') {
    		  int num = (int)ch;
    		  int n = chr_to_int(num);
    		  int * ptr = (int *)start_ptr;
    		  memcpy(ptr,&n,sizeof(int));
              start_ptr = start_ptr + sizeof(int);
            }

    	}
    }
}
void print_list(int list[],int range){
	printf("[");
	for (int i = 0; i < range; i++)
	{
		if (list[i] == -1){break;}
		printf("%d,",list[i]);
	}
	printf("]\n");
}
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