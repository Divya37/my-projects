#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#pragma warning(disable:4996)

struct symbol_table{
	int flag = 1;
	int address;
	int size;
	char name;
	int val;
	char unused[19];
};
struct sym_tab{
	int address;
	int size;
	char name;
	int val;
	struct sym_tab *next;
};


struct intermediate_language{
	int flag = 2;
	int lineno;
	int opcode;
	int para[5];
};

int compare(char *str1, char *str2){
	for (int i = 0; str1[i] != '\0'; i++){
		if (str1[i] != str2[i])return 0;
	}
	return 1;
}
int isarr(char *val){
	for (int i = 0; i < strlen(val); i++){
		if (val[i] == '[')
			return val[i + 1] - '0';
	}
	return 1;
}
int fetch_id(char *keyword){
	char *keywords[14] = { "MOVRM", "MOVMR", "ADD", "SUB", "MUL", "JMP", "IF", "EQ", "LT", "GT", "LTEQ", "GTEQ", "PRINT", "READ" };
	for (int i = 0; i < 14; i++){
		if (compare(keyword, keywords[i]))
			return i;
	}
}
int fetch_reg_id(char *reg){
	//printf("\nreg = %s", reg);
	char *opcode[8] = { "AX", "BX", "CX", "DX", "EX", "FX", "GX", "HX" };
	for (int i = 0; i < 8; i++){
		if (compare(reg, opcode[i]) == 1)
		{
			//printf("\treg = %s i = %d\n", reg, i);
			return i;
		}
	}
}
int fetch_var_addr(char *var, char *vars, int size){
	struct symbol_table s;
	FILE *fpp = fopen("binfile.bin", "rb");
	while (!feof(fpp)){
		fread(&s, sizeof(s), 1, fpp);
		if (s.flag == 1){
			if (s.name == var[0]){
				fclose(fpp);
				return s.address;
			}
		}
	}		
			//printf("\n\t\t i = %d var = %c name = %c address = %d size = %d\n", i, var[0], s.name, s.address, s.size);
		
	return 0;
}

void processcode(FILE *fp){
	FILE *fpp = fp;
	fseek(fp, 0, SEEK_SET);
	char *keywords[14] = { "MOVRM", "MOVMR", "ADD", "SUB", "MUL", "JMP", "IF", "EQ", "LT", "GT", "LTEQ", "GTEQ", "PRINT", "DATA" };
	char *opcode[8] = { "AX", "BX", "CX", "DX", "EX", "FX", "GX", "HX" };
	int arr[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	struct intermediate_language il;
	while (!feof(fp)){
		fread(&il, sizeof(il), 1, fp);
		if (il.flag == 2){
			if (il.opcode == 1){
				fseek(fpp, 0, SEEK_SET);
				while (!feof(fpp)){

				}
			}
		}
	}
	// struct intermediate_language
}
struct sym_tab* insert(struct sym_tab *head, char name, int size, int address){

	struct sym_tab *temp = (struct sym_tab *)malloc(sizeof(struct sym_tab));
	temp->name = name;
	temp->size = size;
	temp->address = address;
	temp->val = -1;
	temp->next = NULL;
	//fprintf(fpp, "DATA %c\n", temp->var);

	//printf("\nin insert %c = %d\n", temp->var, temp->val);
	if (head == NULL)
		return temp;
	struct sym_tab *temp1 = head;
	while (temp1->next != NULL){
		//printf("\nin insert %c = %d\n", temp1->var, temp1->val);
		temp1 = temp1->next;
	}
	temp1->next = temp;
	return head;
}

void main(){
	
	int address = 0, size = 1, ind = 0, lines = 0, val=0;
	char *keyword, *temp, *value, *val1, *val2, *val3, val_index = 0, *var, *vars, key_index = 0;

	struct symbol_table st;
	struct sym_tab *head = NULL;
	struct intermediate_language il;

	vars = (char *)malloc(sizeof(char) * 20);
	var = (char *)malloc(sizeof(char) * 5);
	val1 = (char *)malloc(sizeof(char) * 5);
	val2 = (char *)malloc(sizeof(char) * 5);
	val3 = (char *)malloc(sizeof(char) * 5);
	temp = (char *)malloc(sizeof(char) * 20);
	value = (char *)malloc(sizeof(char) * 10);
	keyword = (char *)malloc(sizeof(char) * 10);

	FILE *fp = fopen("asmcode.txt", "r");
	FILE *fp1 = fopen("binfile.bin", "wb");
	fclose(fp1);
	fseek(fp, 0, SEEK_SET);
	int key_flag = 1, value_flag = 0, equation = 0, lineno = 0, l = 0;

	while (!feof(fp)){	
		fp1 = fopen("binfile.bin", "rb+");
		fscanf(fp, "%s", keyword);
		if (!strcmp(keyword, "DATA")){
			fscanf(fp, " %s\n", value);
			printf("\n keyword : %s value : %s", keyword, value);
			if (sizeof(value) > 2){
				size = isarr(value);
			}

			vars[ind++] = value[0];
			st.name = value[0];
			st.size = size;
			st.address = address;
			head = insert(head, st.name, st.size, st.address);
			fseek(fp1, 0, SEEK_END);
			fwrite(&st, sizeof(st), 1, fp1);
			fclose(fp1);
			//printf("\t value = %c size = %d,  address = %d", st.name, st.size, st.address);
			address = address + size;
			continue;
		}
		if (equation == 0){
			lines++;
			//fscanf(fp, "%s", keyword);
			memset(&il, 0, sizeof(il));
			if (compare(keyword, "READ") == 1 || compare(keyword, "JUMP") == 1)
			{
				fscanf(fp, " %s\n", value);
				printf("\nkeyword: %s value: %s", keyword, value);
				il.para[0] = fetch_reg_id(value);
				printf(" para[0] = %d", il.para[0]);
			}
			else if (compare(keyword, "MOVRM") == 1) // 
			{
				fscanf(fp, " %s %s\n", val1, val2);
				printf("\nkeyword: %s val1: %s val2: %s", keyword, val1, val2);
				if (val1[strlen(val1) - 1] == ',')
					val1[strlen(val1) - 1] = '\0';
				il.para[0] = fetch_reg_id(val1);
				il.para[1] = fetch_var_addr(val2, vars, ind);
				printf(" para[0] = %d para[1] = %d", il.para[0], il.para[1]);
				
			}
			else if (compare(keyword, "MOVMR") == 1)
			{
				fscanf(fp, " %s %s\n", val1, val2);
				printf("\nkeyword: %s val1: %s val2: %s", keyword, val1, val2);
				il.para[0] = fetch_var_addr(val1, vars, ind);
				il.para[1] = fetch_reg_id(val2); 
				printf(" para[0] = %d para[1] = %d", il.para[0], il.para[1]);
			}
			else if (compare(keyword, "ADD") == 1 || compare(keyword, "SUB") == 1 || compare(keyword, "MUL") == 1)
			{
				fscanf(fp, " %s %s %s\n", val1, val2, val3);
				printf("\nkeyword: %s val1: %s val2: %s val3: %s ", keyword, val1, val2, val3);
				if (val1[strlen(val1) - 1] == ',')
					val1[strlen(val1) - 1] = '\0';
				if (val2[strlen(val2) - 1] == ',')
					val2[strlen(val2) - 1] = '\0';
				il.para[0] = fetch_reg_id(val1);
				il.para[1] = fetch_reg_id(val2);
				il.para[2] = fetch_reg_id(val3);
				printf(" para[0] = %d para[1] = %d para[2] = %d", il.para[0], il.para[1], il.para[2]);
			}
			il.lineno = lines;
			il.opcode = fetch_id(keyword);
			fseek(fp1, 0, SEEK_END);
			fwrite(&il, sizeof(il), 1, fp1);
			fclose(fp1);
			continue;
		}
		//fscanf(fp, "%s", keyword); 
		
		/*if (compare(keyword, "START:") == 1 && equation == 0)
		{
			vars[ind] = '\0';
			printf("\n equation made 1");
			printf("----%s---", vars);
			equation = 1;
			memset(keyword, '\0', sizeof(keyword));
			memset(value, '\0', sizeof(value));
			continue;
		}
		*/
		
	}
	fclose(fp);
	fp = fopen("binfile.bin", "rb");
	processcode(fp);
	_getch();

}
