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
	person(int age = 0) : Age(age) {}	//NULL ������

	person& rename(const char* Nam)
	{
		if(name) delete name;	//name�� ���� �ƴϸ�(�޸� ����)
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
	int SubNum = 0;	//�������� ��
	subject sub[10];// kor, eng;
	haksang(const char* Nam, int age, const char* major, int grade) : person(Nam, age), Grade(grade)
	{
		reMajor(major);
	}

	~haksang()
	{
		if (Major) delete Major;
	}
	void SetSub(const char* Su, int sco)//��� �ɶ����� 10������ ���̰� ��
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
		((person*)this)->Show(); //ȫ�漭(19) :
		printf(":%s %d�г�\n", Major, Grade);	//���ڰ��а� 1�г� /����Ŭ������ ���� �̸� ���� �Ұ�
		for (int i = 0; i < SubNum; i++)
		{
			printf("%s : %d\n", sub[i].Name(), sub[i].Score);
		}
	}
};