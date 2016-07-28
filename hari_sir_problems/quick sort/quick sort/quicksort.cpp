#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int partition(int *a, int start, int end){
	int pivot = a[end];
	int pindex = start;
	for (int i = start; i < end; i++){
		if (a[i] <= pivot){
			int temp = a[i];
			a[i] = a[pindex];
			a[pindex] = temp;
			pindex++;
		}
	}
	int temp = a[end];
	a[end] = a[pindex];
	a[pindex] = temp;
	return pindex;
}

void qsort(int *a, int start, int end){
	if (start < end){
		int p = partition(a, start, end);
		qsort(a, start, p - 1);
		qsort(a, p+1, end);
	}
}

void main(){
	int a[] = { 3, 2, 1, 4, 5, 7, 8, 0 };
	qsort(a, 0, 7);
	for (int i = 0; i < 8; i++){
		printf("%d ", a[i]);
	}
	_getch();
}