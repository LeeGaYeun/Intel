#include "Point.h"

template <typename T>
Point<T>& Point<T>::SetP(Point p)
{
    x = p.x;
    y = p.y;
    return *this;
}

template <typename T>
Point<T>& Point<T>::SetP(T x1, T y1)
{
    this->x = x1;
    this->y = y1;
    return *this;
}

template <typename T>
Point<T>& Point<T>::MoveP(int dx, int dy)
{
    this->x += dx;
    this->y += dy;
    return *this;
}

template <typename T>
double Point<T>::Dist(Point p)
{
    T w = x - p.x;
    T h = y - p.y;
    return sqrt(w * w + h * h);
}

template <typename T>
void Point<T>::viewP(const char* s)
{
    printf("%s(%d,%d)\n", s, x, y);
}

template <typename T>
Point<T>& Point<T>::operator+(Point p)
{
    Point* p1 = new Point(x + p.x, y + p.y);
    return *p1;
}

template <typename T>
Point<T>& Point<T>::operator++()
{
    ++x;
    ++y;
    return *this;
}

template <typename T>
Point<T>& Point<T>::operator++(int)
{
    Point* p1 = new Point(x++, y++);
    return *p1;
}

template <typename T>
double Point<T>::operator*(Point p)
{
    int w = x - p.x;
    int h = y - p.y;
    double a = w * h;
    return ABS(a);
}

template <typename T>
Point3D<T>& Point3D<T>::SetP(Point3D p)
{
    Point<T>::X() = p.X();
    Point<T>::Y() = p.Y();
    z = p.z;
    return *this;
}

template <typename T>
double Point3D<T>::Dist3D(Point3D p)
{
    T w = Point<T>::X() - p.Point<T>::X();
    T h = Point<T>::Y() - p.Point<T>::Y();
    T d = z - p.z;
    return sqrt(w * w + h * h + d * d);
}

template class Point<int>;
template class Point3D<int>;

//double Point::Dist(Point p)
//{
//	int w = x - p.x;
//	int h = y - p.y;
//	return sqrt(w * w + h * h);
//}
//Point& Point::setP(Point p)
//{
//	x = p.x; y = p.y;
//	return *this;
//}
//Point& Point::setP(int x, int y)
//{
//	this->x = x; this->y = y;
//	return *this;
//}
//void Point::viewP(const char* s)	//Point�� �����ִ� ����Լ�
//{
//	printf("%s(%d, %d)\n", s, x, y);
//}
//
//Point& Point::moveP(int offsetx, int offsety)	//�Լ� �̸� argument�� �ڷ�� ���ƾ� �� return Ÿ�� / ���� �̸� ���� �ʿ� ����.
//{
//	this->x += offsetx;	this->y += offsety;
//	return *this;
//}
//Point& Point::operator+(Point p)	//�� �� CurP��, p�� + �������� (���ο� Point��) ��ȯ 
//{
//	Point* p1 = new Point(x + p.x, y + p.y);
//	return *p1;
//}
//
//Point& Point::operator++()	//��ü ���� ������ �����ε�
//{
//	++x; ++y;
//	return *this;
//}
//
//Point& Point::operator++(int)	//��ü ���� ������ �����ε�
//{
//	Point* p1 = new Point(x++, y++);
//	return *p1;
//}
//
//double Point::operator*(Point p)
//{
//	int w = x - p.x;
//	int h = y - p.y;
//	double a = w * h;
//	return ABS(a);
//}
//
//Point3D& Point3D::setP(Point3D p)
//{
//	X() = p.X(); Y() = p.Y(); z = p.z;	//reference�� ��
//	return *this;
//}

