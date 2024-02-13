#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void noise_gaussian();
void bilateral();

int main()
{
    //noise_gaussian();
    bilateral();
    return 0;
}

void noise_gaussian()
{
    Mat src = imread("../../images/lena.jpg", IMREAD_GRAYSCALE);
    imshow("image", src);

    for (size_t stddev = 10; stddev <= 30; stddev+= 10)
    {
        Mat noise(src.size(), CV_32SC1);
        randn(noise, 0, stddev);

        Mat dst(src.size(), CV_8SC1);
        add(src, noise, dst, Mat(), CV_8U);

        //imshow("noise", noise);
        imshow("dst", dst);
        waitKey();
    }
    
    waitKey();
    destroyAllWindows();
}

void bilateral()
{
    Mat src = imread("../../images/lena.jpg", IMREAD_GRAYSCALE);

    Mat noise(src.size(), CV_32SC1);
    randn(noise, 0, 5);

    add(src, noise, src, Mat(), CV_8U);
    imshow("image", src);

    Mat dst1;
    GaussianBlur(src, dst1, Size(), 5);
    imshow("dst1", dst1);

    Mat dst2;
    bilateralFilter(src, dst2, -1, 10, 5);
    imshow("dst2", dst2);

    waitKey();
    destroyAllWindows();
}