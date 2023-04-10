/***********************************************************/
/*                 HW#2-4 : Subtraction                     */
/*  작성자 : 송수영          날짜 : 2023년 4월10일          */
/*                                                          */
/* 문제 정의 : 사칙연산과 지금까지 배운 내용을 가지고, 적용 */
/* 해본다.두 이미지의 차이를 이용해, 달라진 점을 확인하고 새*/
/* 로운 연산들을 이용하여 검은 부위와 흰 부위를 강조한다.   */
/**********************************************************/

#include <opencv2/opencv.hpp> // openCV API를 사용하기 위한 기본 헤더파일 포함
//opencv.hpp 에 대부분의 헤더파일이 포함되어 있음
using namespace cv;
using namespace std;


Mat ShowDiff_C(Mat SubImg);
Mat ShowDiff_D(Mat SubImg);

void main() {
	Mat MaskImg = imread(".//Image//Fig0228(a).tif", IMREAD_GRAYSCALE); //gray level은 보통 8bit 0~255사이
	Mat AliveImg = imread(".//Image//Fig0228(b).tif", IMREAD_GRAYSCALE); //gray level은 보통 8bit 0~255사이
	
	Mat SubImg1,SubImg2;
	subtract(MaskImg, AliveImg, SubImg1);
	subtract(MaskImg, AliveImg, SubImg2); //두 이미지를 뺀다

	SubImg1 =ShowDiff_C(SubImg1); //c 이미지를 연산한다
	SubImg2= ShowDiff_D(SubImg2); //d 이미지를 연산한다
	imshow("SubImg2", SubImg2);
    imshow("SubImg1", SubImg1);
	waitKey(0);
}

Mat ShowDiff_C(Mat SubImg) {
	//직선의 방정식을 이용하여, 밝은 부분과 검은 부분을 강조한다.
	double alpha = 2, beta = 0.8;
	SubImg.convertTo(SubImg, -1, alpha, beta);
	//반전하기 위해서, 뺄셈을 실시한다.
	SubImg = 200 - SubImg;

	return SubImg; 
}

Mat ShowDiff_D(Mat SubImg) {
	//차이점을 강조하기 위해서 *5를 한다.
	SubImg *= 5;
	//밝은 부분을 회색으로, 회색부분을 흰색 가까이 변환하기 위해서 뺄셈을 실시한다.
	SubImg = 200 - SubImg;

	return SubImg;
}