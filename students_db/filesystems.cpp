#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct reply_info{
	long reply_offset;
	long bit_position;
}reply;

typedef struct message_info{
	long msg_offset;
	long bit_position;
	int number_of_reply;
	reply** rep;
}message;


typedef struct category_info{
	long category_offset;
	int number_of_messages;
	message** mes;
}category;

typedef struct user_info{
	long user_offset;
	int number_of_categories;
	category** cat;
}user;

typedef struct track_users{
	int count;
	user** users;
}track;

int length(char* name){
	int i = 0;
	for(i=0;name[i]!='\0';i++);
	return i;
}

void create_new_user(track* root, FILE* fp){
	char name[20];
	if (root->count < 20){
		printf("Enter user name\n");
		scanf("%s", name);
		int off = (65536) + 8 + 20 * root->count;//didnt properly understand
		fseek(fp, off, SEEK_SET);
		fwrite(name, length(name)+1, 1, fp);
		root->users[root->count]->user_offset = off;
		root->users[root->count]->number_of_categories = 0;
		root->count += 1;
	}
	else{
		printf("Limit exceeded\n");
	}

}



void create_category_for_user(track* root, int index, FILE* fp){
	char name[20];
	if (index < root->count){
		char buff[20];
		int offset = (65536) + 8 + (20 * 20);
		offset += ((20*5*index) + (20*root->users[index]->number_of_categories));
		char c[20];
		printf("Enter category\n");
		scanf("%s", c);
		fseek(fp, offset, SEEK_SET);
		fwrite(c, length(c)+1, 1, fp);

		root->users[index]->cat[root->users[index]->number_of_categories]->number_of_messages = 0;
		root->users[index]->cat[root->users[index]->number_of_categories]->category_offset = offset;
		root->users[index]->number_of_categories++;
	}
	else{
		printf("invalid input\n");
	}

}

int check_bit_vector(FILE* fp){
	int i = 0;
	for (i = 0; i < 65530; i++){
		char ch;
		fseek(fp, i, SEEK_SET);
		fread(&ch, 1, 1, fp);
		if (ch != '1'){
			fseek(fp, i, SEEK_SET);
			ch = '1';
			fwrite(&ch, 1, 1, fp);
			return i;
		}
	}

}

void create_message(track* root, int index, FILE* fp){
	char name[20];
	if (index < root->count){
		for (int i = 0; i < root->users[index]->number_of_categories; i++){
			char buff[20];
			int offset = root->users[index]->cat[i]->category_offset;
			fseek(fp, offset, SEEK_SET);
			fread(buff, 20, 1, fp);
			printf("%d . %s\n", i, buff);
		}
		int index1;
		scanf("%d", &index1);
		fseek(fp, 0, SEEK_SET);
		int pos = check_bit_vector(fp);
		int offset = (pos * 128) + (67944);
		char c[20];
		printf("Enter message\n");
		scanf("%s", c);
		fseek(fp, offset, SEEK_SET);
		fwrite(c, length(c) + 1, 1, fp);
		root->users[index]->cat[index1]->mes[root->users[index]->cat[index1]->number_of_messages]->msg_offset = offset;
		root->users[index]->cat[index1]->mes[root->users[index]->cat[index1]->number_of_messages]->bit_position = pos;
		root->users[index]->cat[index1]->mes[root->users[index]->cat[index1]->number_of_messages]->number_of_reply = 0;
		root->users[index]->cat[index1]->number_of_messages++;
	}
	else{
		printf("invalid input\n");
	}
}

void send_reply(track* root, int index, FILE* fp){
	char name[20];
	if (index < root->count){
		for (int i = 0; i < root->users[index]->number_of_categories; i++){
			char buff[20];
			int offset = root->users[index]->cat[i]->category_offset;
			fseek(fp, offset, SEEK_SET);
			fread(buff, 20, 1, fp);
			printf("%d . %s\n", i, buff);
		}
		int index1;
		scanf("%d", &index1);
		for (int i = 0; i < root->users[index]->cat[index1]->number_of_messages; i++){
			if (root->users[index]->cat[index1]->mes[i]->msg_offset != -1){
				char buff[128];
				int offset = root->users[index]->cat[index1]->mes[i]->msg_offset;
				fseek(fp, offset, SEEK_SET);
				fread(buff, 128, 1, fp);
				printf("%d . %s\n", i, buff);
			}
		}
		int index2;
		scanf("%d", &index2);
		fseek(fp, 0, SEEK_SET);
		int pos = check_bit_vector(fp);
		int offset = (pos * 128) + (67944);
		char c[128];
		printf("Enter reply\n");
		scanf("%s", c);
		fseek(fp, offset, SEEK_SET);
		fwrite(c, length(c) + 1, 1, fp);
		root->users[index]->cat[index1]->mes[root->users[index]->cat[index1]->number_of_messages]->rep[root->users[index]->cat[index1]->mes[root->users[index]->cat[index1]->number_of_messages]->number_of_reply]->reply_offset = offset;
		root->users[index]->cat[index1]->mes[root->users[index]->cat[index1]->number_of_messages]->rep[root->users[index]->cat[index1]->mes[root->users[index]->cat[index1]->number_of_messages]->number_of_reply]->bit_position = pos;
		root->users[index]->cat[index1]->mes[root->users[index]->cat[index1]->number_of_messages]->number_of_reply++;
	}
	else{
		printf("invalid input\n");
	}
}

void delete_message(track* root, int index, FILE* fp){

	if (index < root->count){
		for (int i = 0; i < root->users[index]->number_of_categories; i++){
			char buff[20];
			int offset = root->users[index]->cat[i]->category_offset;
			fseek(fp, offset, SEEK_SET);
			fread(buff, 20, 1, fp);
			printf("%d . %s\n", i, buff);
		}
		int index1;
		scanf("%d", &index1);
		for (int i = 0; i < root->users[index]->cat[index1]->number_of_messages; i++){
			char buff[128];
			int offset = root->users[index]->cat[index1]->mes[i]->msg_offset;
			fseek(fp, offset, SEEK_SET);
			fread(buff, 128, 1, fp);
			printf("%d . %s\n", i, buff);
		}
		int index2;
		char val = '0';
		scanf("%d", &index2);
		int pos = root->users[index]->cat[index1]->mes[index2]->bit_position;
		fseek(fp, pos, SEEK_SET);
		fwrite(&val, 1, 1, fp);
		for (int k = 0; k < root->users[index]->cat[index1]->mes[index2]->number_of_reply; k++){
			int pos = root->users[index]->cat[index1]->mes[index2]->rep[k]->bit_position;
			fseek(fp, pos, SEEK_SET);
			fwrite(&val, 1, 1, fp);
		}
		root->users[index]->cat[index1]->mes[index2]->msg_offset = -1;
	}
	else{
		printf("invalid input\n");
	}
}

int main(){

	int i, j;
	FILE* fp = fopen("sample2.bin", "wb+");
	if (fp){
		//create memory
		track* root = (track*)malloc(sizeof(track));
		root->users = (user**)malloc(sizeof(user*)* 20);
		for (int k = 0; k < 20; k++){
			root->users[k] = (user*)malloc(sizeof(user));
		}
		root->count = 0;
		for (i = 0; i < 20; i++){
			root->users[i]->cat = (category**)malloc(sizeof(category*)* 5);
			long k;
			for (k = 0; k < 5; k++){
				root->users[i]->cat[k] = (category*)malloc(sizeof(category));
			}
			root->users[i]->number_of_categories = 0;

			for (j = 0; j < 5; j++){
				root->users[i]->cat[j]->mes = (message**)malloc(sizeof(message*)* 10);
				for (k = 0; k < 10; k++){
					root->users[i]->cat[j]->mes[k] = (message*)malloc(sizeof(message));
					root->users[i]->cat[j]->mes[k]->rep = (reply**)malloc(sizeof(reply*)* 10);
					long l= 0;
					for (l = 0; l < 10; l++){
						root->users[i]->cat[j]->mes[k]->rep[l] = (reply*)malloc(sizeof(reply));
					}
					root->users[i]->cat[j]->mes[k]->number_of_reply = 0;
				}
			}
		}

	
		char ch = '\0';
		char check = '1';
		int u, loginflag=0;
		while (check == '1'){
			if(loginflag == 0){
				printf("1.Create user\n 2.login");
				fflush(stdin);
				scanf("%c", &ch);
				if (ch == '1'){
						create_new_user(root, fp);
				}
				for (i = 0; i < root->count; i++){
					char buff[20];
					int offset = root->users[i]->user_offset;	
					fseek(fp, offset, SEEK_SET);
					fread(buff, 20, 1, fp);
					printf("%d . %s\n", i, buff);
				}
				if (ch == '2'){
					loginflag=1;
					printf("\n login as :");
					fflush(stdin);
					scanf("%d",&u);
				}
			}
			if(loginflag == 1){
				printf("\n2.Create category for existent user\n3.Create message\n4.Send reply\n5.Delete message\n");
				fflush(stdin);
				scanf("%c", &ch);				
				
				if (ch != '\0' && ch != '\n'){
					if (ch == '2'){
						create_category_for_user(root, u, fp);
					}
					if (ch == '3'){
						create_message(root, u, fp);
					}
					if (ch == '4'){
						send_reply(root, u, fp);
					}
					if (ch == '5'){
						delete_message(root, u, fp);
					}
					
				}
			}
			printf("1.continue \n2.exit");
			fflush(stdin);
			scanf("%c", &check);
		}
		

	}

	getch();
	return 0;

}