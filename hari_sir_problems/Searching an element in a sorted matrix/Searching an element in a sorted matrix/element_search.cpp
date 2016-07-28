// searching for an element in a matrix in which rows are sorted and columns are sorted

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void search_ele(int matrix[3][3], int rows, int cols, int i, int j, int ele){
	
	if (i >= rows || j < 0){
		printf("element not found");
		return;
	}
	if (ele == matrix[i][j]){
		printf("element found");
		return;
	}
	else if (ele > matrix[i][j]){
		i++;
	}
	else if (ele < matrix[i][j]){
		j--;
	}
	search_ele(matrix, rows, cols, i, j, ele);
}

void main(){
	int matrix[3][3] = {
		{ 1, 2, 3 }, 
		{4, 56, 78},
		{60, 99, 100}
	};
	int rows = 3, cols = 3, ele = 1, i = 0, j = 2;
	search_ele(matrix, rows, cols, i, j, ele);
	_getch();
}