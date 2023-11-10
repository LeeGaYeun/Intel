#include <iostream>
class AAA
{
//private:
//	int a1;
//protected:
//	int a2;
//public:	
//	int a3;
//	AAA() { printf("A\n"); }	//생성자
//	~AAA() { printf("~A\n"); }	//소멸자
//	void name() { printf("class name =  AAA\n"); }
};
class BBB : public AAA	//상속관계
{
//public:
//	int b1;
//	int b2;
//	int b3;
//	BBB() { printf("B\n"); }
//	~BBB() { printf("~B\n"); }	
//	//void Test() { printf("a1 = %d	a2 = %d		a3 = %d\n", a1, a2, a3); }
//	void name() { printf("class name = BBB\n"); }
};
class C	//추상 클래스	(상속을 위한 클래스, 최상의 클랙스)
{
public:
	C() { printf("_C_\n"); }
	virtual void func() = 0	{}//NULL함수면 객체화 안됨 -> 순수 가상 함수
	virtual void func1() = 0 {}
};
class C1 : public C
{
public:
	C1() { printf("_C1_\n"); }
	virtual void func()
	{
		printf("func_in_C1_\n");
	}
};
void func() 
{
	//printf("in function start...\n");
	////AAA *a = new AAA();	//실변수 타입 <-> 포인터 변수(자동으로 소멸되지 않음) -> 명시적인 소멸자 필요 delete 명령어 사용
	//BBB *b = new BBB();
	//b->name();

	//AAA* a = (AAA*)b;
	//a->name();
	//printf("a3 = %d\n", ((AAA*)b)->a3);
	//delete b; //delete a;
	//printf("function end.\n");
}

void func1()
{
	//printf("in function start...\n");
	//AAA* a = new AAA();	//실변수 타입 <-> 포인터 변수(자동으로 소멸되지 않음) -> 명시적인 소멸자 필요 delete 명령어 사용
	//a->name();

	//BBB* b = (BBB*)a;
	//b->name();
	//printf("a3 = %d\n", ((BBB*)a)->b1);
	//delete a;
	//printf("function end.\n");
}

int main()
{
	printf("Program start...\n");
	////AAA a;	//생성자 호출 stack에 생김 (자동 소멸자)
	//BBB b;	//상속받아서 위에 A가 자동으로 생성됨
	//func();	
	////func1();
	
	//C c;
	C1 c1;
	c1.func();
	printf("Program end.\n");
}