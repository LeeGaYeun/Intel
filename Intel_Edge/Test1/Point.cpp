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
Point& Point::operator+(Point p)	//�� �� CurP��, p�� + �������� (���ο� Point��) ��ȯ 
{
	Point *p1 = new Point(x + p.x,	y + p.y);
	return *p1;
}

Point& Point::operator++()	//��ü ���� ������ �����ε�
{
	++x; ++y;
	return *this;
}

Point& Point::operator++(int)	//��ü ���� ������ �����ε�
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
	X() = p.X(); Y() = p.Y(); z = p.z;	//reference�� ��
	return *this;
}
