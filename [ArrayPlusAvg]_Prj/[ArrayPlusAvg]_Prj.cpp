/*
배열 합과 평균
목표: 배열의 합과 평균을 계산하는 함수 작성

구현: 정수로 구성된 배열을 받아 해당 배열의 합과 평균을 계산하는 함수를 작성하세요.

설명: 정수 배열을 받아 배열의 합과 평균을 계산하는 함수를 작성합니다. 함수의 반환 형식은 구조체나 클래스로 할 수 있습니다.
*/

#include <iostream>

class Array
{
private:
    int* arr;
    int Len;
public:
    Array(int size) : Len(size)
    {
        arr = new int[size];
    }

    ~Array()
    {
        delete[] arr;
    }

    int length()
    {
        return Len;
    }

    int& operator[](int idx)
    {
        if (idx<0 || idx > Len - 1)
        {
            std::cout << "Out of bound\n"; exit(1);
        }
        return arr[idx];
    }

    int plus()
    {
        int sum = 0;
        for (int i = 0; i < Len; i++)
        {
            sum += arr[i];
        }
        return sum;
    }

    double average()
    {
        int sum = plus();
        return (double)((sum / Len));
    }
    
    void show()
    {
        int i;
        printf("{");
        for (i = 0; i < Len - 1; i++)
            std::cout << arr[i] << ",";    std::cout << arr[Len - 1];
        printf(" }\n");
    }

};

int main()
{
    int size = 5;
    int array[] = { 2, 4, 6, 8, 10 };
    Array arr(size);
    for (int i = 0; i < 5; i++)
    {
        arr[i] = array[i];
    }

    arr.show();
    printf("합계 : %d\n",arr.plus());
    printf("평균 : %.2f\n",arr.average());
}
