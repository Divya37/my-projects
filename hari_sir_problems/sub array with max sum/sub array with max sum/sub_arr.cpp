//program to find a sub array with maximum sum.
#include<stdio.h>
#include<conio.h>

int max(int *arr, int size){
	int maxval = -999999999;
	for (int i = 0; i < size; i++){
		if (maxval < arr[i])
			maxval = arr[i];
	}
	return maxval;
}
void sub_arr(int *arr,int size)
{
	int i, sum = 0, c_sum = 0, sum1 = 0, end = 0, max_sum = -999999999;
	
	for (i = 0; i < size; i++){		
		sum1 += arr[i];
			if (arr[i] > 0)
				c_sum += arr[i];
			if (sum1 > max_sum)
				max_sum = sum1;
			if (sum1 < 0)
				sum1 = 0;
			
	}
	if (c_sum == 0)
		c_sum = max(arr, size);
	printf("%d,%d", max_sum, c_sum); 
		
}
void main()
{
	int arr[] = { 14, 15, -2, -6, -14, 2, -13, 2, 0,25 };
	sub_arr(arr, 10);
	_getch();
}