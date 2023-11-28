#include <iostream>
#include "Point.h"

//int main()
//{
//	Point p1(10, 10), p2, p3;
//	p1.viewP("P1"); p2.viewP();	p3.viewP();	//" " -> 자동으로 const 붙여짐(문자열 붙였는데 빨간줄 -> const 쓰셈)
//	Point p4 = p3, p5(p2);	//p3의 x, y는 p4에 각각 대입이 된다
//
//	p1.viewP("P1"); p2.viewP("P2");	p3.viewP("P3");
//	p2.setP(Point(20, 30)).viewP("P2");
//	p3.setP(40, 70).viewP("P3");
//	printf("두 점으로 정의되는 사각형의 넓이는  %f 입니다\r\n", p2 * p3);
//
//	printf("\nmoveP 함수 만들기\n\n");
//	p1.moveP(10, 10).viewP("P1");
//	p2.moveP(20, 30).viewP("P2");
//	p3.moveP(40, 70).viewP("P3");
//
//	printf("Point print Test..P1(%d, %d)\n\n", p1.x, p1.y); //컴파일 오류. x, y가 private로 들어갔기 때문 -> 표기하고 싶으면 함수 만드셈
//	printf("Point print Test..P1(%d, %d)\n\n", p1.X(), p1.Y());	//p1.X() 단방향
//	p1.X() = 10;	p1.Y() = 10;
//	printf("Point Ref. Access Test.."); p1.viewP("P1");
//	
//	Point p6 = p1 + p2;
//	printf("Point [Operator+] Test.."); p6.viewP("_P6");
//	printf("Point [Operator++] 후행연산 Test.."); p6++.viewP("_P6");
//	printf("Point [Operator++] 선행연산 Test.."); (++p6).viewP("_P6");	//괄호 안하면 컴파일 오류. 
//
//	
//
//	Point3D pp0, pp1(10, 20, 30);
//	double d = pp1.Dist3D(pp0);
//	double d2 = pp0.Dist(Point(10, 20));//point에 있는 함수(상위 클래스)
//	double d3 = pp0.Dist3D(pp1);	
//	printf("pp0(0, 0, 0)과 pp1(10, 20, 30)의 거리는 %f\n", d);
//	printf("pp0(0, 0, 0)과 pp1(10, 20, 30)의 거리는 %f\n", d2);
//	printf("pp0(0, 0, 0)과 pp1(10, 20, 30)의 거리는 %f\n", d3);
//
//}

int main()
{
    Point<int> p1(10, 10), p2, p3;
    p1.viewP("P1");
    p2.viewP();
    p3.viewP();
    Point<int> p4 = p3, p5(p2);

    p2.SetP(Point<int>(20, 30)).viewP("P2");
    p3.SetP(40, 70).viewP("P3");
    printf("두 점으로 정의되는 사각형의 넓이는 %f 입니다\r\n", p2 * p3);

    Point<int> p6 = p1 + p2;
    printf("Point [Operator+] Test...");
    p6.viewP("_P6");
    printf("Point [Operator++] 후행연산 Test...");
    p6++.viewP("_P6");
    printf("Point [Operator++] 선행연산 Test...");
    (++p6).viewP("_P6");
}