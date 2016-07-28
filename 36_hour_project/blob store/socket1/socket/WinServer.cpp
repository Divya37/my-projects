#include "stdafx.h"
#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#pragma warning(disable:4996)
bool flag = true;
int mid = 0;
int count1 = 0;
char *Data[100];
int count = 1;
int values[100];
DWORD WINAPI SocketHandler(void*);
void replyto_client(char *buf, int *csock);

struct files{
	char user[8];
	char file_name[20];
	long size;
};

struct files createnode(char *path, long pos, char *username, FILE *fp){

	struct files temp;
	strcpy(temp.user, username);
	strcpy(temp.file_name, path);
	temp.size = pos;
	printf("\ntemp -> username = %s", temp.user);
	printf("\ntemp -> filename = %s", temp.file_name);
	printf("\ntemp -> size = %ld", temp.size);
	return temp;
}

void print(struct files head){
	struct files temp = head;
	printf("\ntemp -> filename = %s", temp.user);
	printf("\ntemp -> filename = %s", temp.file_name);
	printf("\ntemp -> size = %ld", temp.size);
}

struct files findfile(char *name, FILE *fp){

	fseek(fp, 0, SEEK_SET);
	struct files f;
	fread(&f, sizeof(f), 1, fp);

	if (!strcmp(f.file_name, name))
		return f;

	else{
		while (!feof(fp)){
			fseek(fp, ftell(fp) + f.size, SEEK_SET);
			fread(&f, sizeof(f), 1, fp);
			if (!strcmp(f.file_name, name))return f;
		}
		return f;
	}
}
long findfilepos(char *name, FILE *fp){
	fseek(fp, 0, SEEK_SET);
	struct files f;
	long x = ftell(fp);
	fread(&f, sizeof(f), 1, fp);

	if (!strcmp(f.file_name, name))
		return x;

	else{
		while (!feof(fp)){
			fseek(fp, ftell(fp) + f.size, SEEK_SET);
			x = ftell(fp);
			fread(&f, sizeof(f), 1, fp);
			if (!strcmp(f.file_name, name))return x;
		}
		return x;
	}
}

struct files find_prevfile(char *name, FILE *fp){

	fseek(fp, 0, SEEK_SET);
	struct files f, prev;
	fread(&f, sizeof(f), 1, fp);

	if (!strcmp(f.file_name, name))
		return f;

	else{
		while (!feof(fp)){
			fread(&prev, sizeof(f), 1, fp);
			fseek(fp, ftell(fp) + f.size, SEEK_SET);
			fread(&f, sizeof(f), 1, fp);
			if (!strcmp(f.file_name, name))
				return prev;
		}
		return f;
	}
}


void upload(FILE *fp, char *path, char *username, long size, int *csock){

	fseek(fp, 0, SEEK_END);
	fwrite(path, size, 1, fp);
	fclose(fp);
	replyto_client("\nupload successfull...", csock);

}


void download(FILE *fp, char *fname, char *outname, int *csock){
	char *buff = (char *)malloc(sizeof(char) * 1024 * 1024);

	struct files f = findfile(fname, fp);
	long pos = findfilepos(fname, fp);
	fread(buff, f.size, 1, fp);
	FILE *t = fopen(outname, "wb");
	fwrite(buff, f.size, 1, t);
	printf("\nin download file : fsize = %ld", f.size);
	fclose(t);
	fclose(fp);
	replyto_client("\ndownload successfull...", csock);

}

void view(FILE *fp, char *uname, int *csock){
	char *buff = (char *)malloc(sizeof(char) * 1024);

	fseek(fp, 0, SEEK_SET);
	struct files f;
	fread(&f, sizeof(f), 1, fp);
	if (!strcmp(f.user, uname))
		buff = strcpy(buff, f.file_name);
	buff = strcat(buff, "\n");
	while (!feof(fp)){
		fseek(fp, ftell(fp) + f.size, SEEK_SET);
		fread(&f, sizeof(f), 1, fp);
		if (!strcmp(f.user, uname)){
			printf("\n %s", f.file_name);
			buff = strcat(buff, f.file_name);
			buff = strcat(buff, "\n");
		}			
	}
	fclose(fp);
	replyto_client(buff, csock);
}

void deletefile(FILE *fp, char *fname, int *csock){

	char *buff = (char *)malloc(sizeof(char) * 1024);

	struct files f = findfile(fname, fp);
	long pos = findfilepos(fname, fp);
	strcpy(f.file_name,"~~~");
	fseek(fp, pos, SEEK_SET);
	fwrite(&f, sizeof(f), 1, fp);
	fclose(fp);
	replyto_client("\ndeleted successfull...", csock);

}

struct node
{
	char msg[128];
	int msg_id;
	node *next;
}*flist,*alist,*printid;

struct bufserv{	
		int userId;
		int forumId;
		int msgId;
		int commentId;
		int choice;
		char *forumname;
		char msg[128];
}buf1;

void socket_server() {

	//The port you want the server to listen on
	int host_port = 1101;

	unsigned short wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0 || (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)) {
		fprintf(stderr, "No sock dll %d\n", WSAGetLastError());
		goto FINISH;
	}

	//Initialize sockets and set options
	int hsock;
	int * p_int;
	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if (hsock == -1){
		printf("Error initializing socket %d\n", WSAGetLastError());
		goto FINISH;
	}

	p_int = (int*)malloc(sizeof(int));
	*p_int = 1;
	if ((setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1) ||
		(setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1)){
		printf("Error setting options %d\n", WSAGetLastError());
		free(p_int);
		goto FINISH;
	}
	free(p_int);

	//Bind and listen
	struct sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(host_port);

	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = INADDR_ANY;

	/* if you get error in bind
	make sure nothing else is listening on that port */
	if (bind(hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1){
		fprintf(stderr, "Error binding to socket %d\n", WSAGetLastError());
		goto FINISH;
	}
	if (listen(hsock, 10) == -1){
		fprintf(stderr, "Error listening %d\n", WSAGetLastError());
		goto FINISH;
	}

	//Now lets do the actual server stuff

	int* csock;
	sockaddr_in sadr;
	int	addr_size = sizeof(SOCKADDR);

	while (true){
		printf("waiting for a connection\n");
		csock = (int*)malloc(sizeof(int));

		if ((*csock = accept(hsock, (SOCKADDR*)&sadr, &addr_size)) != INVALID_SOCKET){
			//printf("Received connection from %s",inet_ntoa(sadr.sin_addr));
			CreateThread(0, 0, &SocketHandler, (void*)csock, 0, 0);
		}
		else{
			fprintf(stderr, "Error accepting %d\n", WSAGetLastError());
		}
	}

FINISH:
	;
}

void replyto_client(char *buf, int *csock) {
	int bytecount;
	
	if((bytecount = send(*csock, buf, strlen(buf), 0))==SOCKET_ERROR){
		fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
		free (csock);
	}
	//printf("\nreplied to client: %s\n",buf);
}

DWORD WINAPI SocketHandler(void* lp){
    int *csock = (int*)lp;
	char *uname = (char *)malloc(sizeof(char) * 5);
	char *recvbuf = (char *)malloc(sizeof(char)*2048);
	int recvbuf_len = 2048;
	int recv_byte_cnt;

	memset(recvbuf, 0, recvbuf_len);
	if((recv_byte_cnt = recv(*csock, recvbuf, recvbuf_len, 0))==SOCKET_ERROR){
		fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
		free (csock);
		return 0;
	}
	int option = atoi(&recvbuf[strlen(recvbuf) - 1]);
	recvbuf[strlen(recvbuf) - 1] = '\0';
	printf("\nselected option : %d", option);
	
	if (option == 1){
		FILE *fp = fopen("thisbin.bin", "rb+");
		uname = "divya";
		char *buf = strtok(recvbuf, ",");
		recvbuf = strtok(NULL, ",");
		long size = atoi(recvbuf);
		char *ff = (char *)malloc(sizeof(char)*size);
		memset(ff, '\0', sizeof(ff));
		fseek(fp, 0, SEEK_END);
		struct files head = createnode(buf, size, uname, fp);
		fwrite(&head, sizeof(head), 1, fp);
		FILE *fo = fopen("temp.bin", "wb");
		replyto_client("\nreceived details", csock);
		while (size >= 0){
			memset(recvbuf, 0, recvbuf_len);
			if ((recv_byte_cnt = recv(*csock, recvbuf, recvbuf_len, 0)) == SOCKET_ERROR){
				fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
				free(csock);
				return 0;
			}
			fwrite(recvbuf, 2048, 1, fo);
			replyto_client("\nyup", csock);
			size = size - 2048;
		}
		fclose(fo);
		fo = fopen("temp.bin", "rb");
		fseek(fo, 0, SEEK_SET);
		fread(ff, head.size, 1, fo);
		printf("\n%s\t%s\t\n%s\t\t%ld", uname, buf, ff, head.size);
		
		upload(fp, ff, uname, head.size, csock);
		
	}
	else if (option == 2){
		FILE *fp = fopen("thisbin.bin", "rb");
		uname = strtok(recvbuf, ",");
		recvbuf = strtok(recvbuf, ",");
		printf("\n%s\t%s", uname, recvbuf);
		download(fp, recvbuf, uname, csock);
		
	}
	else if (option == 3){
		FILE *fp = fopen("thisbin.bin", "rb");
		printf("\nrecv buf : %s\n", recvbuf);
		view(fp, recvbuf, csock);
		
	}
	else if(option == 4){
		FILE *fp = fopen("thisbin.bin", "rb+");
		deletefile(fp, recvbuf, csock);
		
	}

	return 0;
	
}