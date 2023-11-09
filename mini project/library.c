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

		printf("도  서  프  로  그  램\n\n******MENU******\n\n");
		printf("1. 등록\n2. 목록\n3. 검색\n0. 종료\n\n\n");
		printf("사용하고자 하는 기능의 숫자를 입력하시오 :");
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
			printf("\n\n프로그램을 종료합니다.\n\n");
			exit(0);
			break;
		
		
		default:
			printf("\n\n유효한 메뉴를 선택하세요.\n\n");
			break;
		}
	}
	return 0;
}

void registerbooks(book list[])
{
	printf("등록할 책의 권 수를 입력하세요 :");
	scanf("%d", &count);

	for (i = 0; i < count; i++)
	{
		printf("번호를 입력하세요 : ");
		scanf("%d", &list[i].num);
		printf("제목을 입력하세요 : ");
		scanf("%s", &list[i].title);
		printf("작가를 입력하세요 : ");
		scanf("%s", &list[i].writer);
		printf("출판사를 입력하세요 : ");
		scanf("%s", &list[i].publish);
		printf("가격을 입력하세요 : ");
		scanf("%d", &list[i].price);
		
	}
	printf("\n\n    등록된 책 정보\n\n\n");
	for (i = 0; i < count; i++) 
	{
		printf("%d  %s  %s  %s  %d\n\n\n\n", list[i].num, list[i].title, list[i].writer, list[i].publish, list[i].price);
	}
	printf("메뉴로 돌아가시겠습니까?\n\nYes  [1]	  No  [0]\n\n");
	int back;
	scanf("%d", &back);
	if (back == 0)
	{
		printf("\n프로그램을 종료합니다.\n\n");
		exit(0);
	}
}

void listofbook(book list[])
{
	printf("\n\n   책 목록\n\n");
	for (i = 0; i < count; i++)
	{
		printf("%d  %s  %s  %s  %d\n\n", list[i].num, list[i].title, list[i].writer, list[i].publish, list[i].price);
	}
	printf("메뉴로 돌아가시겠습니까?\n\nYes  [1]	  No  [0]\n\n");
	int back;
	scanf("%d", &back);
	if (back == 0)
	{
		printf("\n프로그램을 종료합니다.\n\n");
		exit(0);
	}
}

void searchbook(book list[], char stitle[])
{
	
	printf("검색할 책 제목을 입력하세요. : ");
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
		printf("\n\n찾으시는 책이 없습니다.\n\n\n");
	}
	printf("메뉴로 돌아가시겠습니까?\n\nYes  [1]	  No  [0]\n\n");
	int back;
	scanf("%d", &back);
	if (back == 0)
	{
		printf("\n프로그램을 종료합니다.\n\n");
		exit(0);
	}
}