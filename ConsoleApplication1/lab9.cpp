#include <opencv2/opencv.hpp>
#include<cmath>

using namespace cv;
int main()
{
    float cost;
	Mat Left_image = imread("C:/Users/82103/Desktop/tsukuba/scene1.row3.col2.png",IMREAD_GRAYSCALE);
    Mat right_image = imread("C:/Users/82103/Desktop/tsukuba/scene1.row3.col3.png", IMREAD_GRAYSCALE);
    Mat disp=Mat::zeros(Left_image.size(), CV_8U);

    int windowSize = 16;
    int ksize = 5;

    for (int y = ksize / 2; y < Left_image.rows - ksize / 2; y++)
    {
        for (int x = ksize / 2; x < Left_image.cols - ksize / 2; x++)
        {
            int best_disp = 0;
            int min_cost = INT_MAX;

            for (int d = 0; d <= windowSize; d++)
            {
                cost = 0;
                if (x - d - ksize / 2 < 0)
                    break;
                for (int i = 0; i < ksize; i++)
                {
                    for (int j = 0; j < ksize; j++)
                    {
                        cost += pow(Left_image.at<uchar>(y + (i - ksize / 2), x + (j - ksize / 2)) -right_image.at<uchar>(y + (i - ksize / 2), x - d + (j - ksize / 2)), 2);
                    }
                }
                if (min_cost > cost)
                {
                    best_disp = d;
                    min_cost = cost;
                }
            }
            disp.at<uchar>(y, x) = best_disp;
        }
    }

    disp = disp * 10;

    namedWindow("Left image", 1);
    imshow("Left image", Left_image);

    namedWindow("right image", 1);
    imshow("right image", right_image);

    namedWindow("disparity image", 1);
    imshow("disparity image", disp);

    waitKey(0);
    return 0;
}