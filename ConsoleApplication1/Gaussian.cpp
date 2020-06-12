#include<opencv2/opencv.hpp>
#include<iostream>
#include <string>
#include<math.h>
#include<iomanip>

using namespace cv;
using namespace std;

int main()
{
    int n;
    Mat image, gaussianImage;
    cout << "Enter N: ";
    cin >> n;

    //Load the image
    image = imread("C:/Users/82103/Desktop/Lena_color.png", IMREAD_GRAYSCALE);
    gaussianImage = Mat::zeros(image.size(), image.type());
    if (!image.data) {
        printf("Could not open or find the image"); return -1;
    }

    //intialising sigma to 1.0 ~9.0
    double sigma = 9.0;
   long double r, s = 2.0 * sigma * sigma;
   long double Gkernel[30][30] = {0,};
    double sum=0.0;
   
    //perform  NxN smoothing gaussian filtering for the image
    //for statement by removing the edges
    for (int y = n / 2; y < image.rows - n / 2; y++)
    {
        for (int x = n / 2; x < image.cols - n / 2; x++)
        {
            sum = 0.0;
            //create Gaussian filter 
            for (int i = -n / 2; i <= n / 2; i++)
            {
                for (int j = -n / 2; j <= n / 2; j++)
                {

                    r = sqrt(i * i + j * j);
                    Gkernel[i + n / 2][j + n / 2] = (exp(-(r * r) / s)) / (3.14159265 * s);
                    sum += Gkernel[i + n / 2][j + n / 2];

                }
            }

                double temp1 = 0.0;
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                         //normalizing the kernel
                        Gkernel[i][j] /= sum;
                        
                        temp1 += image.at<uchar>(y + (i - n / 2), x + (j - n / 2)) * Gkernel[i][j];
                    
                    }
                }
            
                gaussianImage.at<uchar>(y, x)=temp1;
        }
        
    }
   
    namedWindow("original image", 1);
    imshow("original image", image);
    namedWindow("Display window", 1);
    imshow("Display window", gaussianImage);
  
   
    waitKey(0);
    return 0;
}