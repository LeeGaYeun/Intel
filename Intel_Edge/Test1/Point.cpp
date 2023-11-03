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
