#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat src = imread("C:/Users/82103/Desktop/Lena_color.png");
    Mat dst = Mat::zeros(src.size(), src.type());

    if (!src.data) {
        printf("Could not open or find the image"); return -1;
    }
    Point2f srcTri[4];
    Point2f dstTri[4];

    Mat warp_mat(3,3, CV_32FC1);

    srcTri[0] = Point2f(-30, -60);
    srcTri[1] = Point2f(src.cols+50 ,-50);
    srcTri[2] = Point2f(src.cols+100, src.rows +50);
    srcTri[3] = Point2f(-50, src.rows +50);

    dstTri[0] = Point2f(0,0);// 안쪽으로 들어오게 
    dstTri[1] = Point2f(src.cols-1, 0);
    dstTri[2] = Point2f(src.cols - 1, src.rows-1);
    dstTri[3] = Point2f(0,src.rows-1);

    warp_mat = getPerspectiveTransform(srcTri, dstTri);
    warpPerspective(src, dst, warp_mat, dst.size());

    namedWindow("original image", 1);
    imshow("original image", src);

    namedWindow("New Image", 1);
    imshow("New Image", dst);

    waitKey(0);
    return 0;

}