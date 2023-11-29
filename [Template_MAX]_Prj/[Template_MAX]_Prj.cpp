/*
템플릿 함수 최대값 찾기:
목표: 템플릿 함수를 사용하여 배열의 최대값을 찾는 프로그램 작성

구현: 정수, 실수 또는 다른 자료형의 배열에서 최대값을 찾는 템플릿 함수를 작성하세요.

설명: 템플릿 함수를 사용하여 배열의 최대값을 찾는 프로그램을 작성합니다. 다양한 자료형에 대해 동작하는 일반적인 함수를 구현합니다.
*/

#include <iostream>

#define MAX(x, y)   (((x)<(y))? (y) : (x))  

template <typename M>
M FMAX(M array[], int size)
{
	M result = array[0];

	for (int i = 0; i < size; i++)
	{
		result = MAX(result, array[i]);
	}

	return result;
}

template <typename M, int n>
M allsize(M (&)[n])
{
	return n;
}

template <typename M, int n>
void show(M (&array)[n])
{
	M result = FMAX(array, n);
	std::cout << result << std::endl;
}

int main()
{
	int arrint[] = { 10, 6, 8, 4, 9 };
	show(arrint);

	double arrdouble[] = { 15.1, 12.1, 13.1, 11.1, 14.1 };
	show(arrdouble);
	
	char arrchar[] = { 'A', 'b', 'C', 'd', 'E', 'f' };
	show(arrchar);
}