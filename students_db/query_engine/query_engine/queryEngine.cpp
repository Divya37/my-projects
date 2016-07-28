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

int min(int *arr, int size){
	int m = 999;
	for (int i = 0; i < size; i++){
		if (arr[i] < m)
			m = arr[i];
	}
	return m;
}

int max(int *arr, int size){
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

void process_nested_query(char *at1, char *at2, char *val, char *at3, char *val1, char subjects[6][15]){
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
						printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
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
						printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
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
						printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
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
						printf("\n%s - %s - %s - %d", st.marks[id]);

					}
				}

			}
			if (!strcmp(at2, "total")){
				while (!feof(fp)){
					memset(&st, '\0', sizeof(st));
					fread(&st, sizeof(st), 1, fp);

					if (st.total == atoi(val) && !strcmp(st.location, val1))
						printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
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
						printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
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
						printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
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
						printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
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
						printf("\n%s - %s - %s - %d", st.marks[id]);

					}
				}


				if (!strcmp(at2, "total")){
					while (!feof(fp)){
						memset(&st, '\0', sizeof(st));
						fread(&st, sizeof(st), 1, fp);

						if (st.total == atoi(val) && !strcmp(st.gender, val1))
							printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
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
							printf("\n%s - %s - %s - %d", st.name, st.gender, st.location, min(st.marks, 6));
							break;
						}
						else if (flag == 2)
						{
							printf("\n%s - %s - %s - %d", st.name, st.gender, st.location, max(st.marks, 6));
							break;
						}
						else if (flag == 3)
						{
							printf("\n%s - %s - %s - %d", st.name, st.gender, st.location, avg(st.marks, 6));
							break;
						}
						else if (flag == 4)
						{
							printf("\n%s - %s - %s - %d", st.name, st.gender, st.location, total(st.marks, 6));
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
					printf("\n%s - %s - %s - %d", st.name, st.gender, st.location, min(a, i));
					//break;
				}
				else if (flag == 2)
				{
					printf("\n%s - %s - %s - %d", st.name, st.gender, st.location, max(a, i));
					//break;
				}
				else if (flag == 3)
				{
					printf("\n%s - %s - %s - %d", st.name, st.gender, st.location, avg(a, i));
					//break;
				}
				else if (flag == 4)
				{
					printf("\n%s - %s - %s - %d", st.name, st.gender, st.location, total(a, i));
					//break;
				}

			}
		}

	}

	fclose(fp);
}


void process_query(char *at1, char *at2, char *val, char subjects[6][15])
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
					printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
						st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);
				}
			}
		}
		if(!strcmp(at2, "location")){
			while (!feof(fp)){
				memset(&st, '\0', sizeof(st));
				fread(&st, sizeof(st), 1, fp);
				if (!strcmp(st.location, val))
				{
					printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
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
					printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
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
					printf("\n%s - %s - %s - %d", st.marks[id]);
					
				}
			}
			
		}
		if (!strcmp(at2, "total")){
			while (!feof(fp)){
				memset(&st, '\0', sizeof(st));
				fread(&st, sizeof(st), 1, fp);
			
				if (st.total == atoi(val))
					printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
					st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);
			}
		}
	}
	fclose(fp);
	
}

void main(){
	
	FILE *fp = fopen("marks.txt", "r");
	FILE *fp1 = fopen("thisbin.bin", "wb");

	struct students st;

	char subjects[6][15];
	fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", subjects[0], subjects[1], subjects[2], subjects[3], subjects[4], subjects[5]);
	fseek(fp1, 0, SEEK_SET);
	printf("\n%s,\n%s,\n%s,\n%s,\n%s,\n%s", subjects[0], subjects[1], subjects[2], subjects[3], subjects[4], subjects[5]);
	
	while (!feof(fp)){
		memset(&st, '\0', sizeof(st));
		fscanf(fp, "%[^,], %[^,], %[^\n]\n", st.name, st.gender, st.location);
		fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &st.marks[0], &st.marks[1], &st.marks[2], &st.marks[3], &st.marks[4], &st.marks[5]);
		st.total = st.marks[0] + st.marks[1] + st.marks[2] + st.marks[3] + st.marks[4] + st.marks[5];
		printf("\n%s - %s - %s - %d - %d - %d- %d - %d - %d", st.name, st.gender, st.location, st.marks[0],
			st.marks[1], st.marks[2], st.marks[3], st.marks[4], st.marks[5]);

		fwrite(&st, sizeof(st), 1, fp1);
	}
	fclose(fp1);
	fclose(fp);
	char *attr = (char *)malloc(sizeof(char) * 20);
	char *attr1 = (char *)malloc(sizeof(char) * 20);
	char *attr3 = (char *)malloc(sizeof(char) * 20);
	char *val1 = (char *)malloc(sizeof(char) * 20);
	char *val = (char *)malloc(sizeof(char) * 20);

	int opt;
	while (true){
		//printf("\nenter queries : \n");
		printf("\n\n\n1.enter query to fetch(select <attr1> where <attr2> = <value>)\n");
		printf("2.enter nested query (select <attr1> where <attr2> = <val> when <attr3> = <val>)\n3.exit\n");
		printf("enter choice :");
		fflush(stdin);
		scanf("%d", &opt);
		
		if (opt == 1){
			printf("\nenter query : \n");
			fflush(stdin);
			scanf("select %s where %s = %s", attr, attr1, val);
			printf("\n%s %s %s", attr, attr1, val);
			process_query(attr, attr1, val, subjects);

		}
		else if (opt == 2){
			printf("\nenter query : \n");
			fflush(stdin);
			scanf("select %s where %s = %s when %s = %s", attr, attr1, val, attr3, val1);
			printf("\n%s %s %s %s %s", attr, attr1, val, attr3, val1);
			process_nested_query(attr, attr1, val, attr3, val1, subjects);

		}
		else{
			break;
		}
	}
}