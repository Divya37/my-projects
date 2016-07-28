#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#pragma warning(disable:4996)

struct nonleafpage{
	int type;
	int offset[3];
	int keys[2];
	char unused[44];
};

struct students{
	int rollno;
	char *name;
	char *college;
};

char* int_to_string(int num){
	char* res = (char*)malloc(sizeof(char) * 15);
	int ind = 0;
	while (num > 0){
		res[ind++] = (num % 10) + '0';
		num = num / 10;
	}
	res[ind] = '\0';
	return strrev(res);
}

void main(){

	struct students records;
	char *record, *line=(char *)malloc(sizeof(char)*1024);
	int ind = 0;
	FILE* fp = fopen("details.csv", "r");
	FILE* fp1 = fopen("st.bin", "wb");

	while (fgets(line, 1024, fp) != NULL)
	{
		memset(&records, 0, sizeof(records));

		record = strtok(line, ",");
		records.rollno = atoi(record);
		record = strtok(NULL, ",");
		records.name = strdup(record);
		record = strtok(NULL, ",");
		records.college = strdup(record);
		record = strtok(NULL, ",");

		fwrite(&records.rollno, 4, 1, fp1);
		fwrite(records.name, 28, 1, fp1);
		fwrite(records.college, 32, 1, fp1);
		printf("\n%d - %s - %s", records.rollno, records.name, records.college);

		memset(line, 0, sizeof(line));		
		ind++;
	}
	fclose(fp1);
	fclose(fp);

	int id;
	printf("\n enter student id to fetch :");
	scanf("%d", &id);

	fp1 = fopen("st.bin", "rb");

	if (fp1 == NULL){
		printf("file open error");
		getchar();
		return;
	}
	int idion;
	int flag = 0;

	for (int i = 0; i < ind; i++){
		fseek(fp1, (i * 64)+4, SEEK_SET);
		fread(&idion, 4, 1, fp1);
		printf("%d", idion);

		if (id == idion){
			//printf("\nits me");
			char* name = (char*)malloc(sizeof(char) * 28);
			char* college = (char*)malloc(sizeof(char) * 32);

			fread(name, 1, 28, fp1);
			fread(college, 1, 32, fp1);

			printf("Name : %s\n", name);
			printf("College : %s\n", college);

			flag = 1;
			break;

		}
	}
	getch();
}