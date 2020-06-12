#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
double alpha; // contrast control
int beta;  // brightness control

int main()
{
    Mat src = imread("C:/Users/82103/Desktop/Lena_color.png");
    Mat dst = Mat::zeros(src.size(), src.type());
  
    Point2f srcTri[3];
    Point2f dstTri[3];

    Mat warp_mat(2, 3, CV_32FC1);
 
    srcTri[0] = Point2f(0, 0);
    srcTri[1] = Point2f(src.cols-1, 0);
    srcTri[2] = Point2f(0, src.rows-1);

    dstTri[0] = Point2f(src.cols*0.0, src.rows*1.0);
    dstTri[1] = Point2f(src.cols * 0.33, src.rows * 0.33);
    dstTri[2] = Point2f(src.cols * 0.33, src.rows * 0.33);

    warp_mat = getAffineTransform(srcTri, dstTri);
    warpAffine(src, dst, warp_mat, dst.size());

    namedWindow("original image", 1);
    imshow("original image", src);

    namedWindow("New Image", 1);
    imshow("New Image", dst);

    waitKey(0);
    return 0;

}