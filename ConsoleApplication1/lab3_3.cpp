#include<opencv2/opencv.hpp>
#include<iostream>
#include <string>
#include<math.h>
#include<algorithm>

using namespace cv;
using namespace std;

int main()
{
    Mat image, Median_image;


    image = imread("C:/Users/82103/Desktop/lena_noise.png");
    Median_image = Mat::zeros(image.size(), image.type());
    
    if (!image.data) {
        printf("Could not open or find the image"); return -1;
    }


    int ksize = 3;
    float temp[9] = {0,};
    float median = 0;
    for (int y = ksize / 2; y < image.rows - ksize / 2; y++)
    {
        for (int x = ksize / 2; x < image.cols - ksize / 2; x++)
        {
            
            for (int c = 0; c < 3; c++)
            {
                for (int i = 0; i < ksize ; i++)
                {
                    for (int j = 0; j < ksize; j++)
                    {
                        temp[i*ksize+j] = image.at<Vec3b>(y+(i - ksize / 2), x + (j - ksize / 2))[c];
                        
                    }
                }
                sort(temp, temp + 9);
                median = temp[(ksize * ksize) / 2];
                Median_image.at< Vec3b >(y, x)[c] = saturate_cast<uchar>(median);
            }

        }
    }
    namedWindow("original image", 1);
    namedWindow("Median Image", 1);
    imshow("original image", image);
    imshow("Median Image", Median_image);

    waitKey(0);
    return 0;
}