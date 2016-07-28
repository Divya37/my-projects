#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#pragma warning(disable:4996)

DWORD WINAPI MyThreadFun(void* lp){
	int *csock = (int*)lp;
	printf("\nhey its my first thread :)");
	return 0;
}

void main(){
	printf("\nentered in main");
	DWORD threadID;
	CreateThread(NULL, 0, &MyThreadFun, NULL, 0, &threadID);
	
	printf("\nother bussiness");
	printf("\nexiting main");
	//CloseHandle(hThread);
	getch();
}