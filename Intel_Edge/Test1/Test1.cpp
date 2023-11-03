#include <iostream>
#include "Point.h"

int main()
{
	Point p1(10, 10), p2, p3;
	p1.viewP("P1"); p2.viewP();	p3.viewP();	//" " -> 자동으로 const 붙여짐(문자열 붙였는데 빨간줄 -> const 쓰셈)
	Point p4 = p3, p5(p2);	//p3의 x, y는 p4에 각각 대입이 된다

	//p1.viewP("P1"); p2.viewP("P2");	p3.viewP("P3");
	p2.setP(Point(20, 30)).viewP("P2");
	p3.setP(40, 70).viewP("P3");
	
	printf("\nmoveP 함수 만들기\n\n");
	p1.moveP(10, 20).viewP("P1");
	p2.moveP(30, 40).viewP("P2");
	p3.moveP(50, 60).viewP("P3");

	//printf("Point print Test..P1(%d, %d)\n\n", p1.x, p1.y); 컴파일 오류. x, y가 private로 들어갔기 때문 -> 표기하고 싶으면 함수 만드셈
	printf("Point print Test..P1(%d, %d)\n\n", p1.X(), p1.Y());	//p1.X() 단방향
	p1.X() = 10;	p1.Y() = 10;
	printf("Point Ref. Access Test.."); p1.viewP("P1");
	
	Point3D pp0, pp1(10, 20, 30);
	double d = pp1.Dist3D(pp0);
	double d2 = pp0.Dist(Point(10, 20));//point에 있는 함수(상위 클래스)
	double d3 = pp0.Dist3D(pp1);	
	printf("pp0(0, 0, 0)과 pp1(10, 20, 30)의 거리는 %f\n", d);
	printf("pp0(0, 0, 0)과 pp1(10, 20, 30)의 거리는 %f\n", d2);
	printf("pp0(0, 0, 0)과 pp1(10, 20, 30)의 거리는 %f\n", d3);

}