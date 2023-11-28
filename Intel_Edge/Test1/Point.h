#pragma once
#include <iostream>

#define ABS(x) (((x)<0)?(-(x)):(x))

template <typename T>
class Point
{
private:
    T x;
    T y;
public:
    Point(T x1 = 0, T y1 = 0) : x(x1), y(y1) {}

    Point& SetP(Point p);
    Point& SetP(T x1, T y1);
    Point& MoveP(int dx, int dy);
    double Dist(Point p);
    void viewP(const char* s = NULL);
    int& X() { return x; };
    int& Y() { return y; };
    Point& operator+(Point p);
    Point& operator++();
    Point& operator++(int);
    double operator*(Point p);
};

template <typename T>
class Point3D : public Point<T>
{
private:
    T z;

public:
    Point3D(T x = 0, T y = 0, T z = 0) : Point<T>(x, y), z(z) {}

    Point3D& SetP(Point3D p);
    double Dist3D(Point3D p);
};


//class Point
//{
//private:
//public:
//	int x;	//���ο��� x�� ���� ����(public�� ���ڳ�), but �ܺο��� �Ұ��� Point3D���� �����
//	int y;
//
//	Point(int x1 = 0, int y1 = 0) : x(x1), y(y1) {}
//	//Point(Point &p)	//�ϼ��� ��ü
//	Point& setP(Point p);	//Self-Reference �ڱ� �ڽ��� �����͸� �����ش�
//	Point& setP(int x, int y);
//	double Dist(Point p);	//Distance
//	void viewP(const char* s = NULL);	//View Current Point (s�� ���� x -> NULL) 
//	Point& moveP(int offsetx, int offsety);	//Move Point position
//	int& X() { return x; };
//	int& Y() { return y; };	// return 10; �� �Ⱦ� ����� ���� reference�� �� ���
//	Point& operator+(Point p);
//	Point& operator++();	//���� ������
//	Point& operator++(int);	//���� ������
//	double operator*(Point p);	//�ΰ��� ���� �̷�� �簢���� ������ ���Ͻÿ� (double)
//
//};
//
//class Point3D : public Point	//3���� �Ÿ� ���ϱ�
//{
//private:
//	int z;
//public:
//	Point3D(int x = 0, int y = 0, int z = 0) : Point(x, y), z(z)	//�ݵ�� ���� ������ ȣ��
//	{}
//	Point3D& setP(Point3D p);
//	double Dist3D(Point3D p)
//	{
//		int w = X() - p.X();	//p.x ������ ����. x�� private�� ������ X()���� public�� ���ݿ�
//		int h = y - p.y;
//		int d = z - p.z;	//���������� ���� �����ϴϱ� z�� �Լ������� �Ⱦ��ٿ�	
//		return sqrt(w * w + h * h + d * d);
//	}
//};

