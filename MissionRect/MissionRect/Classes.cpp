#include "Classes.h"	//Point의 헤더파일
double Point::Dist(Point p)
{
	int w = x - p.x;
	int h = y - p.y;
	return sqrt(w * w + h * h);
}

void Point::Show(const char* s)	//Point에 속해있는 멤버함수
{
	printf("%s(%d, %d)\n", s, x, y);
}

void Point::ShowEx(const char* s)	//Point에 속해있는 멤버함수
{
	std::cout << s << "(" << x << "," << y << ")"<<std::endl;
	printf("%s(%d, %d)", s, x, y);
}


Point& Point::operator+(Point p)	//두 점 CurP와, p의 + 연산결과를 (새로운 Point로) 반환 
{
	p1 = new Point(x + p.x, y + p.y);	//*p1 임시객체 new에 대한 소멸자가 없다 
	return *p1;
}

Rect& Rect::Show(const char* s)	//RECT(P1(x1, y1), P2(x2, y2))
{
	printf("%s(", s);
	LL.ShowEx("LL");
	UR.ShowEx("UR");
	printf(")\n");
	return *this;
}

double Rect::Area()
{
	return (double) (ABS((p1.x - p2.x) * (p1.y - p2.y)));
}
Rect& Rect::operator+(Rect r)
{
	int x1 = MIN(MIN(this->x1, this->x2), MIN(r.x1, r.x2));
	int x2 = MAX(MAX(this->x1, this->x2), MAX(r.x1, r.x2));
	int y1 = MIN(MIN(this->y1, this->y2), MIN(r.y1, r.y2));
	int y2 = MAX(MAX(this->y1, this->y2), MAX(r.y1, r.y2));

	return *(new Rect(x1, y1, x2, y2));
}
Rect& Rect::operator-(Rect r)
{
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;
	Rect& rr = *this;

	//두 사각형이 겹치지 않는 경우 0 RECT 반환
	if (rr.LR.x < rr.LL.x || rr.LL.x > r.LR.x) return *(new Rect(0, 0, 0, 0));;
	if (rr.UL.y < rr.LL.y || rr.LL.y > r.UL.y) return *(new Rect(0, 0, 0, 0));;
	
	x1 = MIN(MIN(rr.x1, rr.x2), MIN(r.x1, r.x2));
	x2 = MAX(rr.LL.x, r.LL.x); 
	x3 = MIN(rr.LR.x, r.LR.x); 
	x4 = MAX(MAX(rr.x1, rr.x2), MAX(r.x1, r.x2));

	y1 = MIN(MIN(rr.y1, rr.y2), MIN(r.y1, r.y2));
	y2 = MIN(rr.UL.y, r.UL.y);
	y3 = MAX(rr.LL.y, r.LL.y);
	y4 = MAX(MAX(rr.y1, rr.y2), MAX(r.y1, r.y2));
	
	if (r.LL.y == x1) {y2 = rr.LL.y; y3 = r.UR.y;}
	
	return *(new Rect(x2, y2, x3, y3));
}
double Rect::operator*(Rect r)
{
	double d1 = Area();
	double d2 = r.Area();
	double d3 = (*(this) - r).Area();

	return d1 + d2 - d3;
}

