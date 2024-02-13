#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
void rotate_(Mat img, Mat& rotate_img, int deg);
int main()
{
   //cout << "Hello OpenCV" << CV_VERSION << endl;
    Mat img; 
    img = imread("images/lena.jpg");

    //auto img = cv::imread("images/lena.jpg");
    //auto i = 10;

    /*Point pt1;
    pt1.x = 10;
    pt1.y = 20;

    Point pt2;
    pt2.x = 20;
    pt2.y = 30;

    Point pt3 = pt1 + pt2;

    cout << pt3 << endl;*/

    /****************size****************/
    /*Size sz1, sz2(10, 20);
    sz1.width = 5;
    sz1.height = 10;*/
    /*cout << sz1.area() << endl;
    cout << sz1 + sz2 << endl;*/

    //Rect
    //Rect rc1(10, 10, 60, 40);
    //Rect rc2;
    //Rect rc3 = rc2 + sz1;
    //

    //Mat mat1(2, 3, CV_8UC3);
    Mat rotate_img;
    int deg = 40;
    //cv::rotate(img, rotate_img, cv::ROTATE_90_COUNTERCLOCKWISE);
    rotate_(img, rotate_img, deg);

    imshow("image", img);
    imshow("rotate_img", rotate_img);
    waitKey();
    return 0;
}

void rotate_(Mat img, Mat& rotate_img, int deg)
{
    //cv::Size s = img.size();
    int height = img.rows;
    int width = img.cols;

    rotate_img = cv::Mat::zeros(img.size(), img.type());
    //rotate_img.create(img.size(), img.type()); // rotate_img를 새로운 이미지로 생성

    double theta = (CV_PI * deg) / (180.0);

    int center_x = width / 2;
    int center_y = height / 2;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int X = static_cast<int>((x - center_x) * cos(theta) - (y - center_y) * sin(theta) + center_x);
            int Y = static_cast<int>((x - center_x) * sin(theta) + (y - center_y) * cos(theta) + center_y);
            if ((X < 0) || (X >= width) || (Y < 0) || (Y >= height))
                continue;
            rotate_img.at<Vec3b>(Y, X) = img.at<Vec3b>(y, x);
        }
    }
}
