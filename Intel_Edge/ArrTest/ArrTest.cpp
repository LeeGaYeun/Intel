#include <iostream>
#include <string>
using namespace std;

template <typename T>
class ArrTest
{
private:
    T* arr;
    int Len;  // 배열 요소의 수   바뀔리가 없는건 자료형 지정
public:
    ArrTest(int size) : Len(size)   //배열 크기에 따라 동적 할당
    {
        arr = new T[size];
    }
    ~ArrTest()
    {
        delete arr;
    }
    int length()    //배열의 길이 반환
    {
        return Len;
    }
    T& operator[](int idx)   // calling sequence : arr[n]
    {
        if (idx<0 || idx > Len - 1)
        {
            std::cout << "Out of bound\n"; exit(1);
        }
        return arr[idx];
    }
     
    ArrTest<T>& operator+(ArrTest<T>& br)
    {
        int l = Len + br.length();                    //총 길이
        ArrTest<T>* cr = new ArrTest<T>(l);           //새로운 객체 생성
        //T* arr1 = new T[Len + brr.length()];        // 새로운 배열 할당
        memcpy(cr->arr, arr, Len * sizeof(T));
        memcpy(cr->arr + Len, br.arr, br.length() * sizeof(T));

        return *cr;
    }

    ArrTest<T>& operator+=(ArrTest<T>& br)  //calling sequence : arr += brr
    {
        return this->append(br);
    }

    bool operator==(ArrTest<T>& br)         //calling sequence : if(arr == brr)
    {
        if (Len != br.length())  return false;
        for (int i = 0; i < Len; i++)
        {
            if (arr[i] != br[i]) return false;
        }
        return true;
    }

    void show()
    {
        int i;
        printf("{");
        for (i = 0; i < Len - 1; i++)
            std::cout << arr[i] << ",";    std::cout << arr[i];
        printf(" }\n");
    }
    ArrTest& append(int size)         //배열 길이 확장
    {
        T* arr1 = new T[Len + size];  // 확장된 메모리
        memcpy(arr1, arr, Len * sizeof(T));
        delete arr;
        arr = arr1;
        Len += size;
        return *this;
    }
    ArrTest& append(ArrTest& brr)             //다른 배열을 현재 배열에 추가
    {
        T* arr1 = new T[Len + brr.length()];  // 확장된 메모리
        memcpy(arr1, arr, Len * sizeof(T));
        memcpy(arr1 + Len, brr.arr, brr.length() * sizeof(T));
        delete arr;
        arr = arr1;
        Len += brr.length();
        return *this;
    }
    friend ostream& operator<<(ostream& os, ArrTest& ar)    //배열 출력을 위한 연산자 오버로딩
    {
        int i;
        printf("{");
        for (i = 0; i < ar.Len - 1; i++)
            std::cout << ar.arr[i] << ",";    std::cout << ar.arr[i];
        printf(" }");
        return os;
    }
  
    //ArrTest& operator+=(ArrTest& other)   // calling sequence : arr[n]
    //{
    //    return this->append(other);
    //    //arr의 append 함수를 사용하여 입력을 brr을 넣는다.
    //    //arr.apeend(brr);
    //}

};
//void ArrTest<T>::show()   // { 1 2 3 4 5} ==> { 1,2,3,4,5 }
//ArrTest& ArrTest::append(int size)  // size :  total ?  
//ArrTest& ArrTest::append(ArrTest& brr)  // size :  total ?  

class Func
{
public:
    int operator()(int a, int b)
    {
        return a * b;
    }
    double operator()(double a, double b)
    {
        return a * b;
    }
    ArrTest<int>& operator()(ArrTest<int>& b1, ArrTest<int>& b2)  // size :  total ?  
    {
        return b1.append(b2);
    }
    ArrTest<double>& operator()(ArrTest<double>& b1, ArrTest<double>& b2)  // size :  total ?  
    {
        return b1.append(b2);
    }
};
//int func(int arg) {}
int main()
{
    double a1[] = { 15.1,12.1,13.1,11.1,14.1 };
    ArrTest<double> arr(5); //class에서 템플릿은 자료형을 나타내줘야 한다.(함수는 x)
    for (int i = 0; i < 5; i++)             arr[i] = a1[i];
    //for (int i = 0; i < arr.length() ; i++) printf("ArrTest[%d] = %d\n", i, arr[i]);
    //
    double a2[] = { 21.1,22.1,23.1,24.1,25.1 };
    ArrTest<double> brr(5);
    for (int i = 0; i < 5; i++)             brr[i] = a2[i];
    //for (int i = 0; i < brr.length() ; i++) printf("ArrTest[%d] = %d\n", i, brr[i]);
    //
    //int n = arr.length();
    //printf("배열 확장 %d --> %d\n\n", n, arr.append(brr).length());
    // 
    //for (int i = 0; i < arr.length() ; i++) printf("ArrTest[%d] = %d\n", i, arr[i]);
    
    if (arr == brr)  printf("Same sequence...\n");

    ArrTest<double> crr = arr + brr;

    Func mul;
    std::cout << mul(2, 3) << "\n";
    std::cout << mul(2.5, 3.7) << "\n";
    std::cout << mul(arr, brr) << "\n"; //mul(arr, brr).show
    std::cout << (arr += brr) << "\n";
    std::cout << crr << "\n";

    string s = "안녕하세요";
    cout << s << endl;
    cout << s.substr(2, 2) << endl; 
}