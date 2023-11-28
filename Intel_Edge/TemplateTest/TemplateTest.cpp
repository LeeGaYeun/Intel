#include <iostream>

template <typename T>
void Swap(T& a, T& b)
{
	T c = a;
	a = b; b = c;
}
template <typename T>
T ABS(T a)
{
	if (a < 0) return -a; return a;
}

int main()
{
	int a = 10, b = 20;
	printf("a=%d   b=%d\n", a, b);
	Swap<int>(a, b);
	printf("a=%d   b=%d\n", a, b);

	double a1 = 2.5, b1 = 3.6;
	printf("a1=%f   b1=%f\n", a1, b1);
	Swap(a1, b1);
	printf("a1=%f   b1=%f\n", a1, b1);
}