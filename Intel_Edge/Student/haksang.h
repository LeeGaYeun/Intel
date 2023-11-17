#pragma once
#include <iostream>

class person
{
	char *name = NULL;
public:
	int Age;
	person(const char *Nam, int age) : Age(age)
	{
		rename(Nam);
		//name = new char[strlen(Nam)+1];
		//strcpy(name, Nam);
	}
	person(int age = 0) : Age(age) {}	//NULL 생성자

	person& rename(const char* Nam)
	{
		if(name) delete name;	//name이 널이 아니면(메모리 관리)
		name = new char[strlen(Nam) + 1];
		strcpy(name, Nam);
		return *this;
	}

	void Show()
	{
		printf("%s(%d)", name, Age);
	}

	~person()
	{
		if (name) delete name;
	}
};

class subject
{
	char* su = NULL;
public:
	int Score;
	subject(){}
	subject(const char* Su, int score) : Score(score)	
	{
		resu(Su);
	}
	subject& resu(const char* Su)
	{
		if (su) delete su;
		su = new char[strlen(Su) + 1];
		strcpy(su, Su);
		return *this;
	}
	char* Name() { return (char*)su; }

	void Show()
	{
		printf("%s : %d", su, Score);
	}
};

class haksang : public person
{
	char* Major = NULL;
public:
	int Grade;
	int SubNum = 0;	//수강과목 수
	subject sub[10];// kor, eng;
	haksang(const char* Nam, int age, const char* major, int grade) : person(Nam, age), Grade(grade)
	{
		reMajor(major);
	}

	~haksang()
	{
		if (Major) delete Major;
	}
	void SetSub(const char* Su, int sco)//등록 될때마다 10개까지 쌓이게 됨
	{
		if (SubNum > 10) return;
		sub[SubNum++].resu(Su).Score = sco;
	}
	haksang& reMajor(const char* major)
	{
		if (Major) delete Major;
		Major = new char[strlen(major) + 1];
		strcpy(Major, major);
		return *this;
	}

	void Show()
	{
		((person*)this)->Show(); //홍길서(19) :
		printf(":%s %d학년\n", Major, Grade);	//전자공학과 1학년 /상위클래스에 존재 이름 접근 불가
		for (int i = 0; i < SubNum; i++)
		{
			printf("%s : %d\n", sub[i].Name(), sub[i].Score);
		}
	}
};