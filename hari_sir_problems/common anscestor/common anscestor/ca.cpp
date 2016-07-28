

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *left;
	struct node *right;
};

struct node *insert(struct node *head, int data){

	if (head == NULL)
	{
		struct node *temp = (struct node *)malloc(sizeof(struct node));

		temp->data = data;
		temp->left = NULL;
		temp->right = NULL;
		return temp;
	}

	if (head->data > data)
	{
		head->left = insert(head->left, data);
	}
	else if (head->data <= data)
	{
		head->right = insert(head->right, data);
	}
	return head;
}

int issorted(int *arr, int size){

	int i = 0;
	for (i = 0; i < size - 1; i++){
		if (arr[i] > arr[i + 1])
			return 0;
	}
	return 1;
}

void inorder_traversal(struct node *root, int *arr, int *index)
{
	if (root == NULL)
		return;
	inorder_traversal(root->left, arr, index);
	arr[*index] = root->data;
	printf("%d\t", arr[*index]);
	*index = *index + 1;
	inorder_traversal(root->right, arr, index);
}

int inorder(struct node *root, int *arr){

	int i = 0;
	if (arr == NULL)
		return 0;
	inorder_traversal(root, arr, &i);

	return issorted(arr, i);

}

int validtree(struct node *head){
	int *arr = (int *)malloc(sizeof(int) * 10);
	return inorder(head, arr);
}

struct node *common_ans(struct node *head, int data1, int data2){

	if (head == NULL)
		return NULL;
	if (head->data > data1 && head->data > data2){
		return common_ans(head->left, data1, data2);
	}

	if (head->data < data1 && head->data < data2){
		return common_ans(head->right, data1, data2);
	}
	return head;
}

void main(){

	struct node *head = NULL;

	head = insert(head, 15);
	head = insert(head, 13);
	head = insert(head, 18);
	head = insert(head, 24);
	head = insert(head, 11);
	head = insert(head, 14);
	
	struct node *t = common_ans(head, 11, 13);
	printf("common ancestor = %d", t->data);

	_getch();

}