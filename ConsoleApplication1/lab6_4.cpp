#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
//dst row, cols
int h, w;
float x_scale,y_scale;
Mat src;
Mat dst;
//image using opencv library
Mat opencv_dst;

void bilinear()
{

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            //scaling size
            int x = floor(j /x_scale);
            int y = floor(i / y_scale);

            //2D seperable
            //distance (s)
            double fx1 = (double)j / (double)x_scale - (double)x;
            //distannce 1-s
            double fx2 = 1 - fx1;

            double fy1= (double)i / (double)y_scale - (double)y;
            double fy2 = 1 - fy1;

            //Find the weight according to the distance.
            double w1 = fx2 * fy2;
            double w2 = fx1 * fy2;
            double w3 = fx2 * fy1;
            double w4 = fx1 * fy1;
            Vec3b p1, p2, p3, p4;
            if (i < h - y_scale && j < w - x_scale)
            {  //The distance is inversely multiplied by the weight.
                p1 = src.at<Vec3b>(y, x);
                p2 = src.at<Vec3b>(y, x + 1);
                p3 = src.at<Vec3b>(y + 1, x);
                p4 = src.at<Vec3b>(y + 1, x + 1);
               

            }
            else {
            //boundary handling
            //mirroring methods
                p1 = src.at<Vec3b>(y, x);
                if (i >= h - y_scale)
                {
                    if (j >= w - x_scale)
                    {
                        p4 = src.at<Vec3b>((src.rows - 1) - (y + 1 - src.rows), (src.cols - 1) - (x + 1 - src.cols));
                    }
                    else
                    p3 = src.at<Vec3b>((src.rows-1)-(y + 1-src.rows), x);
                }
                else
                p2 = src.at<Vec3b>(y, (src.cols - 1) - (x + 1 - src.cols));
   
            }
            dst.at<Vec3b>(i, j) = w1 * p1 + w2 * p2 + w3 * p3 + w4 * p4;
           
        }
    }
    
}
int main()
{   
    cout << "type x_scale, y_scale: \n";
    //input scale size
    cin >> x_scale >> y_scale;
    src = imread("C:/Users/82103/Desktop/Lena_color.png");
    dst = Mat::zeros(src.rows * y_scale, src.cols * x_scale, src.type());
    //image using opencv library
    opencv_dst = Mat::zeros(src.rows * y_scale, src.cols * x_scale, src.type());
    h = dst.rows;
    w = dst.cols;
    if (!src.data) {
        printf("Could not open or find the image"); return -1;
    }
    //by using opencv library - blinear interpolation
    resize(src, opencv_dst, Size(), x_scale, y_scale, INTER_LINEAR);

    //function to perform bilinear interpolation 
    bilinear();


    namedWindow("original image", 1);
    imshow("original image", src);

    namedWindow("New Image using opencv", 1);
    imshow("New Image using opencv", opencv_dst);

    namedWindow("New Image", 1);
    imshow("New Image", dst);

    //save scaling image
    cv::imwrite("C:/Users/82103/Desktop/bilinear_result.png",dst);
    //save scaling image using opencv_library
    cv::imwrite("C:/Users/82103/Desktop/bilinear_result_opencv.png", opencv_dst);
    waitKey(0);
    return 0;

}



