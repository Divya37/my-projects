#include "stdafx.h"
#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
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
char path[100];
int index = 0;

int haspath(int *maze, int rows, int columns, int x1, int y1, int x2, int y2)
{
	if (x1 == x2 && y1 == y2)
		return 1;


	if (x1 + 1 < rows)
	{

		if (maze[(x1 + 1)*columns + y1] == 1)
		{
			maze[(x1 + 1)*columns + y1] = -1;
			if (haspath(maze, rows, columns, x1 + 1, y1, x2, y2))
			{
				//printf("\nx1=%d,y1=%d**********(recursive)", x1 + 1, y1);
				path[index++] = (x1 + 1) + 48;
				path[index++] = y1 + 48;
				return 1;
			}

		}
	}
	if (y1 + 1 < columns)
	{

		if (maze[x1*columns + y1 + 1] == 1)
		{
			maze[x1*columns + y1 + 1] = -1;

			if (haspath(maze, rows, columns, x1, y1 + 1, x2, y2))
			{
				//printf("\nx1=%d,y1=%d**********(recursive)", x1, y1 + 1);
				path[index++] = x1 + 48;
				path[index++] = (y1 + 1) + 48;
				return 1;
			}

		}
	}
	if (x1 - 1 >= 0)
	{

		if (maze[(x1 - 1)*columns + y1] == 1)
		{

			maze[(x1 - 1)*columns + y1] = -1;
			if (haspath(maze, rows, columns, x1 - 1, y1, x2, y2))
			{

				//printf("\nx1=%d,y1=%d**********(recursive)", x1 - 1, y1);
				path[index++] = (x1 - 1) + 48;;
				path[index++] = y1 + 48;
				return 1;
			}

		}
	}

	if (y1 - 1 >= 0)
	{


		if (maze[x1*columns + y1 - 1] == 1)
		{
			//printf("\nx1=%d,y1=%d**********(recursive)", x1, y1 - 1);
			maze[x1*columns + y1 - 1] = -1;
			if (haspath(maze, rows, columns, x1, y1 - 1, x2, y2))
			{
				//printf("\nx1=%d,y1=%d**********(recursive)", x1, y1 - 1);
				path[index++] = x1 + 48;
				path[index++] = (y1 - 1) + 48;
				return 1;
			}

		}
	}
	return 0;
}

int path_exists(int *maze, int rows, int columns, int x1, int y1, int x2, int y2)
{
	int *inp_maze, i, j;
	/*for (i = 0; i<rows; i++)
	{
		for (j = 0; j<columns; j++)
			printf("%d ", maze[(i*rows) + (j)]);
		printf("\n");
	}*/
	inp_maze = (int *)malloc(sizeof(int)*(rows*columns));
	for (int i = 0; i < (rows*columns); i++)
		inp_maze[i] = maze[i];

	if (rows <= 0 || columns <= 0 || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0 ||
		x1 >= rows || y1 >= columns || x2 >= rows || y2 >= columns)
		return 0;
	if (maze[x1*columns + y1] == 0 || maze[x2*columns + y2] == 0)
		return 0;
	return haspath(inp_maze, rows, columns, x1, y1, x2, y2);

}


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
	int ind = 0, ri = 0;
	int *maze = (int *)malloc(sizeof(int)*recv_buf_cnt);
	printf("%s", recvbuf);
	int i = 0;
	int rows = atoi(&recvbuf[i]);
	replybuf[ri++] = recvbuf[i];
	i = i + 2;
	int cols = atoi(&recvbuf[i]);
	replybuf[ri++] = recvbuf[i];
	i = i + 2;
	int x1 = atoi(&recvbuf[i]);
	replybuf[ri++] = recvbuf[i];
	i = i + 2;
	int y1 = atoi(&recvbuf[i]);
	replybuf[ri++] = recvbuf[i];
	i = i + 2;
	int x2 = atoi(&recvbuf[i]);
	replybuf[ri++] = recvbuf[i];
	i = i + 2;
	int y2 = atoi(&recvbuf[i]);
	replybuf[ri++] = recvbuf[i];
	i = i + 2;
	for (i=i; i < recv_buf_cnt; i++){		
		if (recvbuf[i] == ',' || recvbuf[i] == '\n')continue;
		maze[ind++] = atoi(&recvbuf[i]);
		replybuf[ri++] = recvbuf[i];
	}
	if (path_exists(maze,rows,cols,x1,y1,x2,y2))
		replyto_client(path, csock);
	else
		replyto_client("no path found", csock);
	
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

	process_input(recvbuf, recv_byte_cnt, csock);

	return 0;
}