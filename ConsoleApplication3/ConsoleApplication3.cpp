#include <iostream>
#include "Point.h" //파일의 전체 경로
#define MIN(x, y)   (((x)>(y))? (y) : (x))
#define MAX(x, y)   (((x)<(y))? (y) : (x))  

void PrintP(Point p)
{
    printf("Point(%d, %d)\n", p.x, p.y);
}
void swap_v(int a, int b) // Call-by-Value
{
    int t(a);
    printf("[swap] 초기값 a = %d   b = %d\n", a, b);
    a = b;  b = t;
    printf("[swap] 결과값 a = %d   b = %d\n", a, b);
}
void swap_p(int *a, int *b) // Call-by-Reference
{
    int t(*a);  // 사용시는 해당 포인터(주소)의 값
    printf("[swap] 초기값 a = %d   b = %d\n", *a, *b);
    *a = *b;  *b = t;
    printf("[swap] 결과값 a = %d   b = %d\n", *a, *b);
}
//----------------------------------------------------------------------------------
void swap_r(int &a, int &b) // Call-by-Reference (using ref. variables)
{
    int t(a);
    printf("[swap_r] 초기값 a = %d   b = %d\n", a, b);
    a = b;  b = t;
    printf("[swap_r] 결과값 a = %d   b = %d\n", a, b);
}

int main()
{
    Point arr[3];   // 객체 배열 : 3개의 Point 클래스 객체가 default 초기화 됨
    arr[0].SetP(10, 10); PrintP(arr[0]);
    arr[1].SetP(20, 30); PrintP(arr[1]);
    arr[2].SetP(40, 50); PrintP(arr[2]);

    printf("Class Point 객체 크기 : %d\n", sizeof(arr));
    Point* Parr[3]; //각각의 요소에는 실체가 없다 따라서 array마다 초기화가 필요하다
    printf("Point 객체 포인터 배열 크기 : %d\n", sizeof(Parr));
    Parr[0] = new Point(10, 10);  PrintP(*Parr[0]);
    Parr[1] = new Point(20, 30);  PrintP(*Parr[1]);
    Parr[2] = new Point(40, 50);  PrintP(*Parr[2]);

    //포인터(*) 배열
    //Point p1, p2(10, 10), p3(20, 30), p4; // p1은 (0,0) 생성자 정의
    //p4 = p3;
    //double d = p1.Dist(p2);
    //double d1 = p2.Dist(p3);
    //double d2 = p1.Dist(p2, p3); //함수만 이용하기 위한 객체 p1
    //PrintP(p1);     PrintP(p2);     PrintP(p3);
    //PrintP(p4);
    //printf("점간의 거리 계산 : \nd(p1, p2) = %.2f   d1(p2, p3) = %.2f   d2(p2, p3) = %.2f", d, d1, d2);

    //Rect r(p2, p3);
    //printf("\n두 점 \n");
    //PrintP(p2);
    //PrintP(p3);
    //printf("에 의해 정의된 사각형의 꼭지점의 좌표는 \n");
    //PrintP(r.GetLL());
    //PrintP(r.GetLR());
    //PrintP(r.GetUL());
    //PrintP(r.GetUR());

    //Reference 변수 테스트
    //int a(10), b(20);    //a = 10; b = 20;   void swap_r 호출변수와 동기화
    //printf("\n변수 a = %d   b = %d\n", a, b);
    //printf("초기값 a = %d   b = %d\n", a, b);
    ////swap(a, b);   call by vaule
    ////swap_r(&a, &b);   컴파일 오류. 포인터를 받아서 처리한다고 인식하기 때문
    //swap_r(a, b);
    //printf("결과값 a = %d   b = %d\n", a, b);
    ////printf("\n변수 a = %d   b = %d\n", a(30), b(30)); 컴파일 오류. 변수 초기화에만 가능.
    //
    //int n = 1234, n1 = 1000;
    //int& m = n; //초기화 필수
    //printf("[레퍼런스 변수 테스트] n = %d,   m = %d\n", n, m);
    ////&m = n1;  컴파일 오류. 별칭은 선언과 동시에 초기화 해야하기 때문
    //m = 5678;
    //printf("[레퍼런스 변수 테스트] n = %d,   m = %d\n", n, m);
}