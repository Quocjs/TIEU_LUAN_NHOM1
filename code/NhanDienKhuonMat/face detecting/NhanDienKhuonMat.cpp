#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include<opencv2/objdetect.hpp>

using namespace cv;
using namespace std;

void main()
{



	VideoCapture cap(0); // mở thiết bị quay video theo địa chỉ ip của thiết bị
	Mat img; // khai báo ảnh
	CascadeClassifier faceCascade; // dùng để khai báo đối tượng được quét (faceCascade)
	faceCascade.load("haarcascade_frontalface_default.xml"); // load dùng để tải link đường link (như trong bài để tải đường link code quét khôn mặt)
	if (faceCascade.empty()) { cout << "loi he thong"; }  // khi không có gì xảy ra thì nó để trống và báo lỗi hệ thống
	while (true) { // khi có đối tượng quét
		cap.read(img); // đọc hình ảnh
		vector<Rect>faces; // vector đầu vào ra của hình chữ nhật(vector face)
		faceCascade.detectMultiScale(img, faces, 1.1, 3);
		// tự động phát hiện các hình ảnh đầu vào (khuôn mặt) 
		// detectMultiscale(ảnh đầu ào, đối tượng,(scale factor = 1.1) kích thước hình ảnh được giảm sau mỗi hình ảnh, size line)
		for (int i = 0; i < faces.size(); i++)
		{
			Mat imgCrop = img(faces[i]);
			imshow(to_string(i), imgCrop); // đưa ra màn hình phần khôn mặt tọa độ i được quét
			imwrite("khuonmat/" + to_string(i) + ".jpg", imgCrop); // ghi lại hình ảnh khuonmat lưu vào file khuonmat duoi dang jpg
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(256, 0, 256), 3);
			// khuôn mặt quét đưa vào hình chữ nhật
			// rectangle(ảnh đầu vào,tọa độ vector khuôn mặt quét ,màu sắc, size line)

		}

		imshow("camera", img); // in ra màn hình camera 

		waitKey(5);
	}
}