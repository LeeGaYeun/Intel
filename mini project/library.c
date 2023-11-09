#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bookinfo
{
	int num;
	char title[100];
	char writer[100];
	char publish[100];
	int price;
	
} book;

int i, count;
void registerbooks(book list[]);
void listofbook(book list[]);
void searchbook(book list[], char stitle[]);

int main()
{
	book list[100];
	int menu;
	count = 0;

	while (1) {

		printf("��  ��  ��  ��  ��  ��\n\n******MENU******\n\n");
		printf("1. ���\n2. ���\n3. �˻�\n0. ����\n\n\n");
		printf("����ϰ��� �ϴ� ����� ���ڸ� �Է��Ͻÿ� :");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
			registerbooks(list, &count);
			break;
		
		
		case 2:
			listofbook(list);
			break;

		case 3:
			char stitle[100];
			searchbook(list, stitle);
			break;
		case 0:
			printf("\n\n���α׷��� �����մϴ�.\n\n");
			exit(0);
			break;
		
		
		default:
			printf("\n\n��ȿ�� �޴��� �����ϼ���.\n\n");
			break;
		}
	}
	return 0;
}

void registerbooks(book list[])
{
	printf("����� å�� �� ���� �Է��ϼ��� :");
	scanf("%d", &count);

	for (i = 0; i < count; i++)
	{
		printf("��ȣ�� �Է��ϼ��� : ");
		scanf("%d", &list[i].num);
		printf("������ �Է��ϼ��� : ");
		scanf("%s", &list[i].title);
		printf("�۰��� �Է��ϼ��� : ");
		scanf("%s", &list[i].writer);
		printf("���ǻ縦 �Է��ϼ��� : ");
		scanf("%s", &list[i].publish);
		printf("������ �Է��ϼ��� : ");
		scanf("%d", &list[i].price);
		
	}
	printf("\n\n    ��ϵ� å ����\n\n\n");
	for (i = 0; i < count; i++) 
	{
		printf("%d  %s  %s  %s  %d\n\n\n\n", list[i].num, list[i].title, list[i].writer, list[i].publish, list[i].price);
	}
	printf("�޴��� ���ư��ðڽ��ϱ�?\n\nYes  [1]	  No  [0]\n\n");
	int back;
	scanf("%d", &back);
	if (back == 0)
	{
		printf("\n���α׷��� �����մϴ�.\n\n");
		exit(0);
	}
}

void listofbook(book list[])
{
	printf("\n\n   å ���\n\n");
	for (i = 0; i < count; i++)
	{
		printf("%d  %s  %s  %s  %d\n\n", list[i].num, list[i].title, list[i].writer, list[i].publish, list[i].price);
	}
	printf("�޴��� ���ư��ðڽ��ϱ�?\n\nYes  [1]	  No  [0]\n\n");
	int back;
	scanf("%d", &back);
	if (back == 0)
	{
		printf("\n���α׷��� �����մϴ�.\n\n");
		exit(0);
	}
}

void searchbook(book list[], char stitle[])
{
	
	printf("�˻��� å ������ �Է��ϼ���. : ");
	scanf("%s", stitle);

	int found = 0;
	for (i = 0; i < count; i++)
	{
		if (strcmp(list[i].title, stitle) == 0)
		{
			printf("\n\n%d  %s  %s  %s  %d\n\n\n\n", list[i].num, list[i].title, list[i].writer, list[i].publish, list[i].price);
			found = 1;
		}
	}
	if (!found)
	{
		printf("\n\nã���ô� å�� �����ϴ�.\n\n\n");
	}
	printf("�޴��� ���ư��ðڽ��ϱ�?\n\nYes  [1]	  No  [0]\n\n");
	int back;
	scanf("%d", &back);
	if (back == 0)
	{
		printf("\n���α׷��� �����մϴ�.\n\n");
		exit(0);
	}
}