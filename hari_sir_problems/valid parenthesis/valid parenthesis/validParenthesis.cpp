// given a number n print all the valid parenthesis possible 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void print_valid_parenthesis(int n, int open, int close, int index){
	
	static char output[20];
	if (close == n)
	{
		//output[close] = '\n';
		printf("%s \n", output);
		//memset(output, '\0', sizeof(output));
		return;
	}
	else
	{
		if (open > close) {
			output[index] = ')';
			print_valid_parenthesis(n, open, close + 1, index + 1);
		}
		if (open < n) {
			output[index] = '(';
			print_valid_parenthesis(n, open + 1, close, index + 1);
		}
	}
}

void main(){
	int n = 4;
	if (n % 2 == 1){
		n = n - 1;
	}
	print_valid_parenthesis(n,0,0,0);
	_getch();
}