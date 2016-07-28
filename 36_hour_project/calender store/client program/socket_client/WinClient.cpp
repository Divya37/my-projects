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
	int * p_int ;
	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if(hsock == -1){
		printf("Error initializing socket %d\n",WSAGetLastError());
		return -1;
	}
	
	p_int = (int*)malloc(sizeof(int));
	*p_int = 1;
	if( (setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
		(setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) ){
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
	char option, *name = (char *)malloc(sizeof(char) * 20), *spec = (char *)malloc(sizeof(char) * 20);
	char *id = (char *)malloc(sizeof(char) * 5), *d = (char *)malloc(sizeof(char) * 3), *m = (char *)malloc(sizeof(char) * 3), *y = (char *)malloc(sizeof(char) * 5);
	printf("\n\t\t******WELCOME TO CALENDER STORE******\n");
	while (true) {
		
		int hsock = getsocket();
		//add error checking on hsock...
		if (connect(hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == SOCKET_ERROR){
			fprintf(stderr, "Error connecting socket %d\n", WSAGetLastError());
			goto FINISH;
		}

		printf("\n1.create category\n2.create new person\n3.get appointment from person\n");
		fflush(stdin);
		scanf("%c", &option);
		if (option == '1'){
			memset(name, '\0', sizeof(name));
			strcpy(name, "1");
			printf("\ndata being send : %s", name);
			if ((bytecount = send(hsock, name, strlen(name), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}

			printf("\nenter category name : ");
			fflush(stdin);
			scanf("%s", name);
			//name = strcat(name, &option);
			printf("\ndata being send : %s", name);
			if ((bytecount = send(hsock, name, strlen(name), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}

			///printf("\tSent bytes %d\n", bytecount);
			memset(buffer, '\0', sizeof(buffer));
			if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("\n%s\n", bytecount, buffer);
			
		}
		if (option == '2'){
			memset(name, '\0', sizeof(name));
			strcpy(name, "2");
			printf("\ndata being send : %s", name);
			if ((bytecount = send(hsock, name, strlen(name), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}
			memset(buffer, '\0', sizeof(buffer));
			if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("\n%s\n", bytecount, buffer);
			printf("\nchoose category :");
			fflush(stdin);
			scanf("%s", id);
			memset(name, '\0', sizeof(name));
			strcpy(name, id);

			printf("\ndata being send : %s", name);
			if ((bytecount = send(hsock, name, strlen(name), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}
			//printf("\tSent bytes %d\n", bytecount);
			if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("\n%s\n", bytecount, buffer);

			printf("\nenter new person name : ");
			fflush(stdin);
			scanf("%s", name);
			
			printf("\nenter new person specialization : ");
			fflush(stdin);
			scanf("%s", spec);

			printf("\nenter new person id : ");
			fflush(stdin);
			scanf("%s", id);

			strcat(name, ",");
			strcat(name, spec);
			strcat(name, ",");
			strcat(name, id);

			printf("\ndata being send : %s", name);
			if ((bytecount = send(hsock, name, strlen(name), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}
			//printf("\tSent bytes %d\n", bytecount);
			memset(buffer, '\0', sizeof(buffer));
			if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("\n%s\n", bytecount, buffer);

		}
		if (option == '3'){
			memset(name, '\0', sizeof(name));
			strcpy(name, "3");
			printf("\ndata being send : %s", &name);
			if ((bytecount = send(hsock, name, strlen(name), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}
			//printf("\tSent bytes %d\n", bytecount);
			memset(buffer, '\0', sizeof(buffer));
			if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("\n%s\n", bytecount, buffer);

			printf("\nchoose category :");
			fflush(stdin);
			scanf("%s", id);
			memset(name, '\0', sizeof(name));
			strcpy(name, id);

			printf("\ndata being send : %s", name);
			if ((bytecount = send(hsock, name, strlen(name), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}
			//printf("\tSent bytes %d\n", bytecount);
			memset(buffer, '\0', sizeof(buffer));
			if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("\n%s\n", bytecount, buffer);
			printf("\nchoose person :");
			fflush(stdin);
			scanf("%s", id);
			memset(name, '\0', sizeof(name));
			strcpy(name, id);
			printf("\ndata being send : %s", name);
			if ((bytecount = send(hsock, name, strlen(name), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}
			//printf("\tSent bytes %d\n", bytecount);
			
			printf("\nenter username : ");
			fflush(stdin);
			scanf("%s", name);
			printf("\nenter date : ");
			scanf("%s - %s - %s", d, m, y);
			strcat(name, ",");
			strcat(name, d);
			strcat(name, ",");
			strcat(name, m);
			strcat(name, ",");
			strcat(name, y);

			printf("\ndata being send : %s", name);
			if ((bytecount = send(hsock, name, strlen(name), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}
			//printf("\tSent bytes %d\n", bytecount);
			memset(buffer, '\0', sizeof(buffer));
			if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("\n%s\n", bytecount, buffer);

		}
		if (option == '4'){
			closesocket(hsock);
			break;
		}
		closesocket(hsock);
	}

FINISH:
;
}