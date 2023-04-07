/********************************************************/
/*             HW#1 : Power Law                         */
/*  작성자 : 송수영          날짜 : 2023년 4월 6일      */
/*                                                      */
/* 문제 정의 : pow함수를 이용해 이미지의 gray level의 명*/
/* 도 조절을 실행한다. r>1 역로그를 의미, r<1이면 로그변*/
/* 환을 의미한다. 감마에 따라 달라지는 이미지를 확인해보*/
/* 자. 현재 이 과제에서는 1.0 3.0 4.0 5.0에 대해 살펴보 */
/* 았다.                                                */
/*******************************************************/

#include <opencv2/opencv.hpp> // openCV API를 사용하기 위한 기본 헤더파일 포함
//opencv.hpp 에 대부분의 헤더파일이 포함되어 있음
using namespace cv;
using namespace std;

void powImage(Mat, double);

int main()
{
	Mat srcImage = imread(".//Image//Fig0309.tif", IMREAD_GRAYSCALE); //이미지를 읽어온다

	if (srcImage.empty()) { //이미지가 없을 시, 프로그램 종료
		return - 1;
	}

	Mat flmage; //지수 계산을 위한 Mat 객체
	srcImage.convertTo(flmage, CV_32F); //지수 계산을 위해 CV_32F 자료형으로 변환
	powImage(flmage, 3.0); //함수로 정의함으로써, main함수 단순화

	waitKey();
	return 0;
}

/*normarlize함수가 필요한 이유를 알기 위해서, 주석처리 후 실행한 결과
r>1이면, 역로그와 유사해짐.. 명도의 레벨이 낮아지는 효과를 보게됐다.
normalize를 적용하게 되면 정규화 과정을 거치면서 안정된 히스토그램 분포를 가지게 된다 */
//중복된 코드를 줄이기 위해 함수 구현
void powImage(Mat originalImg,double power) {
	Mat powImage;
	pow(originalImg, power, powImage); //powImage = originalImg ^ power
	normalize(powImage, powImage, 0, 1.0, NORM_MINMAX); //pow계산된 powImage normalize시킴
	imshow("powFunction_"+to_string(power), powImage); //출력
}