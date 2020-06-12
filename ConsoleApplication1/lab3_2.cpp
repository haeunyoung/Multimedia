#include<opencv2/opencv.hpp>
#include<iostream>
#include <string>

using namespace cv;
using namespace std;

int main()
{
    int n;
    Mat image, smoothImage;
    std::cout << "Enter N: ";
    std::cin >> n;
    
    image = imread("C:/Users/82103/Desktop/Lena_color.png", IMREAD_GRAYSCALE);
    smoothImage = Mat::zeros(image.size(), image.type());
    if (!image.data) { 
        printf("Could not open or find the image"); return -1; 
    }

    double sum,avg;
    int count;
    for (int y = 0; y < image.rows; y++)
    {
        for (int x = 0; x < image.cols; x++)
        {
            sum = 0;
            avg = 0;
            count = 0;
        
            for (int x_row = x-(n / 2); x_row <= x+(n / 2); x_row++)
            {
                for (int y_row = y-(n / 2); y_row <= y+(n / 2); y_row++)
                {
                    if (y_row >= 0 &&x_row >= 0 && y_row < image.rows && x_row < image.cols)
                    {
                        count++;
                        sum += image.at<uchar>(y_row, x_row);
                    }
                }
            }
            avg = sum / count;
            smoothImage.at<uchar>(y, x) =avg;
        }
    }

    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", smoothImage);

    waitKey(0);
    return 0;
}