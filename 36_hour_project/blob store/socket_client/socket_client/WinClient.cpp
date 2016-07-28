#include "stdafx.h"
#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <conio.h>
#pragma warning(disable:4996)
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

char *int_to_str(long s){
	int n, i=0;
	char *size=(char*)malloc(sizeof(char)*20);
	while (s > 0){
		n = s % 10;
		size[i++] = n + 48;
		s = s / 10;
	}
	size[i] = '\0';
	return strrev(size);
}

void socket_client()
{

	//The port and address you want to connect to
	int host_port= 1101;
	char* host_name="127.0.0.1";

	//Initialize socket support WINDOWS ONLY!
	unsigned short wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 2, 2 );
 	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 || ( LOBYTE( wsaData.wVersion ) != 2 ||
		    HIBYTE( wsaData.wVersion ) != 2 )) {
	    fprintf(stderr, "Could not find sock dll %d\n",WSAGetLastError());
		goto FINISH;
	}

	//Initialize sockets and set any options

	//Connect to the server
	struct sockaddr_in my_addr;

	my_addr.sin_family = AF_INET ;
	my_addr.sin_port = htons(host_port);
	
	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = inet_addr(host_name);

	char *buffer = (char *)malloc(sizeof(char)*2048);
	int buffer_len = 2048;
	int bytecount;
	int c;
	char *downfile = (char *)malloc(sizeof(char) * 15);
	char option, opt, *uname = (char *)malloc(sizeof(char) * 5);
	char *filename = (char *)malloc(sizeof(char)*20);
	while (true) {

		int hsock = getsocket();
		//add error checking on hsock...
		if (connect(hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == SOCKET_ERROR){
			fprintf(stderr, "Error connecting socket %d\n", WSAGetLastError());
			goto FINISH;
		}

		memset(buffer, '\0', buffer_len);

		printf("\n\t************ WELCOME TO BLOB STORE ************\n\n");

		printf("\n1.Upload file\n2.Download file\n3.View file\n4.Delete file\n");
		printf("enter the option: \n");
		fflush(stdin);
		scanf("%c", &option);
		//admin = divya
		if (option == '1')
		{
			printf("\nlogin as: ");
			fflush(stdin);
			scanf("%s", uname);

			printf("enter the file name to upload : ");
			fflush(stdin);
			scanf("%s", filename);

			FILE *fp = fopen(filename, "rb");

			fseek(fp, 0, SEEK_END);
			long size = ftell(fp);
			char *ss = int_to_str(size);
			fseek(fp, 0, SEEK_SET);

			buffer = strcat(buffer, filename);	
			buffer = strcat(buffer, ",");
			buffer = strcat(buffer, ss);
			buffer = strcat(buffer, "1");
			if ((bytecount = send(hsock, buffer, strlen(buffer), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("Sent bytes %d\n", bytecount);
			FILE *fo = fopen("temp.bin", "wb");
			while (!feof(fp)){
				memset(buffer, '\0', 2048);
				fread(buffer, 2048, 1, fp);
				fwrite(buffer, 2048, 1, fo);
				if ((bytecount = send(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
					fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
					goto FINISH;
				}
				printf("~");

				if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
					fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
					goto FINISH;
				}
			}
			printf("\n\ncame out of loop");
			fclose(fp);
			fclose(fo);
		}
		if (option == '2'){
			printf("\nenter the file into which downloading should happen: ");
			fflush(stdin);
			scanf("%s", downfile);
			filename = strcat(filename, downfile);
			filename = strcat(filename, ",");
			printf("enter the file name to download : ");
			fflush(stdin);
			scanf("%s", filename);
			filename = strcat(filename, "2");
			if ((bytecount = send(hsock, filename, strlen(filename), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("\nSent bytes %d, sent data %s\n", bytecount, buffer);

			if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("\nrecieved : %s", buffer);
		}
		if (option == '3'){
			printf("enter the user name to view files : ");
			fflush(stdin);
			scanf("%s", filename);
			filename = strcat(filename, "3");
			if ((bytecount = send(hsock, filename, strlen(filename), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("Sent bytes %d sent data %s\n", bytecount, filename);

			if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("\nrecieved : %s", buffer);
		}
		if (option == '4'){
			printf("enter the file name to delete : ");
			fflush(stdin);
			scanf("%s", filename);
			filename = strcat(filename, "4");
			if ((bytecount = send(hsock, filename, strlen(filename), 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("\nSent bytes %d\n", bytecount);
			if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
				goto FINISH;
			}
			printf("\nrecieved : %s", buffer);
		}


		closesocket(hsock);
	}
	
FINISH:
;
}