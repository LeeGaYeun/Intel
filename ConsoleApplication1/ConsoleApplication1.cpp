#include <iostream>

#define SQUARE(x) (x * x)   //매크로 함수 예제
#define ABS(y) (y >= 0 ? y : (-1)*(y))  //모든 인수에 반드시 괄호
//전역변수/데이터 타입 선언

/*typedef struct Point
{
    int x;
    int y;
}Point2D;
double Dist(Point2D p1, Point2D p2); */

//class Point
//{
//public:
//    int x;
//    int y;
//    Point(int x1, int y1)
//    {
//        x = x1; y = y1;
//    }
//    double Dist(Point p);//이미 argument가 들어가 있어서 다른 점이 필요
//};
class area
{
public:
    int x, y;
    area(int x1, int y1)
    {
        x = x1; y = y1;
    }
    int Square(area p);
};

int area::Square(area p)
{
    int w = ABS(x - p.x);
    int h = ABS(y - p.y);
    int a = w * h;
    return a;
}

//double Point::Dist(Point p)
//{
//    int w = x - p.x;
//    int h = y - p.y;
//    int w1 = w * w;
//    int h1 = h * h;
//    double d = sqrt(w * w + h * h);
//    return d;
//}

//int Square::

int main()
{
    //std::cout << "안녕하세요. C++의 세계에 오신걸 환영합니다!\n";
    /*printf("안녕하세요. C++의 세계에 오신걸 환영합니다!\n\n");
    
    printf("2의 제곱 : %d\n", SQUARE(2));
    printf("5의 제곱 : %d\n", SQUARE(-5));

    printf("절대값 %d\n", ABS(-15));*/
    
    
    
   area p1(10, 10), p2(20, 30); //p1, p2 생성자와의 타입이 맞아야 함 (지금 int형)
   
   //p1.x = 10; p1.y = 10;
   //p2.x = 20; p2.y = 30;

    //double d = p1.Dist(p2);
   // printf("두 점 p1(%d, %d), p2(%d, %d)의 거리는 %.2f", p1.x, p1.y, p2.x, p2.y, d);

   // Point p1(10), p2(20);
   double a = p1.Square(p2);//p2 객체(구조체의 변수)로 
   double a2 = p1.Square(p2);
   printf("넓이는 %.2f", a2);
}

//double Dist(Point2D p1, Point2D p2)
//{
//    int w = ABS(p1.x - p2.x);
//    int h = ABS(p1.y - p2.y);
//    int w1 = w * w;
//    int h1 = h * h;
//    double d = sqrt(w1 + h1);
//    return d;
//}