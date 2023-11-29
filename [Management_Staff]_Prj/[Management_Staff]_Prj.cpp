/*
직원 관리 시스템:
목표: 클래스 상속을 사용하여 직원 계층 구조 만들기

구현: Employee라는 기본 클래스를 만들고, Manager와 Developer 등의 파생 클래스를 만들어 보세요. 
각 클래스에는 직원 정보를 출력하는 가상 함수가 있어야 합니다.

설명: Employee 클래스를 만들고, Manager와 Developer 등의 파생 클래스를 생성하여 직원들의 정보를 다룹니다. 
가상 함수를 이용하여 각 직원의 정보를 출력하는 함수를 작성하세요.
*/
#include <iostream>
#include <string>
using namespace std;

//class Employee
//{
//protected:
//	int ID;
//	string NAME;
//	int AGE;
//public:
//	Employee(int id, string &n, int a) : ID(id), NAME(n), AGE(a) {}
//	virtual void Print()
//	{
//		printf("ID : %d\nName : %s\nAGE : %d\n", ID, NAME, AGE);
//	}
//};
//
//class Manager : public Employee
//{
//	string TITLE;
//public:
//	Manager(int id, string& n, int a, string& t) : Employee(id, n, a), TITLE(t) {}
//	virtual void Print()
//	{
//		Employee::Print();
//		printf("TITLE : %s\n[Manager]\n", TITLE);
//	}
//};
//
//class Developer : public Employee
//{
//	string LAN;
//public:
//	Developer(int id, string& n, int a, string& l) : Employee(id, n, a), LAN(l) {}
//	virtual void Print()
//	{
//		Employee::Print();
//		printf("LANGUAGE : %s\n[Developer]\n", LAN);
//	}
//};

class Employee
{
protected:
    int ID;
    string NAME;
    int AGE;

public:
    Employee(int id, const string& n, int a) : ID(id), NAME(n), AGE(a) {}

    virtual void Print()
    {
        printf("ID : %d\tName : %s\tAGE : %d\t", ID, NAME.c_str(), AGE);
    }
};

class Manager : public Employee
{
    string TITLE;

public:
    Manager(int id, const string& n, int a, const string& t) : Employee(id, n, a), TITLE(t) {}

    virtual void Print()
    {
        Employee::Print();
        printf("TITLE : %s\t[Manager]\n", TITLE.c_str());
    }
};

class Developer : public Employee
{
    string LAN;

public:
    Developer(int id, const string& n, int a, const string& l) : Employee(id, n, a), LAN(l) {}

    virtual void Print()
    {
        Employee::Print();
        printf("LANGUAGE : %s\t[Developer]\n", LAN.c_str());
    }
};

int main()
{
	Manager m1(230502, "LEE", 24, "Staff");
	Developer d1(230101, "KIM", 25, "C++");
    m1.Print();
    d1.Print();
}

