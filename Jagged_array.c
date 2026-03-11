#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct line{
	int len;
	int* data;
};

struct jagged_array{
	int lines_number;
	int numbers_count;
	struct line* data;
};
//===============================================
int free_jagged_array(struct jagged_array* arr_ptr){
	int i;
	for (i=0;i<arr_ptr->lines_number;i++){
		if (arr_ptr->data[i].data!=NULL){free(arr_ptr->data[i].data);}
	}
	free(arr_ptr->data);

	return 0;
}
//================================================
int input(struct jagged_array* arr_ptr, const char* name){
	int i,line_number,temp_len,temp_buff,el_counter,shift,pos;
	char buffer[256];
	
	FILE* f=fopen(name,"r");
	if (f==NULL){printf("%s", "no file found\n"); return -1;};
	pos=0;
	shift=0;
	temp_len=0;
	printf("%s","counting lines\n");
	while ((fgets(buffer,256,f))!=NULL){
		temp_len++;
	}
	printf("%s","lines counted\n");
	rewind(f);
	arr_ptr->lines_number = temp_len;
	arr_ptr->data=malloc(temp_len*sizeof(struct line));
	if (arr_ptr->data==NULL){printf("%s","no array created\n"), fclose (f); return -2;}
	printf("%s","array created\n");
	for (i = 0; i < temp_len; i++){
        arr_ptr->data[i].len = 0;
        arr_ptr->data[i].data = NULL;
    }
	arr_ptr->numbers_count=0;
	printf("%s","array initialized\n");
	line_number=0;
	while ((fgets(buffer,512,f))!=NULL){
		el_counter=0;
		printf("%s","counting length\n");
		while (sscanf(buffer+pos,"%d%n",&temp_buff,&shift)>0){
			pos+=shift;
			el_counter++;
		}
		arr_ptr->data[line_number].len=el_counter;
		arr_ptr->numbers_count+=el_counter;
		printf("%s","length counted\n");
		shift=0;
		pos=0;
		if (el_counter>0){
			arr_ptr->data[line_number].data=malloc(el_counter*sizeof(int));
		}
		el_counter=0;
		printf("%s","memory allocked\n");
		if (arr_ptr->data[line_number].data==NULL){free_jagged_array(arr_ptr); fclose(f); return -3;}
		while (sscanf(buffer+pos,"%d%n",&temp_buff,&shift)>0){
			pos+=shift;
			arr_ptr->data[line_number].data[el_counter]=temp_buff;
			el_counter++;
		}
		printf("%s","line read\n");
		pos=0;
		shift=0;
		line_number++;
	}
		
	fclose(f);
	printf("%s","done\n");
	return 0;
}
//=================================================
int find_summ(struct jagged_array* arr_ptr){
	int i, j, count;
	count=0;
	for (i=0;i<arr_ptr->lines_number;i++){
		for (j=0;j<arr_ptr->data[i].len;j++){
			count+=arr_ptr->data[i].data[j];
		}
	}
	return count;
}//================================================
int is_summ(int count,int summ, int element){
	if (element*count==summ){printf("%d\n",1); return 1;}
	return 0;
}
//=================================================
int remove_a_line(struct jagged_array* arr_ptr, int y) {
    if (y < 0 || y >= arr_ptr->lines_number) {return -1;}
    int old_lines = arr_ptr->lines_number;
    arr_ptr->numbers_count -= arr_ptr->data[y].len;
    free(arr_ptr->data[y].data);
    for (int i = y; i < old_lines - 1; i++) {
        arr_ptr->data[i] = arr_ptr->data[i + 1];
    }
    arr_ptr->data[old_lines - 1].data = NULL;
    arr_ptr->data[old_lines - 1].len = 0;
    arr_ptr->lines_number--;
    return 0;
}
//=================================================
int process_array(struct jagged_array* arr_ptr){
	int i,j,summ,count,index;
	index=-1;
	count=arr_ptr->numbers_count;
	summ=find_summ(arr_ptr);
	for (i=0;i<arr_ptr->lines_number;i++){
		for (j=0;j<arr_ptr->data[i].len;j++){
			if (is_summ(count,summ,arr_ptr->data[i].data[j])){
				printf("%s","found a line\n");
				index=i;
				goto exit;
			}
		}
	}
	exit:
	return (remove_a_line(arr_ptr,index));
}
	
//=================================================
void output(struct jagged_array* arr_ptr){
	int i,j;
	for (i=0;i<arr_ptr->lines_number;i++){
		for (j=0;j<arr_ptr->data[i].len;j++){
			printf("%d%s",arr_ptr->data[i].data[j]," ");
		}
		printf("%s\n","");
	}
}
//===================================================
int main(void){
	struct jagged_array arr;
	struct jagged_array* arr_ptr;
	int count=arr_ptr->numbers_count;
	printf("%s","start\n");
	arr_ptr=&arr;
	if(input(arr_ptr,"1.txt")==0){;
	output(arr_ptr);
	process_array(arr_ptr);
	printf("%s","outputing new\n");
	output(arr_ptr);
	free_jagged_array(arr_ptr);
	printf("%s","freed\n");
	return 0;
	}
	return -1;
}