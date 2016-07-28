//table sector for two different types of records students and staff and also checking for queries
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#pragma warning(disable:4996)
struct tablesector
{
	int pagetype = 0;
	int tableid;
	int rootpageid;
	int flag = 0;
};
struct teachingstaff{
	int type;
	int staffid;
	char name[15];
	char dept[10];
	char college[15];
};
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
	int prevpage;
	struct student data[10];
	char unused[24];
};
struct leafPageStaff{
	int pageType = 1;
	int prevpage;
	struct teachingstaff data[10];
	char unused[24];
};
void advanced_search(FILE *fp1){
	int option = 0;
	char *clg = (char *)malloc(sizeof(char) * 20);
	struct NonLeafPage nlf1, nlf2;
	struct leafPage lf1;
	struct leafPageStaff lf2;
	printf("\n1.Find all the students in a particular college\n2.Find all the branches in a particular college\n3.Find all faculty in a college");
	printf("\n4.Find all faculty of same branch from all colleges\n");
	printf("\nenter option : ");
	fflush(stdin);
	scanf("%d", &option);

	if (option == 1){
		memset(clg, '\0', sizeof(clg));
		printf("enter college to search students :");
		scanf("%s", clg);

		fseek(fp1, 0, SEEK_END);
		int p = ftell(fp1);
		fseek(fp1, p - 1024, SEEK_SET);
		fread(&nlf1, sizeof(nlf1), 1, fp1);

		for (int i = 1; i < 64; i++){
			if (nlf1.offset[i] == 0){
				fseek(fp1, nlf1.offset[i - 1], SEEK_SET);
				fread(&lf1, sizeof(lf1), 1, fp1);
				break;
			}				
		}
		while (lf1.prevpage >= -1){
			if (lf1.prevpage == -1){
				for (int i = 0; i < 10; i++){
					if (!strcmp(lf1.data[i].college, clg)){
						printf("\n%s", lf1.data[i].name);
					}
				}
				break;
			}
			for (int i = 0; i < 10; i++){
				if (!strcmp(lf1.data[i].college, clg)){
					printf("\n%s", lf1.data[i].name);
				}
			}
			fseek(fp1, lf1.prevpage, SEEK_SET);
			fread(&lf1, sizeof(lf1), 1, fp1);
		}

	}
	if (option == 2){
		memset(clg, '\0', sizeof(clg));
		printf("enter college to search faculty :");
		scanf("%s", clg);

		fseek(fp1, 0, SEEK_END);
		int p = ftell(fp1);
		fseek(fp1, p - 512, SEEK_SET);
		fread(&nlf1, sizeof(nlf1), 1, fp1);

		for (int i = 1; i < 64; i++){
			if (nlf1.offset[i] == 0){
				fseek(fp1, nlf1.offset[i - 1], SEEK_SET);
				fread(&lf2, sizeof(lf2), 1, fp1);
				break;
			}
		}
		while (lf2.prevpage >= -1){
			if (lf2.prevpage == -1){
				for (int i = 0; i < 10; i++){
					if (!strcmp(lf2.data[i].college, clg)){
						printf("\n%s", lf2.data[i].dept);
					}
				}
				break;
			}
			for (int i = 0; i < 10; i++){
				if (!strcmp(lf2.data[i].college, clg)){
					printf("\n%s", lf2.data[i].dept);
				}
			}
			fseek(fp1, lf2.prevpage, SEEK_SET);
			fread(&lf2, sizeof(lf2), 1, fp1);
		}
	}
	if (option == 3){
		memset(clg, '\0', sizeof(clg));
		printf("enter college to search faculty :");
		scanf("%s", clg);

		fseek(fp1, 0, SEEK_END);
		int p = ftell(fp1);
		fseek(fp1, p - 512, SEEK_SET);
		fread(&nlf1, sizeof(nlf1), 1, fp1);

		for (int i = 1; i < 64; i++){
			if (nlf1.offset[i] == 0){
				fseek(fp1, nlf1.offset[i - 1], SEEK_SET);
				fread(&lf2, sizeof(lf2), 1, fp1);
				break;
			}
		}
		while (lf2.prevpage >= -1){
			if (lf2.prevpage == -1){
				for (int i = 0; i < 10; i++){
					if (!strcmp(lf2.data[i].college, clg)){
						printf("\n%s", lf2.data[i].name);
					}
				}
				break;
			}
			for (int i = 0; i < 10; i++){
				if (!strcmp(lf2.data[i].college, clg)){
					printf("\n%s", lf2.data[i].name);
				}
			}
			fseek(fp1, lf2.prevpage, SEEK_SET);
			fread(&lf2, sizeof(lf2), 1, fp1);
		}
	}
	if (option == 4){
		memset(clg, '\0', sizeof(clg));
		printf("enter branch to search faculty :");
		scanf("%s", clg);

		fseek(fp1, 0, SEEK_END);
		int p = ftell(fp1);
		fseek(fp1, p - 512, SEEK_SET);
		fread(&nlf1, sizeof(nlf1), 1, fp1);

		for (int i = 1; i < 64; i++){
			if (nlf1.offset[i] == 0){
				fseek(fp1, nlf1.offset[i - 1], SEEK_SET);
				fread(&lf2, sizeof(lf2), 1, fp1);
				break;
			}
		}
		while (lf2.prevpage >= -1){
			if (lf2.prevpage == -1){
				for (int i = 0; i < 10; i++){
					if (!strcmp(lf2.data[i].dept, clg)){
						printf("\n%s", lf2.data[i].name);
					}
				}
				break;
			}
			for (int i = 0; i < 10; i++){
				if (!strcmp(lf2.data[i].dept, clg)){
					printf("\n%s", lf2.data[i].name);
				}
			}
			fseek(fp1, lf2.prevpage, SEEK_SET);
			fread(&lf2, sizeof(lf2), 1, fp1);
		}

	}
	
	

}
void student_details_search(FILE *fp1){
	struct NonLeafPage nlf2;
	struct leafPage lf2;
	char *clg = (char *)malloc(sizeof(char) * 20);
	int st_id, flag = 0;

	printf("\nEnter student id ::");
	fflush(stdin);
	scanf("%d", &st_id);

	memset(&nlf2, 0, sizeof(nlf2));
	fseek(fp1, 0, SEEK_END);
	long pos = ftell(fp1);
	fseek(fp1, pos - 1024, SEEK_SET);
	fread(&nlf2, sizeof(nlf2), 1, fp1);
	while (true){
		if (nlf2.pageType == 2){
			for (int i = 0; i < 62; i++){
				if (st_id < nlf2.keys[i] && i == 0){
					fseek(fp1, nlf2.offset[i], SEEK_SET);
					int x = nlf2.offset[i];
					pos = ftell(fp1);
					fread(&lf2, sizeof(lf2), 1, fp1);
					flag = 2;
					break;
				}
				if ((st_id >= nlf2.keys[i]) && (st_id < nlf2.keys[i + 1] || nlf2.keys[i + 1] == 0)){
					fseek(fp1, nlf2.offset[i + 1], SEEK_SET);
					int x = nlf2.offset[i + 1];
					pos = ftell(fp1);
					fread(&lf2, sizeof(lf2), 1, fp1);
					flag = 2;
					break;
				}
			}
		}
		if (flag == 2){
			for (int i = 0; i < 10; i++){
				if (st_id == lf2.data[i].rollno){
					printf("\n%d %s %s ", lf2.data[i].rollno, lf2.data[i].name, lf2.data[i].college);
					flag = 1;
					break;
				}
			}
		}
		if (flag == 1)
			break;
	}
}
void faculty_details_search(FILE *fp1){
	struct NonLeafPage nlf2;
	struct leafPageStaff lf2;
	char *clg = (char *)malloc(sizeof(char) * 20);
	int fac_id, st_id, flag = 0;

	printf("\nEnter faculty id ::");
	fflush(stdin);
	scanf("%d", &fac_id);

	memset(&nlf2, 0, sizeof(nlf2));
	fseek(fp1, 0, SEEK_END);
	long pos = ftell(fp1);
	fseek(fp1, pos - 512, SEEK_SET);
	fread(&nlf2, sizeof(nlf2), 1, fp1);
	while (true){
		if (nlf2.pageType == 2){
			for (int i = 0; i < 62; i++){
				if (fac_id < nlf2.keys[i] && i == 0){
					fseek(fp1, nlf2.offset[i], SEEK_SET);
					int x = nlf2.offset[i];
					pos = ftell(fp1);
					fread(&lf2, sizeof(lf2), 1, fp1);
					flag = 2;
					break;
				}
				if ((fac_id >= nlf2.keys[i]) && (fac_id < nlf2.keys[i + 1] || nlf2.keys[i + 1] == 0)){
					fseek(fp1, nlf2.offset[i + 1], SEEK_SET);
					int x = nlf2.offset[i + 1];
					pos = ftell(fp1);
					fread(&lf2, sizeof(lf2), 1, fp1);
					flag = 2;
					break;
				}
			}
		}
		if (flag == 2){
			for (int i = 0; i < 10; i++){
				if (fac_id == lf2.data[i].staffid){
					printf("\n%d %s %s %s", lf2.data[i].staffid, lf2.data[i].name, lf2.data[i].college, lf2.data[i].dept);
					flag = 1;
					break;
				}
			}
		}
		if (flag == 1)
			break;
	}
}

int find_empty_pos(FILE *ts){
	struct tablesector tt;
	fseek(ts, 0, SEEK_SET);
	while (!feof(ts)){
		fread(&tt, sizeof(tt), 1, ts);
		if (tt.flag == 0)
		{
			fseek(ts, 0, SEEK_END);
			return tt.rootpageid;
		}
	}
	fseek(ts, 0, SEEK_END);
	return 0;
}

int main()
{
	FILE *fp, *fp1, *fpp;
	struct leafPage lf1;
	struct leafPageStaff lf2;
	struct NonLeafPage nlf1, nlf2;
	struct tablesector tt;
	FILE *ts = fopen("tablesector.bin", "wb");
	fpp = fopen("staff.txt", "r");
	fp = fopen("studs.txt", "r");
	fp1 = fopen("output.bin", "wb");

	if (!fp || !fpp)
	{
		perror("can't open\n");
	}

	int i = 1, offsetvalue = 0, count = 0;
	int flag = 0;
	int k_index = 0, off_index = 1, y = -1, x = -1;
	int prev1 = 0, prev2 = 512, prev_pos_ts1 = 0, prev_pos_ts2 = 16, prev_nlf1 = 2048, prev_nlf2 = 2560;
	fseek(fp, 0, SEEK_SET);
	fseek(fpp, 0, SEEK_SET);
	fseek(fp1, 0, SEEK_SET);
	fseek(ts, 0, SEEK_SET);
	while (!feof(fp) && !feof(fpp))
	{
		for (int j = 0; j < 10; j++)
		{
			memset(&lf1.data[j], '\0', sizeof(struct student));
			memset(&lf2.data[j], '\0', sizeof(struct teachingstaff));

			fscanf(fp, "%d,%[^,],%[^\n]\n", &lf1.data[j].rollno, lf1.data[j].name, lf1.data[j].college);
			fscanf(fpp, "%d,%[^,],%[^,],%[^\n]\n", &lf2.data[j].staffid, lf2.data[j].name, lf2.data[j].college, lf2.data[j].dept);
			
			printf("\n%d %s %s", lf1.data[j].rollno, lf1.data[j].name, lf1.data[j].college);
			printf("\n%d + %s + %s + %s ", lf2.data[j].staffid, lf2.data[j].name, lf2.data[j].college, lf2.data[j].dept);
		}

		fseek(fp1, 0, SEEK_END);
		prev1 = y;
		prev2 = x;
		//printf("\n#################################################prev1 = %d prev2 = %d", prev1, prev2);
		lf1.prevpage = prev1;
		lf2.prevpage = prev2;

		y = ftell(fp1);	
		fwrite(&lf1, sizeof(lf1), 1, fp1);

		x = ftell(fp1);
		fwrite(&lf2, sizeof(lf2), 1, fp1);

		//printf("\nempty pos : %d", find_empty_pos(ts));
		
		++count;
		if (count == 2){
			memset(&nlf1, 0, sizeof(nlf1));
			memset(&nlf2, 0, sizeof(nlf2));
			nlf1.pageType = 2;
			nlf2.pageType = 2;

			nlf1.offset[0] = 0;
			nlf1.offset[1] = 1024;
			nlf2.offset[0] = 512;
			nlf2.offset[1] = 1024 + 512;

			nlf1.keys[0] = lf1.data[0].rollno;
			nlf2.keys[0] = lf2.data[0].staffid;

			fseek(fp1, 0, SEEK_END);

			tt.pagetype = 2;
			tt.tableid = 1;
			tt.rootpageid = ftell(fp1);
			tt.flag = 1;
			prev_pos_ts1 = ftell(ts);
			printf("\nprevpos1 = %d", ftell(ts));
			fseek(ts, 0, SEEK_END);
			fwrite(&tt, sizeof(tt), 1, ts);

			//fwrite(&nlf1, sizeof(nlf1), 1, fp1);

			tt.pagetype = 2;
			tt.tableid = 2;
			tt.rootpageid = ftell(fp1);
			tt.flag = 1;
			printf("\nprevpos2 = %d", ftell(ts));
			prev_pos_ts2 = ftell(ts);
			fseek(ts, 0, SEEK_END);
			fwrite(&tt, sizeof(tt), 1, ts);

			//fwrite(&nlf2, sizeof(nlf2), 1, fp1);
		}

		if (count > 2){			
			nlf1.keys[++k_index] = lf1.data[0].rollno;			
			nlf2.keys[k_index] = lf2.data[0].staffid;

			fseek(fp1, 0, SEEK_END);

			fseek(ts, prev_pos_ts1, SEEK_SET);
			fread(&tt, sizeof(tt), 1, ts);
			tt.flag = 0;
			fseek(ts, prev_pos_ts1, SEEK_SET);
			fwrite(&tt, sizeof(tt), 1, ts);
			fseek(ts, 0, SEEK_END);

			tt.pagetype = 2;
			tt.tableid = 1;
			tt.rootpageid = ftell(fp1);
			tt.flag = 1;
			prev_pos_ts1 = ftell(ts);
			printf("\nprevpos1 = %d", ftell(ts));
			fwrite(&tt, sizeof(tt), 1, ts);
			nlf1.offset[++off_index] = y;
			printf("\n ***************************************************************offset = %d, %d", nlf1.offset[off_index], ftell(fp1));
			//fwrite(&nlf1, sizeof(nlf1), 1, fp1);
			nlf2.offset[off_index] = x;
			
			//memset(&tt, '0', sizeof(tt));
			fseek(ts, prev_pos_ts2, SEEK_SET);
			fread(&tt, sizeof(tt), 1, ts);
			tt.flag = 0;
			fseek(ts, prev_pos_ts2, SEEK_SET);
			fwrite(&tt, sizeof(tt), 1, ts);
			fseek(ts, 0, SEEK_END);

			//memset(&tt, '0', sizeof(tt));
			tt.pagetype = 2;
			tt.tableid = 2;
			tt.rootpageid = ftell(fp1);
			tt.flag = 1;
			prev_pos_ts2 = ftell(ts);
			printf("\nprevpos2 = %d", ftell(ts));
			fwrite(&tt, sizeof(tt), 1, ts);
			printf("\n ***************************************************************offset = %d, %d", nlf2.offset[off_index], ftell(fp1));
			//fwrite(&nlf2, sizeof(nlf2), 1, fp1);
		}

		
	}
	while (!feof(fp)){
		for (int j = 0; j < 10; j++)
		{
			memset(&lf1.data[j], '\0', sizeof(struct student));
			fscanf(fp, "%d,%[^,],%[^\n]\n", &lf1.data[j].rollno, lf1.data[j].name, lf1.data[j].college);
			printf("\n%d %s %s", lf1.data[j].rollno, lf1.data[j].name, lf1.data[j].college);
		}
		prev1 = y;
		lf1.prevpage = prev1;
		//printf("\n#################################################prev1 = %d prev2 = %d", prev1, prev2);

		nlf1.offset[++off_index] = nlf1.offset[off_index - 1] + 512;
		nlf1.keys[++k_index] = lf1.data[0].rollno;

		fseek(fp1, 0, SEEK_END);
	
		//memset(&tt, '0', sizeof(tt));
		fseek(ts, prev_pos_ts1, SEEK_SET);
		fread(&tt, sizeof(tt), 1, ts);
		tt.flag = 0;
		fseek(ts, prev_pos_ts1, SEEK_SET);
		fwrite(&tt, sizeof(tt), 1, ts);
		fseek(ts, 0, SEEK_END);

		//(&tt, '0', sizeof(tt));
		tt.pagetype = 2;
		tt.tableid = 1;
		tt.rootpageid = ftell(fp1);
		tt.flag = 1;
		prev_pos_ts1 = ftell(ts);
		printf("\nprevpos1 = %d", ftell(ts));
		fwrite(&tt, sizeof(tt), 1, ts);
		//fwrite(&nlf1, sizeof(nlf1), 1, fp1);

		//memset(&tt, '0', sizeof(tt));
		fseek(ts, prev_pos_ts2, SEEK_SET);
		fread(&tt, sizeof(tt), 1, ts);
		tt.flag = 0;
		fseek(ts, prev_pos_ts2, SEEK_SET);
		fwrite(&tt, sizeof(tt), 1, ts);
		fseek(ts, 0, SEEK_END);

		//memset(&tt, '0', sizeof(tt));
		tt.pagetype = 2;
		tt.tableid = 2;
		tt.rootpageid = ftell(fp1);
		tt.flag = 1;
		prev_pos_ts2 = ftell(ts);
		printf("\nprevpos2 = %d", ftell(ts));
		fwrite(&tt, sizeof(tt), 1, ts);
		//fwrite(&nlf2, sizeof(nlf2), 1, fp1);
	}
	while (!feof(fpp)){
		for (int j = 0; j < 10; j++)
		{
			memset(&lf2.data[j], '\0', sizeof(struct teachingstaff));
			fscanf(fpp, "%d,%[^,],%[^,],%[^\n]\n", &lf2.data[j].staffid, lf2.data[j].name, lf2.data[j].college, lf2.data[j].dept);
			printf("\n%d %s %s %s", lf2.data[j].staffid, lf2.data[j].name, lf2.data[j].college, lf2.data[j].dept);
		}
		prev2 = x;
		//printf("\n#################################################prev1 = %d prev2 = %d", prev1, prev2);
		fseek(fp1, 0, SEEK_END);
		x = ftell(fp1);
		nlf2.offset[++off_index] = x;
		lf2.prevpage = prev2;
		fwrite(&lf2, sizeof(lf2), 1, fp1);		
		nlf2.keys[++k_index] = lf2.data[0].staffid;

		fseek(fp1, 0, SEEK_END);
		printf("\n**********************************************************offsetnlf2 = %d", nlf2.offset[off_index]);
		//memset(&tt, '0', sizeof(tt));
		fseek(ts, prev_pos_ts1, SEEK_SET);
		fread(&tt, sizeof(tt), 1, ts);
		tt.flag = 0;
		fseek(ts, prev_pos_ts1, SEEK_SET);
		fwrite(&tt, sizeof(tt), 1, ts);
		fseek(ts, 0, SEEK_END);

		//memset(&tt, '0', sizeof(tt));
		tt.pagetype = 2;
		tt.tableid = 1;
		tt.rootpageid = ftell(fp1);
		tt.flag = 1;
		prev_pos_ts1 = ftell(ts);
		printf("\nprevpos1 = %d", ftell(ts));
		fwrite(&tt, sizeof(tt), 1, ts);
		//fwrite(&nlf1, sizeof(nlf1), 1, fp1);

		//memset(&tt, '0', sizeof(tt));
		fseek(ts, prev_pos_ts2, SEEK_SET);
		fread(&tt, sizeof(tt), 1, ts);
		tt.flag = 0;
		fseek(ts, prev_pos_ts2, SEEK_SET);
		fwrite(&tt, sizeof(tt), 1, ts);
		fseek(ts, 0, SEEK_END);

		//memset(&tt, '0', sizeof(tt));
		tt.pagetype = 2;
		tt.tableid = 1;
		tt.rootpageid = ftell(fp1);
		tt.flag = 1;
		prev_pos_ts2 = ftell(ts);
		printf("\nprevpos2 = %d", ftell(ts));
		fwrite(&tt, sizeof(tt), 1, ts);
		//fwrite(&nlf2, sizeof(nlf2), 1, fp1);
	}
	fwrite(&nlf1, sizeof(nlf1), 1, fp1);
	fwrite(&nlf2, sizeof(nlf2), 1, fp1);
	fclose(ts);
	fclose(fp);
	fclose(fpp);
	fclose(fp1);
	fp1 = fopen("output.bin", "rb");
	printf("\nsuccessfully entered");
	while (1){
		int option = 0;
		printf("\n\n1.search for faculty details\n2.search for student details\n3.go for advanced search options\n4.exit\n");
		printf("\nenter choice ::");
		fflush(stdin);
		scanf("%d", &option);
		if (option == 1){
			faculty_details_search(fp1);
		}
		if (option == 2){
			student_details_search(fp1);
		}
		if (option == 3){
			advanced_search(fp1);
		}
		if (option == 4)
			break;
	}
	fclose(fp1);
	
}

