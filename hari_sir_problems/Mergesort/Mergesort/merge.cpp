#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void merge(int *arr,int start, int end, int mid){
	int i = 0, j = 0, k=0;
	int n1 = mid - start + 1;
	int n2 = end - mid;
	int *left, *right;
	
	left = (int *)malloc(sizeof(int)*n1);
	right = (int *)malloc(sizeof(int)*n2);

	for (i = 0; i < n1; i++)
		left[i] = arr[i];
	for (i = mid; i < n2; i++)
		right[j++] = arr[i];
	i = j = 0;
	while (i < n1 && j < n2){
		if (left[i] <= right[j])
			arr[k++] = left[i];
		if (right[j] < left[i])
			arr[k++] = right[i];
	}


}

void mergesort(int *arr, int start, int end){
	if (start < end)
	{
		int mid = (start + end) / 2;
		mergesort(arr, start, mid);
		mergesort(arr, mid + 1, end);	
		merge(arr, start, end, mid);
	}

}

void main(){
	//int arr[10] = { 1, 2, 3, 4, 5, 6, 10, 87, 90, 12 };
	int arr2[10] = { 12, 43, 1, 67, 4, 89, 86, 34, 54, 67 };
	mergesort(arr2, 0, 10);
	_getch();
}