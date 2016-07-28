#include "stdafx.h"
#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

struct students{
	char name[20];
	char gender[8];
	char location[10];
	int marks[6];
	int total;
};

int find_sub_id(char subjects[6][15], char *val){
	for (int i = 0; i < 6; i++){
		if (!strcmp(subjects[i], val))
			return i;
	}
	return -1;
}

int mini(int *arr, int size){
	int m = 999;
	for (int i = 0; i < size; i++){
		if (arr[i] < m)
			m = arr[i];
	}
	return m;
}

int maxi(int *arr, int size){
	int m = -1;
	for (int i = 0; i < size; i++){
		if (arr[i] > m)
			m = arr[i];
	}
	return m;
}

int avg(int *arr, int size){
	int a = 0;
	for (int i = 0; i < size; i++)
		a += arr[i];
	a = a / size;
	return a;
}

int total(int *arr, int size){
	int a = 0;
	for (int i = 0; i < size; i++)
		a += arr[i];
	return a;
}

void process_nested_query(FILE *f, char *at1, char *at2, char *val, char *at3, char *val1, char subjects[6][15]){
	FILE *fp = fopen("thisbin.bin", "rb");
	fseek(fp, 0, SEEK_SET);
	struct students st;
	memset(&st, '\0', sizeof(st));

	if (!strcmp(at1, "*")){
		if (!strcmp(at3, "location")){
			if (!strcmp(at2, "name")){
				while (!feof(fp)){
					memset(&st, '\0', sizeof(st));
					fread(&st, sizeof(st), 1, fp);
					if (!strcmp(st.name, val) && !strcmp(st.location, val1))
					{
						fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
							st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);
					}
				}
			}
			if (!strcmp(at2, "location")){
				while (!feof(fp)){
					memset(&st, '\0', sizeof(st));
					fread(&st, sizeof(st), 1, fp);
					if (!strcmp(st.location, val) && !strcmp(st.location, val1))
					{
						fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
							st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);
					}
				}
			}
			if (!strcmp(at2, "gender")){
				while (!feof(fp)){
					memset(&st, '\0', sizeof(st));
					fread(&st, sizeof(st), 1, fp);
					if (!strcmp(st.gender, val) && !strcmp(st.location, val1))
					{
						fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
							st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);

					}
				}
			}
			if (!strcmp(at2, "marks")){
				while (!feof(fp)){
					memset(&st, '\0', sizeof(st));
					fread(&st, sizeof(st), 1, fp);
					int id = find_sub_id(subjects, val);
					if (id == -1)
					{
						printf("subject no found");
						break;
					}
					else
					{
						fprintf(f, "\n%s - %s - %s - %d", st.marks[id]);

					}
				}

			}
			if (!strcmp(at2, "total")){
				while (!feof(fp)){
					memset(&st, '\0', sizeof(st));
					fread(&st, sizeof(st), 1, fp);

					if (st.total == atoi(val) && !strcmp(st.location, val1))
						fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
						st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);
				}
			}
		}
		else if (!strcmp(at3, "gender")){
			if (!strcmp(at2, "name")){
				while (!feof(fp)){
					memset(&st, '\0', sizeof(st));
					fread(&st, sizeof(st), 1, fp);
					if (!strcmp(st.name, val) && !strcmp(st.gender, val1))
					{
						fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
							st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);
					}
				}
			}
			if (!strcmp(at2, "location")){
				while (!feof(fp)){
					memset(&st, '\0', sizeof(st));
					fread(&st, sizeof(st), 1, fp);
					if (!strcmp(st.location, val) && !strcmp(st.gender, val1))
					{
						fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
							st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);
					}
				}
			}
			if (!strcmp(at2, "gender")){
				while (!feof(fp)){
					memset(&st, '\0', sizeof(st));
					fread(&st, sizeof(st), 1, fp);
					if (!strcmp(st.gender, val) && !strcmp(st.gender, val1))
					{
						fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
							st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);

					}
				}
			}
			if (!strcmp(at2, "marks")){
				int flag = 0;
				while (!feof(fp)){
					memset(&st, '\0', sizeof(st));
					fread(&st, sizeof(st), 1, fp);

					int id = find_sub_id(subjects, val);
					if (id == -1)
					{
						printf("subject no found");
						break;
					}
					else
					{
						fprintf(f, "\n%s - %s - %s - %d", st.marks[id]);

					}
				}


				if (!strcmp(at2, "total")){
					while (!feof(fp)){
						memset(&st, '\0', sizeof(st));
						fread(&st, sizeof(st), 1, fp);

						if (st.total == atoi(val) && !strcmp(st.gender, val1))
							fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
							st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);
					}
				}

			}
		}
		else if (!strcmp(at3, "name")){
			if (!strcmp(at2, "marks")){
				int flag = 0;
				if (!strcmp(val, "min"))
					flag = 1;
				else if (!strcmp(val, "max"))
					flag = 2;
				else if (!strcmp(val, "avg"))
					flag = 3;
				else if (!strcmp(val, "total"))
					flag = 4;
				while (!feof(fp)){
					memset(&st, '\0', sizeof(st));
					fread(&st, sizeof(st), 1, fp);
					if (!strcmp(st.name, val1)){
						if (flag == 1)
						{
							fprintf(f, "\n%s - %s - %s - %d", st.name, st.gender, st.location, mini(st.marks, 6));
							break;
						}
						else if (flag == 2)
						{
							fprintf(f, "\n%s - %s - %s - %d", st.name, st.gender, st.location, maxi(st.marks, 6));
							break;
						}
						else if (flag == 3)
						{
							fprintf(f, "\n%s - %s - %s - %d", st.name, st.gender, st.location, avg(st.marks, 6));
							break;
						}
						else if (flag == 4)
						{
							fprintf(f, "\n%s - %s - %s - %d", st.name, st.gender, st.location, total(st.marks, 6));
							break;
						}
					}


				}
			}

		}
		else if (!strcmp(at3, "subject")){
			if (!strcmp(at2, "marks")){
				int flag = 0;
				if (!strcmp(val, "min"))
					flag = 1;
				else if (!strcmp(val, "max"))
					flag = 2;
				else if (!strcmp(val, "avg"))
					flag = 3;
				else if (!strcmp(val, "total"))
					flag = 4;
				int j = find_sub_id(subjects, val1);
				int a[1000], i = 0;
				while (!feof(fp)){
					memset(&st, '\0', sizeof(st));
					fread(&st, sizeof(st), 1, fp);
					a[i++] = st.marks[j];

				}
				if (flag == 1)
				{
					fprintf(f, "\n%s - %s - %s - %d", st.name, st.gender, st.location, mini(a, i));
					//break;
				}
				else if (flag == 2)
				{
					fprintf(f, "\n%s - %s - %s - %d", st.name, st.gender, st.location, maxi(a, i));
					//break;
				}
				else if (flag == 3)
				{
					fprintf(f, "\n%s - %s - %s - %d", st.name, st.gender, st.location, avg(a, i));
					//break;
				}
				else if (flag == 4)
				{
					fprintf(f, "\n%s - %s - %s - %d", st.name, st.gender, st.location, total(a, i));
					//break;
				}

			}
		}

	}
	fclose(f);
	fclose(fp);
}


void process_query(FILE *f, char *at1, char *at2, char *val, char subjects[6][15])
{
	FILE *fp = fopen("thisbin.bin", "rb");
	fseek(fp, 0, SEEK_SET);
	struct students st;
	memset(&st, '\0', sizeof(st));

	if (!strcmp(at1, "*")){
		if (!strcmp(at2, "name")){
			while (!feof(fp)){
				memset(&st, '\0', sizeof(st));
				fread(&st, sizeof(st), 1, fp);
				if (!strcmp(st.name, val))
				{
					fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
						st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);
				}
			}
		}
		if (!strcmp(at2, "location")){
			while (!feof(fp)){
				memset(&st, '\0', sizeof(st));
				fread(&st, sizeof(st), 1, fp);
				if (!strcmp(st.location, val))
				{
					fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
						st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);
				}
			}
		}
		if (!strcmp(at2, "gender")){
			while (!feof(fp)){
				memset(&st, '\0', sizeof(st));
				fread(&st, sizeof(st), 1, fp);
				if (!strcmp(st.gender, val))
				{
					fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
						st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);

				}
			}
		}
		if (!strcmp(at2, "marks")){
			while (!feof(fp)){
				memset(&st, '\0', sizeof(st));
				fread(&st, sizeof(st), 1, fp);
				int id = find_sub_id(subjects, val);
				if (id == -1)
				{
					printf("subject no found");
					break;
				}
				else
				{
					fprintf(f, "\n%s - %s - %s - %d", st.marks[id]);

				}
			}

		}
		if (!strcmp(at2, "total")){
			while (!feof(fp)){
				memset(&st, '\0', sizeof(st));
				fread(&st, sizeof(st), 1, fp);

				if (st.total == atoi(val))
					fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
					st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);
			}
		}
	}
	fclose(fp);
	fclose(f);

}


struct node
{
	char msg[128];
	int msg_id;
	node *next;
}*flist, *alist, *printid;

struct bufserv{

	int userId;
	int forumId;
	int msgId;
	int commentId;
	int choice;
	char *forumname;
	char msg[128];
}buf1;

bool flag = true;
int mid = 0;
int count1 = 0;
char *Data[100];
int count = 1;
int values[100];
DWORD WINAPI SocketHandler(void*);
void replyto_client(char *buf, int *csock);

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


void process_input(char *recvbuf, int recv_buf_cnt, int* csock)
{
	char replybuf[1024] = { '\0' };
	printf("%s", recvbuf);
	printf("\nenter the reply : ");
	gets(replybuf);
	replyto_client(replybuf, csock);
	//replybuf[0] = '\0';
}

void replyto_client(char *buf, int *csock) {
	int bytecount;

	if ((bytecount = send(*csock, buf, strlen(buf) + 1, 0)) == SOCKET_ERROR){
		fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
		free(csock);
	}
	printf("replied to client: %s\n", buf);
}

DWORD WINAPI SocketHandler(void* lp){
	int *csock = (int*)lp;

	char recvbuf[1024];
	int recvbuf_len = 1024;
	int recv_byte_cnt;

	memset(recvbuf, 0, recvbuf_len);
	if ((recv_byte_cnt = recv(*csock, recvbuf, recvbuf_len, 0)) == SOCKET_ERROR){
		fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
		free(csock);
		return 0;
	}
	printf("Received bytes %d\nReceived string \"%s\"\n", recv_byte_cnt, recvbuf);
	
	FILE *fp = fopen("marks.txt", "r");
	FILE *fp1 = fopen("thisbin.bin", "wb");
	FILE *f = fopen("C:\\Users\\Divya\\Desktop\\client server\\client program\\socket_client\\output.txt", "w");
	struct students st;
	int opt;
	char attr1[20], attr2[20], attr3[20], val1[20], val2[20];

	char subjects[6][15];
	fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", subjects[0], subjects[1], subjects[2], subjects[3], subjects[4], subjects[5]);
	fseek(fp1, 0, SEEK_SET);
	//fprintf(f, "\n%s,\n%s,\n%s,\n%s,\n%s,\n%s", subjects[0], subjects[1], subjects[2], subjects[3], subjects[4], subjects[5]);

	while (!feof(fp)){
		memset(&st, '\0', sizeof(st));
		fscanf(fp, "%[^,], %[^,], %[^\n]\n", st.name, st.gender, st.location);
		fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &st.marks[0], &st.marks[1], &st.marks[2], &st.marks[3], &st.marks[4], &st.marks[5]);
		st.total = st.marks[0] + st.marks[1] + st.marks[2] + st.marks[3] + st.marks[4] + st.marks[5];
		//fprintf(f, "\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
			//st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);
		fwrite(&st, sizeof(st), 1, fp1);
	}
	fclose(fp);
	fclose(fp1);
	FILE *ff = fopen(recvbuf, "r");
	fseek(ff, 0, SEEK_SET);
	fscanf(ff, "%d,", &opt);
	if (opt == 1){
		fscanf(ff, "%[^,],%[^,],%s", attr1, attr2, val1);
		printf("%s,%s,%s", attr1, attr2, val1);
		process_query(f, attr1, attr2, val1, subjects);
	}
	else if (opt == 2){
		fscanf(ff, "%[^,],%[^,],%[^,],%s", attr1, attr2, val1, attr3, val2);
		printf("%s,%s,%s,%s", attr1, attr2, val1, attr3, val2);
		process_nested_query(f, attr1, attr2, val1, attr3, val2, subjects);
	}
	fclose(fp1);

	fclose(ff);
	getch();
	replyto_client("output.txt", csock);
	return 0;
}