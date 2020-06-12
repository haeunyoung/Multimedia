
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int h, w;
float x_scale, y_scale;
Mat src;
Mat dst;
Mat opencv_dst;

void nearest()
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {

            float x = floor(j / x_scale);
            float y = floor(i / y_scale);
            for (int c = 0; c < 3; c++)
                dst.at<Vec3b>(i, j)[c] = src.at<Vec3b>(y, x)[c];
        }
    }
}
int main()
{
    cin >> x_scale >> y_scale;
    src = imread("C:/Users/82103/Desktop/Lena_color.png");
    dst = Mat::zeros(src.rows * y_scale, src.cols * x_scale, src.type());
    opencv_dst = Mat::zeros(src.rows + y_scale, src.cols + x_scale, src.type());
    h = dst.rows;
    w = dst.cols;
    if (!src.data) {
        printf("Could not open or find the image"); return -1;
    }

    resize(src, opencv_dst, Size(), x_scale, y_scale, INTER_NEAREST);

    nearest();

    namedWindow("original image", 1);
    imshow("original image", src);

    namedWindow("New Image using opencv", 1);
    imshow("New Image using opencv", opencv_dst);

    namedWindow("New Image", 1);
    imshow("New Image", dst);

    waitKey(0);
    return 0;

}