/********************************************************/
/*          HW#2-3 : Bit Plane Slicing                  */
/*  작성자 : 송수영          날짜 : 2023년 4월10일      */
/*                                                      */
/* 문제 정의 : 각 이미지의 화소에 따라, 3개의 직선의방정*/
/*식을 구하고, 그 방정식에 따라 명도를 다르게 설정한다. */
/*사용한 직성의 방정식 y=s*(originalVal-x1)+y1으로, 크기*/
/*에 따라서 다른 결과물을 내놓는다.                    * /
/*******************************************************/

#include <opencv2/opencv.hpp> // openCV API를 사용하기 위한 기본 헤더파일 포함
//opencv.hpp 에 대부분의 헤더파일이 포함되어 있음
using namespace cv;
using namespace std;


void main() {
	Mat srcImage = imread(".//Image//Fig0314.tif", cv::IMREAD_GRAYSCALE); //gray level은 보통 8bit 0~255사이
	imshow("Original Img", srcImage);
	int cols, rows, x, y;

	cols = srcImage.cols;
	rows = srcImage.rows;

	printf("%d %d \n", srcImage.rows, srcImage.cols);
	Mat out[9];

    //CV_8UC1 8bit + unsigned + channel 1개 out[i] 하나의 level에 속하고, srcImage의 크기의 모든 Mat를 0으로 초기화
	for (int i = 0; i <= 8; i++) {
		out[i] = Mat(rows, cols, CV_8UC1, Scalar(0));
	}

	for (int i = 0; i <= 8; i++) { //bit plane 레벨 의미
		for (int x = 0; x < rows; x++) { //row
			for (int y = 0; y < cols; y++) { //col을 srcImage의 각 레벨에 해당하는 값을 넣기 위해 있음.
				//해당 자리수에 값이 있는지 없는지 true false로 확인하기 위해서 and연산 실시. 
				out[i].at<uchar>(x, y) = (srcImage.at<uchar>(x, y) & uchar(pow(2,i)))? uchar(255) : uchar(0);
			}
		}
		string s = "dstImage";
		s += to_string(i);
		imshow(s, out[i]);
	}


	waitKey();
}