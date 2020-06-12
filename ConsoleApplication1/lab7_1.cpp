#include <opencv2/opencv.hpp>

using namespace cv;
void affine(Mat src, Mat dst)
{

	Point2f srcTri[3];
	Point2f dstTri[3];

	Mat warp_mat(2, 3, CV_32FC1);

	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);

	dstTri[0] = Point2f(src.cols * 0.0, src.rows * 0.33);
	dstTri[1] = Point2f(src.cols * 0.85, src.rows * 0.25);
	dstTri[2] = Point2f(src.cols * 0.15, src.rows * 0.7);

	warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(src, dst, warp_mat, dst.size());
	

}

int main(int, char**)
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		return -1;
	}

	Mat edges;
	namedWindow("Affine transform", 1);

	for (;;)
	{
		Mat frame,warp_dst;
		cap >> frame;
		//affine(frame,frame);
		imshow("Affine transform", frame);
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);
	    imshow("edges", edges);
		if (waitKey(30) >= 0) break;
	}
	
	return 0;
}
/*
#include "opencv2/opencv.hpp"

using namespace cv;
void Affine(Mat frame, Mat warp_mat);
Mat Edge(Mat frame, Mat edges);
int main()
{
	VideoCapture cap(0); //oepn the default camera
	Mat warp_mat(2, 3, CV_32FC1);
	if (!cap.isOpened())
		return -1;
	Mat edges;
	Point2f srcTri[3], dstTri[3];
	namedWindow("edges", 1);

	for (;;)
	{
		Mat frame;
		cap >> frame;
		//frame=Edge(frame, frame);
		Affine(frame, frame);
		imshow("edges", frame);
		if (waitKey(30) >= 0)break;
	}
	return 0;
}
Mat Edge(Mat frame, Mat edges)
{
	cvtColor(frame, edges, COLOR_BGR2GRAY);
	GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
	Canny(edges, edges, 0, 30, 3);
	return edges;

}
void Affine(Mat frame, Mat warp_dst)
{
	Mat warp_mat(2, 3, CV_32FC1);
	Point2f srcTri[3], dstTri[3];
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(frame.cols - 1, 0);
	srcTri[2] = Point2f(0, frame.rows - 1);

	dstTri[0] = Point2f(frame.cols * 0.0, frame.rows * 0.33);
	dstTri[1] = Point2f(frame.cols * 0.85, frame.rows * 0.25);
	dstTri[2] = Point2f(frame.cols * 0.15, frame.rows * 0.7);
	warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(frame, warp_dst, warp_mat, frame.size());
}

*/