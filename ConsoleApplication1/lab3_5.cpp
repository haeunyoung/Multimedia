#include<opencv2/opencv.hpp>
#include<iostream>
#include <string>
#include<math.h>

using namespace cv;
using namespace std;

int main()
{
    Mat image, laplacian_image;


    image = imread("C:/Users/82103/Desktop/Lena_color.png", IMREAD_GRAYSCALE);
    laplacian_image = Mat::zeros(image.size(), CV_8U);
    Mat sharpen_image=Mat::zeros(image.size(), CV_8U);
    if (!image.data) {
        printf("Could not open or find the image"); return -1;
    }


    int ksize = 3;
    float temp1,c=1.0;
    float kernel[3][3] = { {0,-1,0},{-1,4,-1},{0,-1,0} };
    for (int y = ksize / 2; y < image.rows - ksize / 2; y++)
    {
        for (int x = ksize / 2; x < image.cols - ksize / 2; x++)
        {
            temp1 = 0;

            for (int i = 0; i < ksize; i++)
            {
                for (int j = 0; j < ksize; j++)
                {

                    temp1 += image.at<uchar>(y + (i - ksize / 2), x + (j - ksize / 2)) * kernel[i][j];
                    laplacian_image.at<uchar>(y, x) = saturate_cast<uchar>(temp1);
                    sharpen_image.at<uchar>(y, x) = saturate_cast<uchar>(image.at<uchar>(y, x) + c * temp1);
                }
            }

        }
    }
    namedWindow("original image", 1);
    namedWindow("Laplacian Image", 1);
    namedWindow("Enhanced Image", 1);
    imshow("original image", image);
    imshow("Laplacian Image", laplacian_image);
    imshow("Enhanced Image", sharpen_image);

    waitKey(0);
    return 0;
}