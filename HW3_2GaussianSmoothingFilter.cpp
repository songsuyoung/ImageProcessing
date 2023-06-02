/***********************************************************/
/*		    HW#3-2 : Gaussian Smoothing Filter             */
/*  작성자 : 송수영          날짜 : 2023년 4월 24일          */
/*                                                          */
/* 문제 정의 :getGaussianKernel과 GaussianBlur의 sig값을 일치한 후
getGaussianKenel은 filter2D를 이용해 직접 블러효과를 제공했고,
GaussianBlur의 경우에 cv2에서 제공해주는 함수를 직접 이용했다.
하지만, 두 결과가 다르게 나와 왜 다른가 찾아봤을때,getGaussianKenel은
1차원 가우시안 분포를 이용하고, GaussianBlur는 2차원 가우시안 분포
를 사용한다는 점을 알게 되었다.                            */
/**********************************************************/

#include <opencv2/opencv.hpp> // openCV API를 사용하기 위한 기본 헤더파일 포함
//opencv.hpp 에 대부분의 헤더파일이 포함되어 있음
using namespace cv;
using namespace std;

int main() {
	Mat src = imread(".//Image//255x255.png", IMREAD_GRAYSCALE);
	imshow("original Img", src);


	/*Gaussian의 경우 표준편차가 커지면, 저주파를 많이 통과하고, 작아지면 적게 통과하는 경향이 있음
	즉, 스무딩의 정도가 표준편차에 의해 영향을 받음.*/

	vector<Mat> SigKernel(4);

	for (int i = 0; i < SigKernel.size(); i++) {
		SigKernel[i] = getGaussianKernel(5, i+1); //sig=1 일때
	}

	//위 4가지를 이용한 가우시안 커널을 이용해 필터를 적용해 볼 예정이다.

	vector<Mat> Sigdst(4);

	for (int i = 0; i < Sigdst.size(); i++) {
		filter2D(src, Sigdst[i], -1, SigKernel[i]); //1차원 결과이기때문에, 두번째 적용한 가우시안 필터와의 결과가 다름을 알 수 있음
	}

	//위 필터 적용한 결과를 imshow 할 예정인데, 위 결과와 가우시안 스무딩 필터를 바로 적용
	//했을때랑 차이를 알아볼 예정!

	for (int i = 0; i < 4; i++) {
		imshow("Sig" + to_string(i+1), Sigdst[i]);
	}
	//가우시안 블러 필터를 사용했을때 결과를 알아봄.
	vector<Mat> GaussainFilter(4);

	for (int i = 0; i < GaussainFilter.size(); i++) {
		GaussianBlur(src, GaussainFilter[i], Size(5, 5), i+1); //위와 달리 2차원 가우시안 필터임!!! y sig를 지정안하면, x값과 일치 시키기 때문에
		//가우시안 블러를 이용했을때가 훨 흐릿해지는 결과를 얻을 수 있었음.
		imshow("GaussBlur Filter " + to_string(i+1), GaussainFilter[i]);
	}

	waitKey(0);
}