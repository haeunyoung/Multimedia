#include<opencv2/opencv.hpp>

#include<iostream>
#include <string>

using namespace cv;
using namespace std;

int main()
{
    double a = 0.5;
    double input;
    Mat src1, src2, dst;

    std::cout << "Enter alphga [0-1]";
    std::cin >> input;

    if (input >= 0.0 && input <= 1.0)
    {
        a = input;

    }
    src1 = imread("C:/Users/82103/Desktop/frozen.jpg");
    src2 = imread("C:/Users/82103/Desktop/frozenName.jpg");
    dst = Mat::zeros(src1.size(), src1.type());
    if (!src1.data) { printf("Error loading src1\n"); return -1; }
    if (!src2.data) { printf("Error loading src2\n"); return -1; }
    cv::resize(src2, src2, cv::Size(src1.cols, src1.rows));

    for (int y = 0; y < src1.rows; y++)
    {
        for (int x = 0; x < src1.cols; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                dst.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(a * src1.at<Vec3b>(y, x)[c] + (1 - a) * src2.at<Vec3b>(y, x)[c]);
            }
        }
    }
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", dst);

    waitKey(0);
    return 0;

}