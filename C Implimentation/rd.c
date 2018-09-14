#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int mod_arr();
void mod_structure();
int main(void){
	struct u {
		int a;
		int b;
	};
	struct u var[2];
	mod_structure(&var);
	printf("A:%d, B:%d \n",var[0].a,var[0].b);
	printf("A:%d, B:%d \n",var[1].a,var[1].b);
	printf("Address of a is:%x and b is:%x\n",&var[0].a,&var[0].b);
	printf("Address of a is:%x and b is:%x\n",&var[1].a,&var[1].b);
	printf("\nAddress of var 0 is:%x\n",&var[0]);
	printf("\nAddress of var 0 + $ Bytes is:%x\n",(&var[0]+2));
	printf("\nAddress of var 1 is:%x\n",&var[1]);
	return(0);
}

void mod_structure(int * start_ptr){
	long unsigned int int_unref_ptr = (long unsigned int) start_ptr;

	void modify(long unsigned int unref_ptr,int bytes_to_push,int data){
		int * ref_ptr = (int *) unref_ptr;
		memcpy(ref_ptr,&data,bytes_to_push);
	}

	modify(int_unref_ptr,4,14);
	int_unref_ptr += 4;
	modify(int_unref_ptr,4,98);
	int_unref_ptr += 4;
	modify(int_unref_ptr,4,109);
	int_unref_ptr += 4;
	modify(int_unref_ptr,4,166);


}
/*
int mod_arr(int *arr,int dimx , int dimy){

	long unsigned int start_ptr = arr;

	for(int i=0;i<3;i++) {

		for (int j=0;j<3;j++) {

			printf("Enter the value at index %di,%dj:",i,j);
			scanf("%d",start_ptr);
			start_ptr = start_ptr+4;
		
		}
	}
	return(0);

}
*/