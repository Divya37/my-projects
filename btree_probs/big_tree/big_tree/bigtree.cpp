
//offsets = 64 , keys = 63 640records
 
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma warning(disable:4996)

struct students{
	int type;
	int rollno;
	char name[20];
	char college[20];
};

struct nonleaf{
	int type;
	int offset[64];
	int key[63];
}; 

struct leaf{
	int pagetype;
	struct students data[10];
	char unused[28];
};

void main(){

	struct students record[10];
	struct nonleaf node;
	struct leaf d;
	int level = 0, offs = 0;
	int nor = 0, temp = 0, i = 0;
	FILE *fp = fopen("thisfile.csv", "r");
	FILE *fp1 = fopen("bigfile.bin", "wb+");
	char *line = (char*)malloc(sizeof(char) * 128);

		fseek(fp1, 0, SEEK_SET);
		fseek(fp, 0, SEEK_SET);

		i = 0;
		while (!feof(fp)){
			i = 0;
			while (i < 10){
				fscanf(fp, "%d,%[^,],%[^\n]", &d.data[i].rollno, d.data[i].name, d.data[i].college);
				d.data[i].type = 0;
				//printf("\n%d - %s - %s", d.data[i].rollno, d.data[i].name, d.data[i].college);
				i++;
			}
			fwrite(&d, sizeof(d), 1, fp1);
		}
		long size = ftell(fp1);
		memset(&node, 0, sizeof(node));
		memset(record, 0, sizeof(record));
		node.type = 1;
		i = 0;
		node.offset[i++] = 0;
		struct leaf lf;
		while (i<64){
			memset(&lf, 0, sizeof(lf));
			node.offset[i++] = i * 512;
			fseek(fp1, node.offset[i - 1], SEEK_SET);
			fread(&lf, 512, 1, fp1);
			node.key[i-1] = lf.data[0].rollno;
			size = size - 512;
		}
		fseek(fp1, 0, SEEK_END);
		printf("size = %d", sizeof(node));
		fwrite(&node,512, 1, fp1);
		_getch();
}




































