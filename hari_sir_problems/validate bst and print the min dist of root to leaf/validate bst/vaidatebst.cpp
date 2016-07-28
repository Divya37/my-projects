//validating bst and minimum height of bst

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *left;
	struct node *right;
};
int min(int x, int y)
{
	return (x < y) ? x : y;
}
struct node * new_node_spec(int data){
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
struct node * add_node_spec(struct node *root, int data){
	if (root == NULL) return new_node_spec(data);

	if (data < root->data)
		root->left = add_node_spec(root->left, data);
	else if (data > root->data)
		root->right = add_node_spec(root->right, data);
	return root;
}
bool isBST(struct node* root)
{
	if (root == NULL) return(true);

	if (root->left != NULL && root->left->data > root->data)
		return(false);

	if (root->right != NULL && root->right->data <= root->data)
		return(false);

	if (!isBST(root->left) || !isBST(root->right))
		return(false);

	return(true);
}
int minheight(struct node *root){
	if (root == NULL)
		return 0;
	if (root->left != NULL)
		return minheight(root->left);
	if (root->right != NULL)
		return minheight(root->right);
	return min(minheight(root->left), minheight(root->right)) + 1;
}
void main()
{
	struct node *root = NULL;
	int nums[20] = { 50, 25, 75, 15, 35,
		90, 5, 17, 45, 120,
		1, 7, 19, 39, 49,
		100, 20, 21, 22, 23
	};

	for (int i = 0; i < 20; i++){
		root = add_node_spec(root, nums[i]);
	}

	//int ans = 3;
	int dist = minheight(root);
	printf("%d", dist);
	_getch();

}