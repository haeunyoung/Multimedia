
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
  //cv::resize(src,dst,cv::Size(src.cols,scr.rows,0,0,INTER))
    string imageName("C:/Users/82103/Desktop/frozen.jpg");
    if (argc > 1)
    {
        imageName = argv[1];
    }

    Mat image;

    image = imread(imageName.c_str(), IMREAD_COLOR);

    if (image.empty())
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    float ab;
    std::cout << "enter the alpha value [1.0-3.0]"; std::cin >> ab;
    Mat new_image = Mat::zeros(image.size(), image.type()); //Image와 동일한 크기와 타입(color chanel 등등 )으로 메모리 확보.
    Mat new_image2 = Mat::zeros(image.size(), image.type());// 다 0 같으로 초기화 해서 만들어주세요 

   /// Initialize values
    int alpha = 2.2;
    int beta = 0;

    int a = 2.7;

    /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
    for (int y = 0; y < image.rows; y++) { //세로
        for (int x = 0; x < image.cols; x++) { //가로 
            for (int c = 0; c < 3; c++) {
                new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * (image.at<Vec3b>(y, x)[c]) + beta);
                new_image2.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(ab * (image.at<Vec3b>(y, x)[c]) + beta);
                //saturate_cast = 유효한 픽셀 값 보장을 위함. 픽셀값 범위는 [0, 255]이므로 이를 넘어서는 범위는 자동으로 클램핑(Clamping).
            }
        }
    }

    /// Create Windows
    namedWindow("Original Image", 1);
    namedWindow("New Image", 1);
    namedWindow("New Image2", 1);

    /// Show stuff
    imshow("Original Image", image);
    imshow("New Image", new_image);
    imshow("New Image22", new_image2);

    /// Wait until user press some key
    waitKey();
    return 0;

}