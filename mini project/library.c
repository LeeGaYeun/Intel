#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBooks 100

typedef struct bookinfo
{
	int num;				//책 번호
	char title[100];		//책 이름
	char writer[100];		//작가
	char publish[100];		//출판사
	int price;				//가격
	int borrownum;			//대출 여부 (0: 대출 가능, 1: 대출 중)
} book;
char stitle[100];			//검색할 책 제목을 저장하는 배열
int i, count, found;
book list[MAXBooks];		//구조체 book 정보를 저장하는 배열

void registerbooks(book list[]);
void deletebook();
void listofbook();
void searchbook(book list[], char stitle[]);
void borrow();
void return_();
void BACKMENU();
void print();
int typo(const char* type);

int main()
{
	while (1) {

		printf("도  서  프  로  그  램\n\n******MENU******\n\n");
		printf("1. 등록\n2. 목록\n3. 검색\n4. 대출\n5. 반납\n6. 도서 삭제\n0. 종료\n\n\n");
		int menu = typo("사용하고자 하는 기능의 숫자를 입력하시오 :");

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

void registerbooks(book list[])		//책 등록 함수
{
	int numbook = typo("등록할 책의 권 수를 입력하세요\n");

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
		list[count + i].price = typo("가격을 입력하세요 : ");
	}

	count += numbook;	//전체 도서의 개수 + 새로 등록한 책

	for (i = count - numbook; i < count; i++)	//등록한 책 대출여부 0으로 초기화
	{
		list[i].borrownum = 0;
	}

	printf("등록한 책 정보\n\n");
	for (i = count - numbook; i < count; i++)
	{
		print();
	}
}

void listofbook()	//등록한 책 정보 리스트
{
	printf("\n\n   책 목록\n\n");
	for (i = 0; i < count; i++)
	{
		print();
	}
}

void searchbook(book list[], char stitle[])		//도서 검색 함수
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

void borrow()	//도서 대출 함수
{
	printf("대출 가능한 책\n");
	for (i = 0; i < count; i++)
	{
		if (list[i].borrownum == 0)
		{
			print();
		}
	}

	int cborrownum = typo("대출할 책 번호를 입력하세요.\n");

	for (i = 0; i < count; i++)
	{
		if (cborrownum == list[i].num)	//대출할 책 번호와 일치하는지 확인
		{
			found = 1;		//일치하면 1
			if (list[i].borrownum == 0)		//대출 가능하면 1로 처리
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

	if (!found)		//일치하는게 없을 경우
	{
		printf("책 번호가 존재하지 않습니다.\n\n");
	}

}

void return_()	//도서 반납 함수
{
	printf("반납 가능한 책\n");		//반납 가능한 책 리스트
	for (i = 0; i < count; i++)
	{
		if (list[i].borrownum == 1)
		{
			print();
		}
	}

	int cborrownum = typo("반납할 책 번호를 입력하세요.\n");

	for (i = 0; i < count; i++)
	{
		if (cborrownum == list[i].num)	//반납할 책 번호와 일치하는지 확인
		{
			found = 1;		//일치하면 1
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

	if (!found)	//일치하는게 없을 경우
	{
		printf("책 번호가 존재하지 않습니다.\n\n");
	}

}

void BACKMENU()		//메뉴로 돌아가는 함수
{
	int back = typo("메뉴로 돌아가시겠습니까 ? \n\nYes[1]	  No[0]\n\n");

	if (back == 0)
	{
		printf("\n프로그램을 종료합니다.\n\n");
		exit(0);
	}
}

void deletebook()	//도서 삭제 함수
{
	printf("삭제 가능한 책 목록\n");

	for (i = 0; i < count; i++)		//대출중인 책 뺀 책 리스트
	{
		if (list[i].borrownum == 0)
		{
			print();
		}
	}

	int delete = typo("삭제할 책 번호를 입력하세요.\n");
	int deletenum = -1;

	for (i = 0; i < count; i++)
	{
		if (delete == list[i].num)	//삭제할 책 번호와 일치하는 번호 찾기
		{
			deletenum = i;
			break;
		}
	}

	if (deletenum != -1)	//삭제할 책 확인
	{
		if (list[deletenum].borrownum == 1)	//대출중인건 불가
		{
			printf("대출 중인 책은 삭제할 수 없습니다.\n");
		}
		else
		{
			for (int j = deletenum; j < count - 1; j++)	//선택한 책 삭제
			{
				list[j] = list[j + 1];
			}
			list[count - 1].num = 0;	//삭제한 배열 초기화
			strcpy(list[count - 1].title, "");
			strcpy(list[count - 1].writer, "");
			strcpy(list[count - 1].publish, "");
			list[count - 1].price = 0;
			list[count - 1].borrownum = 0;
			count--;	//전체 책 수량 줄이기
			for (int j = 0; j < count; j++)		//배열 책 번호 재조정
			{
				list[j].num = j + 1;	//도서의 번호가 1부터 시작하도록 조정
			}
		}
	}
	else
	{
		printf("책을 찾을 수 없습니다.\n");
	}
}

void print()	//출력 함수
{
	printf("\n\n%d  %s  %s  %s  %d",
		list[i].num, list[i].title, list[i].writer, list[i].publish, list[i].price);
	if (list[i].borrownum == 1) //대출중 표시
	{
		printf("\t대출중...\n");
	}
	else printf("\n\n");
}

int typo(const char* type)	//정수 입력 받는 함수
{
	int num;

	while (1) {
		printf("%s", type);
		if (scanf("%d", &num) == 1 && num >= 0)	//정수가 성공적으로 받으면 1 and 0보다 크거나 같다. 
		{
			break;
		}
		else {
			printf("올바른 숫자를 입력하세요.\n");
			while (getchar() != '\n');  // 입력 버퍼 비우기
		}
	}

	return num;
}
