#include <opencv2/opencv.hpp>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include<vector>

using namespace cv;
using namespace std;


int main()
{
    //read image
    Mat foreground = imread("C:/Users/82103/Desktop/Girl_in_front_of_a_green_background.jpg");
    Mat background= imread("C:/Users/82103/Desktop/background.jpg");
    resize(background, background, foreground.size());
    Mat new_image = Mat::zeros(foreground.size(), foreground.type());

    //draw the histrogram
    //histogram size (0~255)
    vector<Mat> bgr_planes;
    split(foreground, bgr_planes);  
    int histSize = 256;  
    float range[] = { 0, 256 };  
    const float* histRange = { range };  
    bool uniform = true; 
    bool accumulate = false;  
    Mat b_hist, g_hist, r_hist;  
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);  
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);  
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);  
    // Draw the histograms for B, G and R  
    int hist_w = 512; 
    int hist_h = 400;  
    int bin_w = cvRound( (double) hist_w/histSize );  
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );  
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );  
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );  
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );  
    for( int i = 1; i < histSize; i++ )  {      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),     
      Scalar( 255, 0, 0), 2, 8, 0  );      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) , Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),  
          Scalar( 0, 255, 0), 2, 8, 0  );      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),      
              Scalar( 0, 0, 255), 2, 8, 0  );  }  

    
    //print histogram & foreground image & back ground image
    namedWindow("calcHist Demo", WINDOW_AUTOSIZE );  
    imshow("calcHist Demo", histImage );
    namedWindow("foreground", WINDOW_AUTOSIZE);
    imshow("foreground", foreground);
    namedWindow("background", WINDOW_AUTOSIZE);
    imshow("background", background);

     //Processing in YCbCr foreground-> new image
    cvtColor(foreground, new_image, COLOR_BGR2YCrCb);
    
    int countColor[260][2] = { 0,};
    int cb_key;
    int cr_key;
    int cr, cb;
    //to find the most distributed color(green)
    for (int y = 0; y < new_image.rows; y++) {
        for (int x = 0; x < new_image.cols; x++) {

            //counting green , red 
            cb= new_image.at<Vec3b>(y, x)[1];
            cr = new_image.at<Vec3b>(y, x)[2];
            countColor[cb][0]++;
            countColor[cr][1]++;
        }
    }

    int max_b = 0;
    int max_r = 0;
    // to find max (cr_key, cb_key)
    for (int i = 0; i < 256; i++)
    {
        if (countColor[i][0] > max_b)
        {
            max_b = countColor[i][0];
            cb_key = i;
        }
        if (countColor[i][1] > max_r)
        {
            max_r = countColor[i][1];
            cr_key = i;
        }

    }

      //found inner, outer through histogram 
    int inner=30, outer=50;
    Mat alpha = Mat::zeros(new_image.size(), CV_32F);
    float euclidean;
    //determine the euclidean distance between each pixel's color 
    for (int y = 0; y < new_image.rows; y++) {
        for (int x = 0; x < new_image.cols; x++) {
            euclidean=sqrt(pow(new_image.at<Vec3b>(y, x)[1] - cb_key, 2) + pow(new_image.at<Vec3b>(y, x)[2] - cr_key, 2));

            //if the distance is within an inner threshold
            if (euclidean < inner)
            {
                alpha.at<float>(y,x) = 0.0;
            }
            else if(euclidean>outer) //if above an outer threshold
                alpha.at<float>(y, x) = 1.0;
            else//between inner and outer
            {
                alpha.at<float>(y, x) = (euclidean - inner) / (outer - inner);
            }
        }
    }
    
    Mat chromakey= Mat::zeros(foreground.size(), foreground.type());
    //blending between foreground and background
    for (int y = 0; y < foreground.rows; y++)
    {
        for (int x = 0; x < foreground.cols; x++)
        {
            for (int c = 0; c < 3; c++)
            {
              chromakey.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha.at<float>(y,x)* foreground.at<Vec3b>(y, x)[c] + (1 - alpha.at<float>(y, x)) * background.at<Vec3b>(y, x)[c]);
            }
        }
    }

    namedWindow("chromakey",0.7);
    imshow("chromakey", chromakey);
    waitKey(0);
    return 0;
}


