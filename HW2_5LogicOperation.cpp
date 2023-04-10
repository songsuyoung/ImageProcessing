/***********************************************************/
/*                 HW#2-5 : Logic Operation                 */
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
	Mat MaskImg = imread(".//Image//Fig0230(b).tif", IMREAD_GRAYSCALE); //gray level은 보통 8bit 0~255사이
	Mat SourceImg = imread(".//Image//Fig0230(a).tif", IMREAD_GRAYSCALE); //gray level은 보통 8bit 0~255사이
	
	Mat OutImg;
	bitwise_and(SourceImg, MaskImg, OutImg);
    imshow("SubImg1", OutImg);
	waitKey(0);
}
