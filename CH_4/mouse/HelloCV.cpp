#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat img;
void on_mouse(int event, int x, int y, int flags, void*);

int main()
{
    img = imread("../images/lena.jpg");
    namedWindow("img");
    setMouseCallback("img", on_mouse);

    imshow("img", img);
    waitKey();
    destroyAllWindows();

    return 0;
}

void on_mouse(int event, int x, int y, int flags, void*)
{
    Point ptOld;
    switch (event)
    {
    case EVENT_LBUTTONDOWN:
        ptOld = Point(x, y);
        cout << "left_Down" << x << ", " << y << endl;
        break;

    case EVENT_LBUTTONUP:
        ptOld = Point(x, y);
        cout << "left_Up" << x << ", " << y << endl;
        break;

    case EVENT_MOUSEMOVE:
        if (flags & EVENT_FLAG_LBUTTON)
        {
            line(img, ptOld, Point(x, y), Scalar(0, 0, 255), 2);
            imshow("img", img);
            ptOld = Point(x, y);
        }
        break;

    default:
        break;
    }
}