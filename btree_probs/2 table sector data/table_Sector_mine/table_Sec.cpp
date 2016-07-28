#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#pragma warning(disable:4996)

struct student{
	int type;
	int rollno;
	char name[20];
	char college[20];
};
struct NonLeafPage{
	int pageType = 2;
	int keys[63];
	int offset[64];
};
struct leafPage{
	int pageType = 1;
	struct student data[10];
	char unused[28];
};
int main()
{
	FILE *fp, *fp1, *fpp;
	struct leafPage lf1, lf2;
	struct NonLeafPage nlf1, nlf2;
	fp = fopen("thisfile.csv", "r");
	fpp = fopen("thisfile.txt", "r");
	fp1 = fopen("output.bin", "wb");

	if (!fp || !fpp)
	{
		perror("can't open\n");
	}

	int i = 1, k1 = -1, offsetvalue = 0, k2 = -1, count = 0;
	int flag = 0;
	int k_index = 0, off_index = 1;
	fseek(fp, 0, SEEK_SET);
	fseek(fpp, 0, SEEK_SET);
	fseek(fp1, 0, SEEK_SET);
	while (!feof(fp) && !feof(fpp))
	{		
		for (int j = 0; j < 10; j++)
		{
			memset(&lf1.data[j], '\0', sizeof(struct student));
			memset(&lf2.data[j], '\0', sizeof(struct student));
			fscanf(fp, "%d,%[^,],%[^\n]\n", &lf1.data[j].rollno, lf1.data[j].name, lf1.data[j].college);
			fscanf(fpp, "%d,%[^,],%[^\n]\n", &lf2.data[j].rollno, lf2.data[j].name, lf2.data[j].college);
			printf("\n%d %s %s", lf1.data[j].rollno, lf1.data[j].name, lf1.data[j].college);
		}
		fwrite(&lf1, sizeof(struct leafPage), 1, fp1);
		int y = ftell(fp1);
		fwrite(&lf2, sizeof(struct leafPage), 1, fp1);
		int x = ftell(fp1);
		++count;

		if (count > 2){
			nlf1.offset[++off_index] = nlf1.offset[off_index-1] + 1024;
			nlf1.keys[++k_index] = lf1.data[0].rollno;

			nlf2.offset[off_index] = nlf2.offset[off_index - 1] + 1024;
			nlf2.keys[k_index] = lf2.data[0].rollno;

			fseek(fp1, 0, SEEK_END);
			fwrite(&nlf1, sizeof(nlf1), 1, fp1);
			fwrite(&nlf2, sizeof(nlf2), 1, fp1);
		}

		if (count == 2){
			memset(&nlf1, 0, sizeof(nlf1));
			memset(&nlf2, 0, sizeof(nlf2));

			nlf1.offset[0] = 0;
			nlf1.offset[1] = 1024;
			nlf2.offset[0] = 512;
			nlf2.offset[1] = 1024+512;

			nlf1.keys[0] = lf1.data[0].rollno;
			nlf2.keys[0] = lf2.data[0].rollno;

			fseek(fp1, 0, SEEK_END);
			fwrite(&nlf1, sizeof(nlf1), 1, fp1);
			fwrite(&nlf2, sizeof(nlf2), 1, fp1);
		}

	}

	printf("successfull");
	_getch();
}

