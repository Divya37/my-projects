#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma warning(disable:4996)

struct students{
	int type;
	int rollno;
	char name[28];
	char college[28];
};

struct nonleaf{
	int type;
	int offset[3];
	int key[2];
	char unused[40];
};

void main(){

	struct students record;
	struct nonleaf node;
	int level = 0, offs = 0;
	int nor = 0, temp = 0;
	FILE *fp = fopen("thisfile.txt", "r");
	FILE *fp1 = fopen("thisbin.bin", "wb+");
	char *line = (char*)malloc(sizeof(char) * 128);


	fseek(fp1, 0, SEEK_SET);
	fseek(fp, 0, SEEK_SET);

	while (fscanf(fp, "%d,%[^,],%s", &record.rollno, record.name, record.college) != EOF){
		record.type = level;
		fwrite(&record, 64, 1, fp1);
		printf("\n%d - %s - %s", record.rollno, record.name, record.college);
		nor++;
	}
	++level;

	int val = 1;
	int count = 0;
	//fseek(fp1, 0, SEEK_CUR);
	printf("\n %d ", (ceil(log(nor*1.0f) / log(3.0f))));
	for (int j = 0; j < 5; j++)
	{
		if (level <= 1)
		{
			for (int i = 0; i < nor; i = i + 3){
				
				node.offset[0] = 64 * offs++;
				printf("\nnode off = %d", node.offset[0]);
				node.offset[1] = 64 * offs++;
				printf("\tnode off = %d", node.offset[1]);
				node.offset[2] = 64 * offs++;
				printf("\tnode off = %d", node.offset[2]);

				temp = ftell(fp1);
				fseek(fp1, node.offset[1], SEEK_SET);
				fread(&record, 64, 1, fp1);
				node.key[0] = record.rollno;
				fseek(fp1, node.offset[2], SEEK_SET);
				fread(&record, 64, 1, fp1);
				node.key[1] = record.rollno;
				fseek(fp1, temp, SEEK_SET);
				node.type = 0;
				printf("\n----key = %d\tkey = %d", node.key[0], node.key[1]);
				fwrite(&node, 64, 1, fp1);
				count++;
			}
			level = 2;
			//offs += count;
			continue;
		}

		else
		{
			struct nonleaf tleaf;
			tleaf = node;

			printf(" \n--- in else block coutn = %d--- ",count);
			memset(&node, 0, sizeof(node));
			for (int of = 0; of < 3; of++)
				node.offset[of] = 64 * offs++;
			printf("\n*************new node off : %d, %d, %d*************\n", node.offset[0], node.offset[1], node.offset[2]);
			temp = ftell(fp1);
			fseek(fp1, node.offset[1], SEEK_SET);
			fread(&tleaf, 64, 1, fp1);

			while (tleaf.type != 0)
			{
				//printf("##first while##");
				fseek(fp1, tleaf.offset[0], SEEK_SET);
				fread(&tleaf, 64, 1, fp1);
			} 
			fseek(fp1, tleaf.offset[0], SEEK_SET);
			fread(&record, 64, 1, fp1);
			node.key[0] = record.rollno;
			memset(&tleaf, 0, sizeof(tleaf));

			fseek(fp1, node.offset[2], SEEK_SET);
			fread(&tleaf, 64, 1, fp1);
			while (tleaf.type != 0){
				//printf("##second while##");
				fseek(fp1, tleaf.offset[0], SEEK_SET);
				fread(&tleaf, 64, 1, fp1);
			}
			fseek(fp1, tleaf.offset[0], SEEK_SET);
			fread(&record, 64, 1, fp1);
			node.key[1] = record.rollno;
			node.type = 2;
			fseek(fp1, 0, SEEK_END);
			printf("\n%d %d %d --- %d %d -- %d", node.offset[0], node.offset[1], node.offset[2], node.key[0], node.key[1], node.type);
			fwrite(&node, sizeof(node), 1, fp1);
			++level;
		}
	}


	getch();
}
