/********************************************************/
/*             HW#3-3 : Noise Removal                      */
/*  작성자 : 송수영          날짜 : 2023년 4월 25일      */
/*                                                      */
/* 문제 정의 : salt&pepper Noise를 이용하여 잡음을 생성하
였고, 그 잡음을 가우시안 필터와 메디안 필터로 제거하는
알고리즘을 구현했다. 가우시안의 경우 노이즈도 남아있고,
화면만 흐릿해진 반면에, 메디안 필터의 경우 노이즈도 거의
사라지고 세세한 부분이 사라지긴 했지만, 높은 성능을 보였
다. 그래서 지금까지 배운 필터 중 임펄스 노이즈에서 높은
성능을 보이는 것은 메디안 필터라고 확정할 수 있었다. */
/*******************************************************/

#include <opencv2/opencv.hpp> // openCV API를 사용하기 위한 기본 헤더파일 포함
//opencv.hpp 에 대부분의 헤더파일이 포함되어 있음
using namespace cv;
using namespace std;

//salt and pepper noise 적용 함수
Mat GetSaltAndPepperNoise(const Mat &src,int noiseNum) {

	Mat imgAddNoise(src);

	//다 다른값을 내오기 위한 초기화
	srand((int)time(NULL));

	for (int i = 0; i < noiseNum; i++) {

		//rows cols를 벗어나면 안되기때문에 나머지 연산처리
		int randRows = rand() % src.rows;
		int randCols = rand() % src.cols;

		//0 or 1 반환시 1일때 255로를 곱함으로써 흑 백을 완성
		int saltAndPepper = (rand() % 2) * 255;
		//rows cols 위치에 255 or 0삽입
		imgAddNoise.at<uchar>(randRows, randCols) = saltAndPepper;
		
	}

	return imgAddNoise;
}

int main() {
	//load
	Mat srcImage = imread(".//Image//255x255.png", cv::IMREAD_GRAYSCALE);

	imshow("Original Img", srcImage);

	Mat noiseImg=GetSaltAndPepperNoise(srcImage, 1000);

	//noise 제거를 위한 필터 알고리즘 적용
	// 배운 필터 : Median Filtering | Gaussian Filter 

	//1. Median Filtering : salt&pepper 노이즈를 지우는데 용이하고, 경계를 유지함 
	imshow("Add Noise", noiseImg);
	Mat medianImg;
	//크기를 5x5로 설정하여, median 필터를 적용
	medianBlur(noiseImg, medianImg, 5);
	imshow("Median filter를 이용해 Noise 삭제", medianImg);

	//2. Gaussian Filter
	Mat GaussianImg;
	//GaussianBlur 함수 내부에서, 필터를 생성하고 노이즈 제거를 진행함
	GaussianBlur(noiseImg, GaussianImg, Size(5,5), 3.0);
	//확인용
	imshow("Gaussian Filter를 이용한 Noise 삭제", GaussianImg);

	waitKey();

	return 0;
}