#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;
class BaSic 
{
public:
	//Hàm Mở ảnh
	void Image(string path)
	{
		Mat img = imread(path);
		imshow("Image", img);
		waitKey(0);
	}
	// Hàm mở Video
	void Video(string path)
	{
		Mat img;
		VideoCapture cap(path);
		while (true)
		{
			cap.read(img);
			imshow("Video Dieu Anh", img);
			waitKey(20);
		}
	}
	// Hàm Camera
	void Camera()
	{
		VideoCapture cap(0);
		while (true)
		{
			Mat img;
			imshow("Camera", img);
			waitKey(20);
		}
	}
};



void main()
{
	string pathAnh = "DieuAnh.png";
	string pathVideo = "DieuAnh.mp4";
	BaSic coban;
	coban.Image(pathAnh);
	coban.Video(pathVideo);
	coban.Camera();
}

