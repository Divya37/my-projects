// client side program
#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

DWORD WINAPI MyThreadFun(void * lp){
	int *csock = (int*)lp;
	FILE *fs = fopen("C:\\Users\\Divya\\Documents\\Visual Studio 2013\\Projects\\myserver program\\myserver program\\serverfile.txt", "r+");
	int flag = 0;
	char buf[100];
	fscanf(fs, "%d,%s", &flag, buf);
	printf("\nreply : %s", buf);
	fseek(fs, 0, SEEK_SET);
	fprintf(fs, "%d", 0);
	fclose(fs);
	return 0;
}

void main()
{
	char *reply = (char *)malloc(sizeof(char) * 100);

	int key, flag = 0;
	int offset = 0;
	char *message = (char *)malloc(sizeof(char) * 100);
	char *buf = (char *)malloc(sizeof(char) * 100);
	memset(message, '\0', sizeof(message));
	DWORD threadID;
	while (1){
		FILE *fc = fopen("C:\\Users\\Divya\\Documents\\Visual Studio 2013\\Projects\\myserver program\\myserver program\\clientfile.txt", "w");
		FILE *fs = fopen("C:\\Users\\Divya\\Documents\\Visual Studio 2013\\Projects\\myserver program\\myserver program\\serverfile.txt", "r+");
		printf("\nsend message : ");
		gets(message);
		fseek(fc, 0, SEEK_SET);
		fprintf(fc, "%d,%s", 1, message);
		fclose(fc);
		while (1)
		{
			fseek(fs, 0, SEEK_SET);
			fscanf(fs, "%d,%s", &flag, buf);
			if (flag == 1){				
				CreateThread(NULL, 0, &MyThreadFun, NULL, 0, &threadID);
				Sleep(500);
				break;
			}
		}
		
		fclose(fs);
	}

}
