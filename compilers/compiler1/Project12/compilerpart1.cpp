//compiler part 1

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

struct variables{
	char var;
	int val;
	struct variables *next;
};

struct variables *insert(struct variables *head, char var, int val, FILE *fpp){

	struct variables *temp = (struct variables *)malloc(sizeof(struct variables));
	temp->var = var;
	temp->val = val;
	temp->next = NULL;
	fprintf(fpp, "DATA %c\n", temp->var);

	printf("\nin insert %c = %d\n", temp->var, temp->val);
	if (head == NULL)
		return temp;
	struct variables *temp1 = head;
	while (temp1->next != NULL){
		printf("\nin insert %c = %d\n", temp1->var, temp1->val);
		temp1 = temp1->next;
	}
	temp1->next = temp;
	return head;
}

struct variables *update(struct variables *head, char var, int val){

	struct variables *temp = head;
	while (temp->next != NULL){
		if (temp->var == var)
			temp->val = val;
		temp = temp->next;
	}
	return head;
}

int isinlist(struct variables *head, char var){

	struct variables *temp = head;
	if (temp == NULL)
		return 0;
	while (temp!= NULL){
		if (temp->var == var)
			return 1;
		temp = temp->next;
	}
	return 0;
}

int findval(struct variables *head, char var){

	if (head == NULL)
		return -999;
	struct variables *temp = head;
	while (temp != NULL){
		if (temp->var == var)
			return temp->val;
		temp = temp->next;
	}
	return -999;
}

void main(){

	int datatype, temp, identifier;
	char *command = (char *)malloc(sizeof(char) * 10);
	char var, var_val;
	struct variables *head = NULL;
	FILE *fp = fopen("input.txt", "r");
	FILE *fpp = fopen("asmcode.txt", "w");

	while (!feof(fp)){
		fscanf(fp, "%d", &datatype);
		char *buf = (char *)malloc(sizeof(char) * 255);
		memset(buf, '\0', sizeof(buf));

		if (datatype == 1){
			fscanf(fp, " %s %c\n", command, &var);
			printf("\ntype = %d, %s, %c\n", datatype, command, var);

			if (!strcmp(command, "SCAN")){
				fflush(stdin);
				scanf("%d", &temp);
				if (isinlist(head, var))
					head = update(head, var, temp);
				else
					head = insert(head, var, temp, fpp);
				

			}
			if (!strcmp(command, "PRINT")){
				fflush(stdin);
				temp = findval(head, var);
				printf("\nvalue of %c = %d\n", var, temp);
			}
		}
		if (datatype == 2){
			char var1, op, res = 0;
			char computation_val;

			fscanf(fp, " %c = %c %c %d\n", &var, &var1, &op, &temp);
			printf("type = %d, %c, %c, %c, %d\n", datatype, var, var1, op, temp);

			int v = findval(head, var1);
			if (op == '+'){
				if (v == -999)
					printf("variable %c not declared\n", var1);
				res = temp + v;
				if (!isinlist(head, var))
					head = insert(head, var, res, fpp);
				else
					head = update(head, var, res);
			}
			if (op == '-'){
				if (v == -999)
					printf("variable %c not declared\n", var1);
				res = v - temp;
				if (!isinlist(head, var))
					head = insert(head, var, res, fpp);
				else
					head = update(head, var, res);
			}
			if (op == '*'){
				if (v == -999)
					printf("variable %c not declared\n", var1);
				res = temp * v;
				if (!isinlist(head, var))
					head = insert(head, var, res, fpp);
				else
					head = update(head, var, res);
			}
			if (op == '/'){
				if (v == -999)
					printf("variable %c not declared\n", var1);
				res = v / temp;
				if (!isinlist(head, var))
					head = insert(head, var, res, fpp);
				else
					head = update(head, var, res);
			}
		}
		if (datatype == 3){
			char var1, op, res = 0;
			char computation_val;

			fscanf(fp, " %c = %d %c %c\n", &var, &temp, &op, &var1);
			printf("type = %d, %c, %c, %c, %d\n", datatype, var, var1, op, temp);

			int v = findval(head, var1);
			if (op == '+'){
				if (v == -999)
					printf("variable %c not declared\n", var1);
				res = temp + v;
				if (isinlist(head, var))
					head = update(head, var, res);
				else 
					head = insert(head, var, res, fpp);
			}
			if (op == '-'){
				if (v == -999)
					printf("variable %c not declared\n", var1);
				res = temp - v;
				if (isinlist(head, var))
					head = update(head, var, res);
				else
					head = insert(head, var, res, fpp);
			}
			if (op == '*'){
				if (v == -999)
					printf("variable %c not declared\n", var1);
				res = temp * v;
				if (isinlist(head, var))
					head = update(head, var, res);
				else
					head = insert(head, var, res, fpp);
			}
			if (op == '/'){
				if (v == -999)
					printf("variable %c not declared\n", var1);
				res = temp / v;
				if (isinlist(head, var))
					head = update(head, var, res);
				else
					head = insert(head, var, res, fpp);
			}
			
		}
		if (datatype == 4){
			char var1, var2, op, res = 0;
			char computation_val;

			fscanf(fp, " %c = %c %c %c\n", &var, &var2, &op, &var1);
			printf("type = %d, %c, %c, %c, %c\n", datatype, var, var1, var2, op);

			int v = findval(head, var1);
			int v1 = findval(head, var2);
			if (op == '+'){
				if (v == -999)
					printf("variable %c not declared\n", var1);
				res = v1 + v;
				if (isinlist(head, var))
					head = update(head, var, res);
				else
					head = insert(head, var, res, fpp);
			}
			if (op == '-'){
				if (v == -999)
					printf("variable %c not declared\n", var1);
				res = v1 - v;
				if (isinlist(head, var))
					head = update(head, var, res);
				else
					head = insert(head, var, res, fpp);
			}
			if (op == '*'){
				if (v == -999)
					printf("variable %c not declared\n", var1);
				res = v1 * v;
				if (isinlist(head, var1))
					head = update(head, var1, res);
				else
					head = insert(head, var1, res, fpp);
			}
			if (op == '/'){
				if (v == -999)
					printf("variable %c not declared\n", var1);
				res = v1 / v;
				if (isinlist(head, var))
					head = update(head, var, res);
				else
					head = insert(head, var, res, fpp);
			}
			
		}
	}
	while (head != NULL){
		printf("%c = %d\n", head->var, head->val);
		head = head->next;
	}
	fclose(fp);
	fclose(fpp);
	_getch();

}