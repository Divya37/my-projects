#include "stdafx.h"
#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#pragma warning(disable:4996)
int f = 1;
bool flag = true;
int mid = 0;
int count1 = 0;
char *Data[100];
int count = 1;
int values[100];
DWORD WINAPI SocketHandler(void*);
void replyto_client(char *buf, int *csock);

struct category{
	int flag;
	int id;
	char spec[20];
	char unused[36];
};

struct person{
	int flag;
	int category_id;
	int person_id;
	char name[20];
	char specialization[20];
	char unused[12];
	//long nextperson;
	//long appointments;
};

struct appointment{
	int flag;
	int category_id;
	int person_id;
	char username[20];
	int d, m, y;
	char unused[20];
	//long nextapp;
};
int get_id(FILE *fp){
	int id = 1;
	fseek(fp, 0, SEEK_SET);
	struct category c;
	while (!feof(fp)){
		memset(&c, 0, sizeof(c));
		fread(&c, sizeof(c), 1, fp);
		if (c.flag == 1){
			id = c.id;
		}
	}
	return id + 1;
}

void createcategory(FILE *fp, char *spec, int *csock){
	long f;
	fseek(fp, 0, SEEK_END);
	f = ftell(fp);
	struct category c;
	c.flag = 1;
	if (f == 0)
		c.id = 1;
	else
		c.id = get_id(fp);
	printf("\ncid = %d\n", c.id);
	strcpy(c.spec, spec);
	fwrite(&c, sizeof(c), 1, fp);
	replyto_client("category creation successfull...", csock);
}

void createperson(FILE *fp, int cid, int pid, char *p_name, char *p_spec, int *csock){

	fseek(fp, 0, SEEK_END);
	struct person p;
	p.flag = 2;
	p.category_id = cid;
	p.person_id = pid;
	strcpy(p.name, p_name);
	strcpy(p.specialization, p_spec);
	fwrite(&p, sizeof(p), 1, fp);
	replyto_client("person creation successfull...", csock);
}

int isvalid_date(FILE *fp, int d, int m, int y){

	struct appointment a;
	memset(&a, 0, sizeof(a));
	fseek(fp, 0, SEEK_SET);
	if (m > 12 || m <= 0 || d <= 0 || y <= 0 || d>31)
		return 0;
	else{
		while (!feof(fp)){
			memset(&a, 0, sizeof(a));
			fread(&a, sizeof(a), 1, fp);
			if (a.flag == 3){
				if (a.d == d && a.m == m && a.y == y)
					return 0;
			}
		}
	}
	return 1;
}

void getappointment(FILE *fp, int cid, int pid, char *user, int d, int m, int y, int *csock){
	printf("\n in get appointments");

	fseek(fp, 0, SEEK_END);
	struct appointment a;
	a.flag = 3;
	a.category_id = cid;
	a.person_id = pid;
	strcpy(a.username, user);
	a.d = d;
	a.m = m;
	a.y = y;
	if (isvalid_date(fp, d, m, y)){
		fwrite(&a, sizeof(a), 1, fp);
		replyto_client("appointment creation successfull...", csock);
	}
	else{
		replyto_client("invalid/alreday booked date provided try again with another date :)", csock);
	}
}

void display_categories(FILE *fp, int *csock){

	char *data = (char *)malloc(sizeof(char) * 40);
	memset(data, '\0', 40);

	fseek(fp, 0, SEEK_SET);
	strcpy(data, "\n");
	struct category c;
	while (!feof(fp)){
		memset(&c, '\0', sizeof(c));
		fread(&c, sizeof(c), 1, fp);
		if (c.flag == 1){
			strcat(data, c.spec);
			strcat(data, "\n");
			printf("\n%d. %s", c.id, c.spec);
		}
	}
	
	replyto_client(data, csock);
}

void display_persons(FILE *fp, int cid, int *csock){

	char *data = (char *)malloc(sizeof(char) * 40);
	memset(data, '\0', 40);
	strcpy(data, "\n");
	fseek(fp, 0, SEEK_SET);
	struct person p;
	while (!feof(fp)){
		memset(&p, '\0', sizeof(p));
		fread(&p, sizeof(p), 1, fp);
		if (p.flag == 2){
			if (p.category_id == cid){
				strcat(data, p.name);
				strcat(data, p.specialization);
				strcat(data, "\n");
				printf("\n%d. %s - %s", p.person_id, p.name, p.specialization);
			}
		}
	}
	replyto_client(data, csock);
}

void display_appointments(FILE *fp, int cid, int pid, int *csock){

	char *data = (char *)malloc(sizeof(char) * 40);
	memset(data, '\0', 40);
	strcpy(data, "1");
	int i = 0;
	fseek(fp, 0, SEEK_SET);
	struct appointment a;
	while (!feof(fp)){
		memset(&a, '\0', sizeof(a));
		fread(&a, sizeof(a), 1, fp);
		if (a.flag == 3){
			if (a.category_id == cid && a.person_id == pid){
				strcat(data, a.username);
				strcat(data, "\n");
				//printf("\n%d. %s  %d-%d-%d", i++, a.username, a.d, a.m, a.y);
			}				
		}
	}
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
	int host_port= 1101;

	unsigned short wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 2, 2 );
 	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 || ( LOBYTE( wsaData.wVersion ) != 2 ||
		    HIBYTE( wsaData.wVersion ) != 2 )) {
	    fprintf(stderr, "No sock dll %d\n",WSAGetLastError());
		goto FINISH;
	}

	//Initialize sockets and set options
	int hsock;
	int * p_int ;
	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if(hsock == -1){
		printf("Error initializing socket %d\n",WSAGetLastError());
		goto FINISH;
	}
	
	p_int = (int*)malloc(sizeof(int));
	*p_int = 1;
	if( (setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
		(setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) ){
		printf("Error setting options %d\n", WSAGetLastError());
		free(p_int);
		goto FINISH;
	}
	free(p_int);

	//Bind and listen
	struct sockaddr_in my_addr;
	my_addr.sin_family = AF_INET ;
	my_addr.sin_port = htons(host_port);
	
	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = INADDR_ANY ;
	
	/* if you get error in bind 
	make sure nothing else is listening on that port */
	if( bind( hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1 ){
		fprintf(stderr,"Error binding to socket %d\n",WSAGetLastError());
		goto FINISH;
	}
	if(listen( hsock, 10) == -1 ){
		fprintf(stderr, "Error listening %d\n",WSAGetLastError());
		goto FINISH;
	}
	
	//Now lets do the actual server stuff

	int* csock;
	sockaddr_in sadr;
	int	addr_size = sizeof(SOCKADDR);
	
	while(true){
		printf("waiting for a connection\n");
		csock = (int*)malloc(sizeof(int));
		
		if((*csock = accept( hsock, (SOCKADDR*)&sadr, &addr_size))!= INVALID_SOCKET ){
			//printf("Received connection from %s",inet_ntoa(sadr.sin_addr));
			CreateThread(0,0,&SocketHandler, (void*)csock , 0,0);
		}
		else{
			fprintf(stderr, "Error accepting %d\n",WSAGetLastError());
		}
	}

FINISH:
;
}


void process_input(char *recvbuf, int recv_buf_cnt, int* csock) 
{
	int x = atoi(recvbuf);
	int recvbuf_len = 1024;
	int recv_byte_cnt;
	FILE *fp = fopen("thisbin.bin", "rb+");
	if (x == 1){
		if ((recv_byte_cnt = recv(*csock, recvbuf, recvbuf_len, 0)) == SOCKET_ERROR){
			fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
			free(csock);
			return;
		}
		printf("\nReceived bytes %d\nReceived string \"%s\"\n", recv_byte_cnt, recvbuf);
		createcategory(fp, recvbuf, csock);
	}
	if (x == 2){
		char *name = (char *)malloc(sizeof(char) * 10);
		char *specification = (char *)malloc(sizeof(char) * 20);
		char *pid = (char *)malloc(sizeof(char) * 3);
		char *token = (char *)malloc(sizeof(char) * 20);
		char s[2] = ",";
		display_categories(fp, csock);
		memset(recvbuf, '\0', sizeof(recvbuf));
		if ((recv_byte_cnt = recv(*csock, recvbuf, recvbuf_len, 0)) == SOCKET_ERROR){
			fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
			free(csock);
			return;
		}
		printf("\nReceived bytes %d\nReceived string \"%s\"\n", recv_byte_cnt, recvbuf);

		int p = atoi(recvbuf);
		display_persons(fp, p, csock);
		if ((recv_byte_cnt = recv(*csock, recvbuf, recvbuf_len, 0)) == SOCKET_ERROR){
			fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
			free(csock);
			return;
		}
		printf("\nReceived bytes %d\nReceived string \"%s\"\n", recv_byte_cnt, recvbuf);
		token = strtok(recvbuf, s);
		while (token != NULL)
		{
			printf(" %s\n", token);
			if (count == 1)
				strcpy(name, token);
			if (count == 2)
				strcpy(specification, token);
			if (count == 3)
				strcpy(pid, token);
			token = strtok(NULL, s);
			count++;
		}
		createperson(fp, p, atoi(pid), name, specification, csock);
	}
	if (x == 3){
		char *name = (char *)malloc(sizeof(char) * 10);
		char *d = (char *)malloc(sizeof(char) * 3);
		char *m = (char *)malloc(sizeof(char) * 3);
		char *y = (char *)malloc(sizeof(char) * 5);
		char *token = (char *)malloc(sizeof(char) * 20);
		char s[2] = ",";
		count = 1;
		display_categories(fp, csock);
		memset(recvbuf, '\0', sizeof(recvbuf));
		if ((recv_byte_cnt = recv(*csock, recvbuf, recvbuf_len, 0)) == SOCKET_ERROR){
			fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
			free(csock);
			return;
		}
		printf("\nReceived bytes %d\nReceived string \"%s\"\n", recv_byte_cnt, recvbuf);

		int c = atoi(recvbuf);
		display_persons(fp, c, csock);
		if ((recv_byte_cnt = recv(*csock, recvbuf, recvbuf_len, 0)) == SOCKET_ERROR){
			fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
			free(csock);
			return;
		}
		printf("\nReceived bytes %d\nReceived string \"%s\"\n", recv_byte_cnt, recvbuf);

		int  p= atoi(recvbuf);
		if ((recv_byte_cnt = recv(*csock, recvbuf, recvbuf_len, 0)) == SOCKET_ERROR){
			fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
			free(csock);
			return;
		}
		printf("\nReceived bytes %d\nReceived string \"%s\"\n", recv_byte_cnt, recvbuf);

		display_appointments(fp, c, p, csock);
		token = strtok(recvbuf, s);
		while (token != NULL)
		{
			printf("\n in while loop %d", count);
			printf(" %s\n", token);
			if (count == 1)
				strcpy(name, token);
			if (count == 2)
				strcpy(d, token);
			if (count == 3)
				strcpy(m, token);
			if (count == 4)
				strcpy(y, token);
			token = strtok(NULL, s);
			count++;
		}
		getappointment(fp, c, p, name, atoi(d), atoi(m), atoi(y), csock);
	}
	fclose(fp);
}

void replyto_client(char *buf, int *csock) {
	int bytecount;
	
	if((bytecount = send(*csock, buf, strlen(buf)+1, 0))==SOCKET_ERROR){
		fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
		free (csock);
	}
	printf("replied to client: %s\n",buf);
}

DWORD WINAPI SocketHandler(void* lp){
    int *csock = (int*)lp;

	char recvbuf[1024];
	int recvbuf_len = 1024;
	int recv_byte_cnt;

	memset(recvbuf, 0, recvbuf_len);
	if((recv_byte_cnt = recv(*csock, recvbuf, recvbuf_len, 0))==SOCKET_ERROR){
		fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
		free (csock);
		return 0;
	}

	printf("Received bytes in sockethandler %d\nReceived string \"%s\"\n", recv_byte_cnt, recvbuf);

	process_input(recvbuf, recv_byte_cnt, csock);

    return 0;
}