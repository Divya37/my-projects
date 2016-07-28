// json file problem

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
struct tags{

	char tag_name[20];
	char tag_value[20];
	int level;
	struct tags *nested;
	struct tags *next;

};

int length(char *str){
	int i;
	for (i = 0; str[i] != '\0'; i++);
	return i;
}


struct tags *createtags(struct tags *head, char *name, char *value, int level)
{
	printf("\n~~~~~~~~~~~~~~~~~~~~\n");
	struct tags *temp, *temp2;
	temp = (struct tags *)malloc(sizeof(struct tags));


	//for (int i = 0; i < length(name); i++)
	strcpy(temp->tag_name, name);

	//for (int i = 0; i<length(name); i++)
	strcpy(temp->tag_value, value);
	temp->nested = NULL;
	temp->next = NULL;
	printf("\n%s = %s\n", temp->tag_name, temp->tag_value);
			
	if (head == NULL)
		return temp;

	else
	{
		temp2 = head;
		while (temp2->next != NULL)
		{
			if (!strcmp(temp2->tag_name, name))
			{
				temp2->nested = temp;
				return head;
			}
			temp2 = temp2->next;

		}
		temp2->next = temp;
		return head;
	}
}


int main()
{
	int tag_flag = 1, value_flag = 0, scope_flag = 0, inner_flag = 0;
	int tag_no = 0, ind = 0, level = 0, flag = 1;
	char ch, tag_name[20], tag_value[20];

	struct tags *head = NULL;

	FILE *fp;
	fp = fopen("test_json.txt", "r");

	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n' || ch == ' ' || ch == '"' || ch == '\t' )
			continue;

		if(ch == '[')
		{
				head = createtags(head, tag_name, "the followeing values", level);
				continue;
		}
			
		if(ch == ']'){
			head = createtags(head, tag_name, tag_value, level);
				
			tag_flag = 1;
			value_flag = 0;
			ind = 0;
			continue;
		}

		if (ch == '{' && value_flag == 1){
			level++;
			tag_flag = 1;
			value_flag = 0;
			ind = 0;
			scope_flag++;
			continue;
		}

		if (ch == '}' && tag_flag == 1){

			head = createtags(head, tag_name, tag_value, level);
			level--;
			tag_flag = 1;
			value_flag = 0;
			ind = 0;
			continue;
		}
		if (ch == '{' || ch == '}')
			continue;

		if (ch == ',')
		{
			tag_value[ind] = '\0';
			//printf("\n-while , -----%s--- %s-----%d", tag_name, tag_value, level);
			head = createtags(head, tag_name, tag_value, level);
			tag_no++;
			tag_flag = 1;
			value_flag = 0;
			ind = 0;
			continue;

		}

		if (ch == ':')
		{
			tag_name[ind] = '\0';
			//printf("\n%s", tag_name);
			tag_flag = 0;
			value_flag = 1;
			ind = 0;
			continue;

		}

		if (tag_flag)
			tag_name[ind++] = ch;


		else if (value_flag)
			tag_value[ind++] = ch;


	}
	char *str;
	str = (char *)malloc(sizeof(char) * 20);
	printf("enter the value to retrieve : ");
	scanf("%s", str);
	while (head != NULL)
	{
		if (!strcmp(head->tag_name, str))
		{
			printf("required value : %s", head->tag_value);
			while (head->nested != NULL)
			{
				printf("\t%s", head->nested->tag_value);
				head = head->nested;
			}
			_getch();
			return 0;
		}

		//printf("\ntag = %s",head->tag_value);
		//printf("\nvalue = %s", head->tag_value);
		//printf("\nnested = %p", head->nested);
		head = head->next;
	}
	_getch();
	return 0;
}
