#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBooks 100

typedef struct bookinfo
{
	int num;
	char title[100];
	char writer[100];
	char publish[100];
	int price;
	int borrownum;

} book;
char stitle[100];
int i, count, found;
book list[MAXBooks];
void registerbooks(book list[]);
void deletebook();
void listofbook();
void searchbook(book list[], char stitle[]);
void borrow();
void return_();
void BACKMENU();
void print();

int main()
{
	int menu;
	
	while (1) {

		printf("도  서  프  로  그  램\n\n******MENU******\n\n");
		printf("1. 등록\n2. 목록\n3. 검색\n4. 대출\n5. 반납\n0. 종료\n\n\n");
		printf("사용하고자 하는 기능의 숫자를 입력하시오 :");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
			registerbooks(list);
			BACKMENU();
			break;

		case 2:
			listofbook();
			BACKMENU();
			break;

		case 3:
			searchbook(list, stitle);
			BACKMENU();
			break;
		
		case 4:
			borrow();
			BACKMENU();
			break;

		case 5:
			return_();
			BACKMENU();
			break;

		case 6:
			deletebook();
			BACKMENU();
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
	int numbook;

	printf("등록할 책의 권 수를 입력하세요\n");
	scanf("%d", &numbook);

	if (numbook > MAXBooks)
	{
		printf("100개 이상 책 등록 불가합니다.\n");
		return;
	}

	for (i = 0; i < numbook; i++)
	{
		printf("\n%d번째 책 정보를 입력하세요:\n\n", count + i + 1);
		list[count + i].num = count + i + 1;
		printf("제목을 입력하세요 : ");
		scanf("%s", list[count + i].title);
		printf("작가를 입력하세요 : ");
		scanf("%s", list[count + i].writer);
		printf("출판사를 입력하세요 : ");
		scanf("%s", list[count + i].publish);
		printf("가격을 입력하세요 : ");
		scanf("%d", &list[count + i].price);
	}

	count += numbook;
	
	for (i = count - numbook; i < count; i++)
	{
		list[i].borrownum = 0;
	}

	printf("등록한 책 정보\n\n");
	for (i = count - numbook; i < count; i++)
	{
		print();
	}
}

void deletebook()
{
	int delete;
	printf("삭제할 책 번호를 입력하세요\n");
	scanf("%d", &delete);
	for (i = 0; i < count; i++)
	{
		if (delete == list[i].num)
		{
			//list[i].num, list[i].title, list[i].writer, list[i].publish, list[i].price
			list[i - 1].num = list[i].num;
			strcpy(list[i - 1].title, list[i].title);
			strcpy(list[i - 1].writer, list[i].writer);
			strcpy(list[i - 1].publish, list[i].publish);
			list[i - 1].price = list[i].price;
			
			printf("\n\n%d  %s  %s  %s  %d\n\n",
				list[0].num, list[0].title, list[0].writer, list[0].publish, list[0].price);

		}
	}
	
	
}

void listofbook()
{
	printf("\n\n   책 목록\n\n");
	for (i = 0; i < count; i++)
	{
		print();
	}
}

void searchbook(book list[], char stitle[])
{
	printf("검색할 책 제목을 입력하세요. : ");
	scanf("%s", stitle);
		
	for (i = 0; i < count; i++)
	{
		if (strcmp(list[i].title, stitle) == 0)
		{
			print();
			found = 1;
		}
	}
	
	if (!found)
	{
		printf("\n\n찾으시는 책이 없습니다.\n\n\n");
	}
}

void borrow()
{
	int cborrownum;
	printf("대출 가능한 책\n");
	for (i = 0; i < count; i++)
	{
		if (list[i].borrownum == 0)
		{
			print();
		}
	}

	printf("대출할 책 번호를 입력하세요.\n");
	scanf("%d", &cborrownum);

	for (i = 0; i < count; i++)
	{
		if (cborrownum == list[i].num)
		{
			found = 1;
			if (list[i].borrownum == 0)
			{
				list[i].borrownum = 1;
				printf("%d번 책 대출 했습니다.\n\n", cborrownum);
			}
			else
			{
				printf("대출 불가능합니다.\n\n");
			}
		}
	}

	if (!found)
	{
		printf("책 번호가 존재하지 않습니다.\n\n");
	}
	
}

void return_()
{
	int cborrownum;
	printf("반납 가능한 책\n");
	for (i = 0; i < count; i++)
	{
		if (list[i].borrownum == 1)
		{
			print();
		}
	}

	printf("반납할 책 번호를 입력하세요.\n");
	scanf("%d", &cborrownum);

	for (i = 0; i < count; i++)
	{
		if (cborrownum == list[i].num)
		{
			found = 1;
			if (list[i].borrownum == 1)
			{
				list[i].borrownum = 0;
				printf("%d번 책 반납 했습니다.\n\n", cborrownum);
			}
			else
			{
				printf("반납 불가능합니다.\n\n");
			}
		}
	}

	if (!found)
	{
		printf("책 번호가 존재하지 않습니다.\n\n");
	}

}

void BACKMENU()
{
	printf("메뉴로 돌아가시겠습니까?\n\nYes  [1]	  No  [0]\n\n");
	int back;
	scanf("%d", &back);

	if (back == 0)
	{
		printf("\n프로그램을 종료합니다.\n\n");
		exit(0);
	}
}

void print()
{
	printf("\n\n%d  %s  %s  %s  %d", 
		list[i].num, list[i].title, list[i].writer, list[i].publish, list[i].price);
	if (list[i].borrownum == 1) {
		printf("\t대출중...\n");
	}
	else printf("\n\n");
}
