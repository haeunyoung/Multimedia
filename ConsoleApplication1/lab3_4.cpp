#include<opencv2/opencv.hpp>
#include<iostream>
#include <string>
#include<math.h>

using namespace cv;
using namespace std;

int main()
{
    Mat image, smoothImage;
    

    image = imread("C:/Users/82103/Desktop/Lena_color.png", IMREAD_GRAYSCALE);
    smoothImage = Mat::zeros(image.size(), CV_8U);
    if (!image.data) {
        printf("Could not open or find the image"); return -1;
    }

   
    int ksize = 3;
    float temp1, temp2;
    float kernelx[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
    float kernely[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
    for (int y = ksize/2; y <image.rows-ksize/2; y++)
    {
        for (int x = ksize/2; x <image.cols-ksize/2; x++)
        {
            temp1 = 0; temp2 = 0;

            for (int i =0; i <ksize; i++)
            {
                for (int j = 0; j < ksize ; j++)
                {

                    temp1 += image.at<uchar>(y + (i - ksize / 2), x + (j - ksize / 2)) * kernelx[i][j];
                    temp2 += image.at<uchar>(y + (i - ksize / 2), x + (j - ksize / 2)) * kernely[i][j];
                    smoothImage.at<uchar> (y, x)= sqrt(temp1 * temp1 + temp2 * temp2);
                }
            }
           
        }
    }

    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", smoothImage);

    waitKey(0);
    return 0;
}