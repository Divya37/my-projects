// C program to print all permutations with duplicates allowed

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
void swap(char *x, char *y)
{
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int indict(char *s){
	char *temp = (char *)malloc(sizeof(char) * 20);
	FILE *fp = fopen("corncob_lowercase.txt", "r");
	//FILE *fpp = fopen("corncob_lowercase.txt", "r");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp)){
		fscanf(fp, "%s\n", temp);
		if (!strcmp(s, temp))
			return 1;
	}
	return 0;
}

void permute(char *a, int start, int end)
{
	if (start == end){
		if (indict(a)){
			printf("\n%s", a);
		}
	}
	else
	{
		for (int i = start; i <= end; i++)
		{
			swap((a + start), (a + i));
			permute(a, start + 1, end);
			swap((a + start), (a + i));
		}
	}
}

void main()
{
	char str[] = "abatement";
	int n = strlen(str);
	permute(str, 0, n - 1);
	_getch();
}