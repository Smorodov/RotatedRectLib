#include "RR_Lib.h"
using namespace std;
using namespace cv;
//-----------------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	Mat img = imread("../lena.jpg", 1);

	if (img.empty())
	{
		return 0;
	}

	RotatedRect rr;
	rr.center = cv::Point2f(256, 256);
	rr.angle = 10;
	rr.size.width = 150;
	rr.size.height = 150;

	Mat fragment;
	getRotRectImg(rr, img, fragment);
    drawRR(img, rr, cv::Scalar(255, 0, 0),2);
	imshow("extracted fragment", fragment);

	cv::Rect src_roi = Rect(0, 0, fragment.cols, fragment.rows);
	rr.center = cv::Point2f(128, 128);
	copyToRotRectImg(src_roi, rr, fragment, img);
	drawRR(img, rr, cv::Scalar(255, 255, 0), 2);
	imshow("inserted fragment", img);

	rr.center = cv::Point2f(300, 300);
	rr.angle = -30;
	copyToRotRectImg(src_roi, rr, fragment, img);
	drawRR(img, rr, cv::Scalar(255, 0, 255), 2);
	imshow("inserted fragment 2", img);

	waitKey();

}
