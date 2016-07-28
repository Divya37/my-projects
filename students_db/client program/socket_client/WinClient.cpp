#include <winsock2.h>
#include "stdafx.h"
#include <windows.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <conio.h>

int getsocket()
{
	int hsock;
	int * p_int;
	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if (hsock == -1){
		printf("Error initializing socket %d\n", WSAGetLastError());
		return -1;
	}

	p_int = (int*)malloc(sizeof(int));
	*p_int = 1;
	if ((setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1) ||
		(setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1)){
		printf("Error setting options %d\n", WSAGetLastError());
		free(p_int);
		return -1;
	}
	free(p_int);

	return hsock;
}

void socket_client()
{

	//The port and address you want to connect to
	int host_port = 1101;
	char* host_name = "127.0.0.1";

	//Initialize socket support WINDOWS ONLY!
	unsigned short wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0 || (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)) {
		fprintf(stderr, "Could not find sock dll %d\n", WSAGetLastError());
		goto FINISH;
	}

	//Initialize sockets and set any options

	//Connect to the server
	struct sockaddr_in my_addr;

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(host_port);

	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = inet_addr(host_name);

	//if( connect( hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == SOCKET_ERROR ){
	//	fprintf(stderr, "Error connecting socket %d\n", WSAGetLastError());
	//	goto FINISH;
	//}

	//Now lets do the client related stuff
	char buffer[1024];
	int buffer_len = 1024;
	int bytecount;
	int c;

	while (true) {

		int hsock = getsocket();
		//add error checking on hsock...
		if (connect(hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == SOCKET_ERROR){
			fprintf(stderr, "Error connecting socket %d\n", WSAGetLastError());
			goto FINISH;
		}

		FILE * fp = fopen("C:\\Users\\Divya\\Desktop\\client server\\server program\\socket\\input.txt", "w");


		char *attr = (char *)malloc(sizeof(char) * 20);
		char *attr1 = (char *)malloc(sizeof(char) * 20);
		char *attr3 = (char *)malloc(sizeof(char) * 20);
		char *val1 = (char *)malloc(sizeof(char) * 20);
		char *val = (char *)malloc(sizeof(char) * 20);

		int opt;

		//printf("\nenter queries : \n");
		printf("\n\n\n1.enter query to fetch(select * where <attr2> = <value>)\n");
		printf("2.enter nested query (select * where <attr2> = <val> when <attr3> = <val>)\n3.exit\n");

		printf("enter choice :");
		fflush(stdin);
		scanf("%d", &opt);

		if (opt == 1){
			printf("\nenter query : \n");
			fflush(stdin);
			scanf("select %s where %s = %s", attr, attr1, val);
			fseek(fp, 0, SEEK_SET);
			fprintf(fp, "%d,%s,%s,%s", opt, attr, attr1, val);
			fclose(fp);
		}
		else if (opt == 2){
			printf("\nenter query : \n");
			fflush(stdin);
			scanf("select %s where %s = %s when %s = %s", attr, attr1, val, attr3, val1);

			fseek(fp, 0, SEEK_SET);
			fprintf(fp, "%d,%s,%s,%s,%s,%s", opt, attr, attr1, val, attr3, val1);
			fclose(fp);
		}
		else{
			break;
		}

		strcpy(buffer, "input.txt");
		printf("\ndata being send : %s", buffer);
		if ((bytecount = send(hsock, buffer, strlen(buffer), 0)) == SOCKET_ERROR){
			fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
			goto FINISH;
		}
		if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
			fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
			goto FINISH;
		}
		printf("Recieved bytes %d\nReceived string \"%s\"\n", bytecount, buffer);
		printf("%s\n", buffer);
		FILE *f = fopen(buffer, "r");
		while (!feof(f)){
			fread(buffer, sizeof(buffer), 1, f);
			printf("%s", buffer);
		}
		fclose(f);
		closesocket(hsock);
	}

	//closesocket(hsock);
FINISH:
	;

}