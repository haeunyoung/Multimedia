#include<opencv2/opencv.hpp>
#include<iostream>
#include <string>

using namespace cv;
using namespace std;

int main()
{
    Mat image, rgb,ycbcr,cmy,hsv;


    image = imread("C:/Users/82103/Desktop/Lena_color.png", IMREAD_COLOR);
    rgb = Mat::zeros(image.size(), CV_8U);
    ycbcr = Mat::zeros(image.size(), CV_8U);
    cmy = Mat::zeros(image.size(), CV_8U);
    hsv = Mat::zeros(image.size(), CV_8U);
    Mat sharpen_image = Mat::zeros(image.size(), CV_8U);
    if (!image.data) {
        printf("Could not open or find the image"); return -1;
    }

    return 0;

    *CMY* /
        for (int y = 0; y < image.rows; y++)
        {
            for (int x = 0; x < image.cols; x++)
            {

                for (int c = 0; c < 3; c++) {
                    CMY.at<Vec3b>(y, x)[2 - c] = 1 - image.at<Vec3b>(y, x)[c];
                }
            }
        }
}