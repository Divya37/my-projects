#include<stdio.h>
#include<conio.h>
#include<stdlib.h>


#pragma warning(disable:4996)



int path(int *maze, int rows, int x1, int y1, int x2, int y2, int *arr)
{
	if ((x1 == x2) && (y1 == y2))	
		return 1;
	if (*((arr + x1*rows) + y1) == 1) 
		return 0;
	else 
		*((arr + x1*rows) + y1) = 1;
	if (x1 >= 0 && x1<y2 && y1 >= 0 && y1<y2 && *((maze + x1*rows) + y1) == 1)
	{
		if (path(maze, rows, x1, y1 + 1, x2, y2, arr) == 1)
			return 1;
		if (path(maze, rows, x1 + 1, y1, x2, y2, arr) == 1)
			return 1;

		return 0;
	}
	return 0;
}
int path_exists(int *maze, int rows, int columns, int x1, int y1, int x2, int y2)
{
	if (rows <= 0 || columns <= 0 || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0 ||
		x1 >= rows || x2 >= rows || y1 >= columns || y2 >= columns)
		return 0;
	int *arr = (int *)malloc(sizeof(int)*(rows + columns));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			*((arr + i*rows) + j) = 0;
		}
	}
	if (path(maze, columns, x1, y1, x2, y2, arr) == 1) return 1;
	else return 0;

}

void main()
{
	int maze[1][2] = {
		{ 1, 1 }//, 0, 0, 1 },
		//{ 1, 1, 0, 1, 1 },
		//{ 0, 1, 1, 1, 0 }
	};
	int rows = 1, columns = 2;
	int x1, x2, y1, y2;

	
	x1 = 0, y1 = 0, x2 = 0, y2 = 1;
	printf("maze[%d][%d] = %d , maze[%d][%d] = %d", x1, y1, maze[x1][y1], x2, y2, maze[x2][y2]);

	if (path_exists((int *)maze, rows, columns, x1, y1, x2, y2))
		printf("\npath found");
	else
		printf("\npath not found");
	_getch();
}