/*
String  class:
목표:  배열클래스를 이용한 문자열 처리 클래스 작성

구현:  문자열을 다루른 데 적합한 String 클래스를 만들고,  연산자를 오버로딩하여 문자열에 대한 연산을 수행하세요.

설명:   +,<<,!=  , ==, += 연산자 오버로딩. 찾기, 자르기, 바꾸기 연산 수행
*/

#include <iostream>
#include <cstring>
using namespace std;

class ArrTest {
private:
    double* arr;
    int Len;  // 배열 요소의 수

public:
    // 생성자
    ArrTest(int size) : Len(size) {
        arr = new double[size];
    }

    // 소멸자
    ~ArrTest() {
        delete[] arr;
    }

    // 배열의 길이 반환
    int length() {
        return Len;
    }

    // 배열 요소에 접근
    double& operator[](int idx) {
        if (idx < 0 || idx > Len - 1) {
            std::cout << "Out of bound\n";
            exit(1);
        }
        return arr[idx];
    }

    // + 연산자 오버로딩
    ArrTest operator+(ArrTest& br) {
        int l = Len + br.length();
        ArrTest cr(l);
        memcpy(cr.arr, arr, Len * sizeof(double));
        memcpy(cr.arr + Len, br.arr, br.length() * sizeof(double));
        return cr;
    }

    // += 연산자 오버로딩
    ArrTest& operator+=(ArrTest& br) {
        append(br);
        return *this;
    }

    // == 연산자 오버로딩
    bool operator==(ArrTest& br) {
        if (Len != br.length()) return false;
        for (int i = 0; i < Len; i++) {
            if (arr[i] != br[i]) return false;
        }
        return true;
    }

    // 배열 출력을 위한 연산자 오버로딩
    friend std::ostream& operator<<(std::ostream& os, ArrTest& ar) {
        std::cout << "{";
        for (int i = 0; i < ar.Len - 1; i++)
            std::cout << ar.arr[i] << ",";
        std::cout << ar.arr[ar.Len - 1] << " }";
        return os;
    }

    // 배열 길이 확장
    void append(int size) {
        double* arr1 = new double[Len + size];
        memcpy(arr1, arr, Len * sizeof(double));
        delete[] arr;
        arr = arr1;
        Len += size;
    }

    // 다른 배열을 현재 배열에 추가
    void append(ArrTest& brr) {
        double* arr1 = new double[Len + brr.length()];
        memcpy(arr1, arr, Len * sizeof(double));
        memcpy(arr1 + Len, brr.arr, brr.length() * sizeof(double));
        delete[] arr;
        arr = arr1;
        Len += brr.length();
    }
};

class Func {
public:
    int operator()(int a, int b) {
        return a * b;
    }

    double operator()(double a, double b) {
        return a * b;
    }

    ArrTest& operator()(ArrTest& b1, ArrTest& b2) {
        return b1 += b2;
    }
};

int main() {
    double a1[] = { 15.1, 12.1, 13.1, 11.1, 14.1 };
    ArrTest arr(5);
    for (int i = 0; i < 5; i++) arr[i] = a1[i];

    double a2[] = { 21.1, 22.1, 23.1, 24.1, 25.1 };
    ArrTest brr(5);
    for (int i = 0; i < 5; i++) brr[i] = a2[i];

    if (arr == brr) std::cout << "Same sequence...\n";

    ArrTest crr = arr + brr;

    Func mul;
    std::cout << mul(2, 3) << "\n";
    std::cout << mul(2.5, 3.7) << "\n";
    std::cout << mul(arr, brr) << "\n";
    std::cout << (arr += brr) << "\n";
    std::cout << crr << "\n";

    return 0;
}
