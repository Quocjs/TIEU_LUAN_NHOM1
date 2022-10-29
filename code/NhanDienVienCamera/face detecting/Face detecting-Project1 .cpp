#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void ContourTool(Mat imgDil, Mat img)
{
	vector<vector<Point>> contours; // vector điểm trên hình
	vector<Vec4i> hierarchy;
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
}

void main()
{
VideoCapture cap(0);
Mat img;
	Mat imgCVT, imgBlur, imgCanny, imgDilate;

	while (true)
	{
		cap.read(img);
		cvtColor(img, imgCVT, COLOR_BGR2GRAY);
		GaussianBlur(img, imgBlur, Size(7, 7), 4, 0);
		Canny(imgBlur, imgCanny, 70, 7);
		Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
		dilate(imgCanny, imgDilate, kernel);

		ContourTool(imgDilate, img);

		imshow("Image", img);
		waitKey(20);
	}
}

