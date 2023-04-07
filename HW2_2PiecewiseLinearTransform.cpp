/********************************************************/
/*          HW#2-2 : Piecewise-Linear Transform         */
/*  작성자 : 송수영          날짜 : 2023년 4월 7일      */
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
	Mat srcImage = imread(".//Image//Fig0310.tif", cv::IMREAD_GRAYSCALE); //gray level은 보통 8bit 0~255사이

	//기울기 공식 아닌가?
	//(0,0) (8,8) y2-y1/x2-x1   (64,64) (255,255)
	double r1 = 100, s1 = 50, r2 = 125, s2 = 200;
	Mat dstImage=srcImage.clone();
	double scale;
	
	//각 픽셀의 화소에 대해 기울기 계산을 진행
	for (int i = 0; i < srcImage.rows; i++) {
		for (int j = 0; j < srcImage.cols; j++) {
			uchar originalVal = srcImage.at<uchar>(i, j);
			if (originalVal <= r1) {
				//r1보다 작을 때, 기울기 계산
				scale = s1 / r1;
				dstImage.at<uchar>(i, j) = (originalVal-r1) * scale+s1;
			}
			else if (originalVal >= r2) {
				//r2보다 클 때, 기울기 계산, gray ;evel일경우 8비트로, 0~255값으로 이루어짐.
				scale = (255.0-s2)/ (255.0 - r2);
				dstImage.at<uchar>(i, j) = (originalVal-r2) * scale + s2;
			}
			else {
				//r1<=x<=r2 사이일때, (r1,s1) - (r2,s2) 사이의 직선의 방정식 식을 이용해, 계산.
				scale = (s2-s1) / (r2-r1);
				dstImage.at<uchar>(i, j) = (originalVal - r2) * scale + s2;
			}
			// 직선의 방정식 공식 : scale * (originalVal-r1) + s1
			// 둘다 해당되지 않을경우 원래 r1=s2를 가진다.
		}
	}
	imshow("dstImage", dstImage);
	waitKey();
}