#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

using namespace cv;
using namespace std;

Mat  srcdil, srccanny;// lưu ảnh 
void getContours(Mat srcdil, Mat src) {
	vector<vector<Point>> contours;// là một mảng hai chiều lưu trữ những điểm point pixel trong hình ảnh 
	vector<Vec4i>hierarchy;// danh sách các vector của contours mảng 2 chiều và vec4i là vecto có 4 chiều 
	string objectType;// khai báo đối tượng 

	findContours(srcdil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// tìm các đường viền của ảnh , trong đó RETR_EXTERNAL là lấy các đường viền bên ngoài hình 
	//CHAIN_APPROX_SIMPLE  nối các phân đoạn ngang dọc chéo của đường viền đối tượng  
	drawContours(src, contours, -1, Scalar(255, 0, 255), 10);
	//hàm dùng để vẽ các đường viền mà hàm findContours đã kiếm
	//src ảnh để vẽ ,contours mảng chứa những điểm để vẽ, -1 hoặc số âm là vẽ tất cả các đường viền
	// Scalar chỉnh màu cho  đường viền, 10 là độ dày của đường viền
	vector<vector<Point>>conPoly(contours.size());
	// là 1 mảng 2 chiều lấy kích thước của đối tượng ở mảng contours ở trên trừ các điểm ở đỉnh 
	vector<Rect>boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++) {

		int area = contourArea(contours[i]);// khai báo hàm tính diện tích của đối tượng và tính diện tích 
		cout << area << endl;
		if (area > 0) {
			float peri = arcLength(contours[i], true);// hàm lấy chu vi của độ dài đường cong cho biết đường cong có đóng hay không 
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			// hàm lấy khung của đối tượng ,vẽ gần giống như đối tượng cần vẽ 
			//0.02*peri độ chính xác gần đúng mà bạn muốn (epsilon)
			drawContours(src, conPoly, i, Scalar(255, 0, 255), 2);
			cout << conPoly[i].size() << "\n";
			boundRect[i] = boundingRect(conPoly[i]);
			// hàm giới hạn hình chữ nhật xung quanh ảnh nhị phân (hay còn gọi là ảnh trắng đen)
			rectangle(src, boundRect[i].tl(), boundRect[i].br(), Scalar(256, 0, 256), 5);
			//vẽ khung hình chữ nhật xung quanh ảnh nhị phân
			//boundRect[i].tl() lấy đường viền từ góc trên bên trái xuống
			//boundRect[i].br() lấy đường viền từ góc dưới cùng bên phải lên

			int objcor = (int)conPoly[i].size();// lấy số phần tử trong mảng 

			if (objcor == 3) { objectType = "tam giac"; }
			if (objcor == 4) { objectType = "tu giac"; }
			if (objcor == 5) { objectType = "ngu giac"; }
			if (objcor == 6) { objectType = "luc giac"; }
			if (objcor > 6) { objectType = "hinh tron"; }

			putText(src, objectType, { boundRect[i].x + 20,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1.2, Scalar(0, 69, 255), 1);
			//hàm dùng để ghi văn bản vào đối tượng vd:tên ,ghi chú ...,
			//objectType tên cần ghi vô được lấy từ hàm if, 
			//oundRect[i].x + 20,boundRect[i].y - 5 tùy chỉnh vị trí cần ghi 
			//FONT_HERSHEY_PLAIN lấy font chữ , 1.2 là cỡ chữ , 1 là độ dày nét chữ
		}
	}


}



int main()
{
	string path = "vuong.jpg";// lưu trữ link ảnh 
	Mat src = imread(path);// đọc link ảnh được lâý từ string
	/// các hàm thục hiện//////
	Mat kennel = getStructuringElement(MORPH_RECT, Size(9, 9));
	// dùng để làm tăng độ dày của đường nét ,trong đó MORPH_RECT hình dáng của đường nét 
	Canny(src, srccanny, 25, 75);// hàm vẽ các nét của hình ảnh
	dilate(srccanny, srcdil, kennel);// làm đậm các nét để nhìn rõ hơn 

	//getContours(srcdil, src);

	imshow("hinh", src);
	imshow("srcdil", srcdil);
	imshow("srccanny", srccanny);
	waitKey(0);

	return 0;

}