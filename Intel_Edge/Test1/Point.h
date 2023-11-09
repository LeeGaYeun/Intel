#pragma once
//extern double sqrt(double);
#include <iostream>
#define ABS(x)		(((x)<0)?()-(x)):(x))

class Point
{
private:
public:
	int x;	//내부에서 x는 접근 가능(public에 있자냐), but 외부에선 불가능 Point3D에선 못사용
	int y;

	Point(int x1 = 0, int y1 = 0) : x(x1), y(y1) {}
	//Point(Point &p)	//완성된 객체
	Point& setP(Point p);	//Self-Reference 자기 자신의 포인터를 돌려준다
	Point& setP(int x, int y);
	double Dist(Point p);	//Distance
	void viewP(const char *s = NULL);	//View Current Point (s값 지정 x -> NULL) 
	Point& moveP(int offsetx, int offsety);	//Move Point position
	int& X() { return x; };	
	int& Y() { return y; };	// return 10; 은 안씀 상수에 대해 reference할 수 없어서
	Point& operator+(Point p);
	Point& operator++();	//선행 연산자
	Point& operator++(int);	//후행 연산자
	double operator*(Point p);	//두개의 점이 이루는 사각형의 면적을 구하시오 (double)

};

class Point3D : public Point	//3차원 거리 구하기
{
private:
	int z;
public:
	Point3D(int x = 0, int y = 0, int z = 0) : Point(x, y), z(z)	//반드시 상위 생성자 호출
	{}
	Point3D& setP(Point3D p);
	double Dist3D(Point3D p)
	{
		int w = X() - p.X();	//p.x 컴파일 오류. x가 private로 묶여서 X()가능 public에 있잖여
		int h = y - p.y;
		int d = z - p.z;	//내부적으로 접근 가능하니까 z는 함수형으로 안쓴다요	
		return sqrt(w * w + h * h + d * d);
	}
};