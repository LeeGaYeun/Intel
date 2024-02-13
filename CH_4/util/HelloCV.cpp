#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main()
{
    Mat src = imread("../images/airplane2.jpg", IMREAD_COLOR);
    Mat dst = imread("../images/red_sky.jpg", IMREAD_COLOR);

    Mat src_mask(src.rows, src.cols, CV_8UC1);
    Mat dst_mask(dst.rows, dst.cols, CV_8UC1);

    vector<Point> pts;
    pts.push_back(Point(0, 40));
    pts.push_back(Point(150, 60));
    pts.push_back(Point(203, 56));
    pts.push_back(Point(200, 100));
    pts.push_back(Point(88, 103));
    pts.push_back(Point(1, 75));

    fillPoly(src_mask, pts, (255, 255, 255));

    Point center(600, 150);
    Mat output;
    seamlessClone(src, dst, src_mask, center, output, MIXED_CLONE);

    TickMeter tm;
    tm.start();

    for (int j = 0; j < src.rows; j++)
    {
        for (int i = 0; i < src.cols; i++)
        {
            dst_mask.at<uchar>(j, i) = 255 - dst.at<uchar>(j, i);
        }
    }

    tm.stop();
    cout << "Image inverse took " << tm.getTimeMilli() << "ms." << endl;

    imshow("src", src);
    imshow("dst", dst);
    imshow("output", output);

    ////mask file 만들어야 함
    //Mat gray;
    //cvtColor(src, gray, COLOR_BGR2GRAY);
    //Mat mask;
    //threshold(gray, mask, 220.0, 255, THRESH_BINARY);
    //// 파일 저장
    //imwrite("mask_plane.jpg", mask);
    //Mat mask_plane = imread("mask_plane.jpg", IMREAD_GRAYSCALE);
    //Mat dst = imread("../images/red_sky.jpg", IMREAD_COLOR);
    //Mat mask_plane_inv;
    //bitwise_not(mask_plane, mask_plane_inv);
    //Mat output;
    //seamlessClone(src, dst, mask_plane_inv, Point(600, 150), output, MIXED_CLONE);
    //imshow("inv", mask_plane_inv);
    //imshow("output", output);
    //imshow("mask_plane", mask_plane);
    waitKey();
    destroyAllWindows();

    return 0;
}