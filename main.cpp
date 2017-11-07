#include "RR_Lib.h"
using namespace std;
using namespace cv;
//-----------------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	Mat img = cv::imread("../lena.jpg", 1);
    Mat img_bak = img.clone();
	if (img.empty())
	{
		return 0;
	}

    // Set rotated region to extract fragment
	RotatedRect rr;
	rr.center = cv::Point2f(256, 256);
	rr.angle = 10;
	rr.size.width = 150;
	rr.size.height = 150;

	Mat fragment;
    // Extract fragment
	RRLib::getRotRectImg(rr, img, fragment);
    // Show where we extracted it from
    RRLib::drawRR(img, rr, cv::Scalar(255, 0, 0),2);
	imshow("extracted fragment", fragment);
    imshow("extracting fragment", img);

    // restore image
    img = img_bak.clone();
    // get piece of image
	cv::Rect src_roi = Rect(0, 0, fragment.cols, fragment.rows);
    // set target roi
	rr.center = cv::Point2f(300, 300);
	rr.angle = -30;
    // paste it to image
	RRLib::copyToRotRectImg(src_roi, rr, fragment, img);
    // draw frame around
	RRLib::drawRR(img, rr, cv::Scalar(255, 0, 255), 2);
	imshow("inserted fragment simple", img);


    // restore image
    img = img_bak.clone();
    rr.center = cv::Point2f(150, 350);
    rr.angle = -60;

    // create mask
    Mat mask = Mat::zeros(fragment.size(), CV_8UC3);
    circle(mask, Point(fragment.cols / 2, fragment.rows / 2), fragment.rows / 2, Scalar::all(255),-1);
    GaussianBlur(mask, mask, Size(25, 25), 17);
    normalize(mask, mask, 0, 255, cv::NORM_MINMAX);

    // paste with mask (it really blending)
    RRLib::copyToRotRectImg(rr, fragment,mask, img);
    RRLib::drawRR(img, rr, cv::Scalar(255, 0, 255), 2);
    imshow("inserted fragment with mask", img);

	waitKey();

}
