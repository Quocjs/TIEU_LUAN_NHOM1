#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void main()
{
	string path = "DieuAnh.png";
	Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(3, 3), 4, 2);
	Canny(imgBlur, imgCanny, 15, 10);
	
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(imgCanny, imgDilate, kernel);
	erode(imgDilate, imgErode, kernel);

	imshow("Dieu Anh", img);
	imshow("Dieu Anh GRAY", imgGray);
	imshow("Dieu Anh Blur", imgBlur);
	imshow("Dieu Anh Canny", imgCanny);
	imshow("Dieu Anh Dilate", imgDilate);
	imshow("Dieu Anh Erode", imgErode);

	waitKey(0);
}