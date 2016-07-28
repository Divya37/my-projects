#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int index = 0;
struct node {
	int val;
	int count = 0;
	struct node *next;
};

struct node * enqueue(int ele, struct node *start){
	index++;
	struct node *temp = (struct node *)malloc(sizeof(struct node)), *temp1=start;
	temp->val = ele;
	temp->next = NULL;
	if (start == NULL)
		return temp;
	while (temp1->next != NULL){
		temp1 = temp1->next;
	}
	temp1->next = temp;
	return start;
}
struct node * dequeue(struct node *start, int ele){
	if (start == NULL)
		return NULL;
	struct node * temp=start, *prev;
	prev = temp;
	while (temp->next != NULL){
		
		if (temp->val == ele){
			prev->next = temp->next;
			break;
		}
		prev = temp;
		temp = temp->next;
		
	}
	temp->next = temp->next->next;
	return start;
}
bool isinarray(struct node *start, int ele){
	struct node *temp = start;
	if (start == NULL)
		return false;
	while(temp->next !=NULL){
		if (ele == temp->val)
			return true;
		temp = temp->next;
	}
	return false;
}
void main(){
	int ele, op;
	printf("enter the position : ");
	//fflush(stdin);
	scanf("%d", &op);
	struct node *start = NULL;
	FILE *fp = fopen("input.txt", "r");
	while (!feof(fp)){
		fscanf(fp, "%d\n", &ele);
		if (!isinarray(start, ele))
			start = enqueue(ele, start);
		else
			start = dequeue(start, ele);
		if (op == index)
		{
			while(start->next != NULL && op>0){
				printf("\n%d", start->val);
				start = start->next;
				op--;
			}
				
			break;
		}
		
	}
	_getch();
}