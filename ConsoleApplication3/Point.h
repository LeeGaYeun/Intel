#include <iostream>
#define MIN(x, y)   (((x)>(y))? (y) : (x))
#define MAX(x, y)   (((x)<(y))? (y) : (x))

class Point
{
private:  //default 접근 지시자 (외부 참조 불가)


public:   //  "   (외부 참조 가능)

    int x, y, z; //멤버 변수 선언    객체(나 자신)의 좌표
    Point(int x1 = 0, int y1 = 0) : x(x1), y(y1)    //initializer
        // 생성자 정의, 함수적 특성(default , Overload 등)
    {
        z = 0;// x = x1; y = y1;
    }
    void SetP(int x1 = 0, int y1 = 0) { x = x1; y = y1; }

    double Dist(Point p)  //멤버 함수 : 두 점간의 거리 계산. Double 값으로 return
    {
        int w = x - p.x;
        int h = y - p.y;
        return sqrt(w * w + h * h);
    }
    double Dist(Point p1, Point p2)  //멤버 함수 : 두 점(자신을 제외한)의 거리 계산. Double 값으로 return
    {
        int w = p1.x - p2.x;
        int h = p1.y - p2.y;
        return sqrt(w * w + h * h); // (sqrt 자체가 double임)
        /*double d = sqrt(w * w + h * h);
        return d;*/
    }
};

class Rect  //사각형 꼭짓점 구하기
{

    Point p11, p22;   //클래스 변수 선언
    Point LL, LR, UL, UR;
public:
    Rect(Point p1, Point p2) {
        /*int xl = MIN(p1.x, p2.x);
        int xr = MAX(p1.x, p2.x);
        int yl = MIN(p1.y, p2.y);
        int yu = MAX(p1.y, p2.y);
        LL = Point(xl, yl);
        LR = Point(xr, yl);
        UL = Point(xl, yu);
        UR = Point(xr, yu);*/
        p11 = p1;   p22 = p2;
    }
    Point GetLL()
    {
        return Point(MIN(p11.x, p22.x), MIN(p11.y, p22.y));
    }
    Point GetLR()
    {
        return Point(MAX(p11.x, p22.x), MIN(p11.y, p22.y));
    }
    Point GetUL()
    {
        return Point(MIN(p11.x, p22.x), MAX(p11.y, p22.y));
    }
    Point GetUR()
    {
        return Point(MAX(p11.x, p22.x), MAX(p11.y, p22.y));
    }
};
