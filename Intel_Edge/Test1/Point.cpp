#include "Point.h"	//Point의 헤더파일
double Point::Dist(Point p)
{
	int w = x - p.x;
	int h = y - p.y;
	return sqrt(w * w + h * h);
}
Point& Point::setP(Point p)
{
	x = p.x; y = p.y;	
	return *this;
}
Point& Point::setP(int x, int y)
{
	this->x = x; this->y = y;	
	return *this;
}
void Point::viewP(const char *s)	//Point에 속해있는 멤버함수
{
	printf("%s(%d, %d)\n", s, x, y);
}

Point& Point::moveP(int offsetx, int offsety)	//함수 이름 argument의 자료명 같아야 함 return 타입 / 변수 이름 같을 필요 없다.
{
	this->x += offsetx;	this->y += offsety;
	return *this;
}
Point& Point::operator+(Point p)	//두 점 CurP와, p의 + 연산결과를 (새로운 Point로) 반환 
{
	Point *p1 = new Point(x + p.x,	y + p.y);
	return *p1;
}

Point& Point::operator++()	//객체 선행 연산자 오버로딩
{
	++x; ++y;
	return *this;
}

Point& Point::operator++(int)	//객체 후행 연산자 오버로딩
{
	Point* p1 = new Point(x++, y++);	
	return *p1;
}

double Point::operator*(Point p)
{
	int w = x - p.x;
	int h = y - p.y;
	double a = w * h;
	return ABS(a);
}

Point3D& Point3D::setP(Point3D p)
{
	X() = p.X(); Y() = p.Y(); z = p.z;	//reference의 힘
	return *this;
}
