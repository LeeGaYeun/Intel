#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void blurring_mean();
void blurring_gaussian();
void sharpen();

int main()
{
    //blurring_mean();
    //blurring_gaussian();
    sharpen();
    return 0;
}

void blurring_mean()
{
    Mat img = imread("../../images/lena.jpg");
    imshow("image", img);

    Mat dst;
    for (size_t i = 1; i < 10; i++)
    {
        blur(img, dst, Size(i, i));
        imshow("blur", dst);
        waitKey(500);
    }

    waitKey();
    destroyAllWindows();
}

void blurring_gaussian()
{
    Mat img = imread("../../images/lena.jpg");
    imshow("image", img);

    Mat dst;
    for (size_t i = 1; i < 10; i++)
    {
        GaussianBlur(img, dst, Size(0, 0), (double)(i));
        imshow("GaussianBlur", dst);
        waitKey(500);
    }

    waitKey();
    destroyAllWindows();
}

void sharpen()
{
    Mat src = imread("../../images/lena.jpg");
    imshow("image", src);

    Mat dst;
    for (size_t i = 1; i < 10; i++)
    {
        Mat blurred;
        GaussianBlur(src, blurred, Size(), i);

        float alpha = 1.f;
        Mat dst = src + (alpha * src - alpha * blurred);

        imshow("blur", blurred);
        imshow("sharpen", dst);
        waitKey(500);
    }

    waitKey();
    destroyAllWindows();
}