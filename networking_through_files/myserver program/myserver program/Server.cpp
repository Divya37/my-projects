// server side program

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include <Windows.h>

#pragma warning(disable:4996)

DWORD WINAPI MyThreadFun(void * lp){
	int *csock = (int*)lp;
	FILE *fp = fopen("clientfile.txt", "r+");
	int flag = 0;
	char buf[100];
	fscanf(fp, "%d%s", &flag, buf);
	printf("\nreply : %s", buf);
	fseek(fp, 0, SEEK_SET);
	fprintf(fp, "%d", 0);
	return 0;
}

void main()
{
	char *reply = (char *)malloc(sizeof(char) * 100);

	int key, flag = 0;
	int offset = 0;
	char *message = (char *)malloc(sizeof(char) * 100);
	memset(message, '\0', sizeof(message));
	char *buf = (char *)malloc(sizeof(char) * 100);
	DWORD threadID;
	while (1){
		
		FILE *fc = fopen("clientfile.txt", "r+");
		while (1){
			fseek(fc, 0, SEEK_SET);
			fscanf(fc, "%d,%s", &flag, buf);
			if (flag == 1){
				CreateThread(NULL, 0, &MyThreadFun, NULL, 0, &threadID);
				Sleep(500);
				break;
			}
		}
		printf("\nsend message : ");
		gets(message);
		FILE *fs = fopen("serverfile.txt", "w");
		fseek(fs, 0, SEEK_SET);
		fprintf(fs, "%d,%s", 1, message);
		fclose(fs);
		fclose(fc);
	}
			
}
	
