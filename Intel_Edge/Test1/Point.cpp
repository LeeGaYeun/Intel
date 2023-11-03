#include "Point.h"	//Point�� �������
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
void Point::viewP(const char *s)	//Point�� �����ִ� ����Լ�
{
	printf("%s(%d, %d)\n", s, x, y);
}

Point& Point::moveP(int offsetx, int offsety)	//�Լ� �̸� argument�� �ڷ�� ���ƾ� �� return Ÿ�� / ���� �̸� ���� �ʿ� ����.
{
	this->x += offsetx;	this->y += offsety;
	return *this;
}
