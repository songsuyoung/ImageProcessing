/***********************************************************/
/*					 HW#3-1 : Convolution		     	     */
/*  작성자 : 송수영          날짜 : 2023년 4월23일          */
/*                                                          */
/* 문제 정의 : Convolution 자체에 의미가 있지는 않지만, 마스크
형태와 크기에 따른 연산에 따라 의미를 가진다. smoothing 효과를 
부여하는가우시안과 박스 마스크 총 합이 1이 되면, convolution을 
진행하고,선명한 효과를 지니는 샤프닝, 수평에지, 수직에지에 대해
합계가 0이 될 수 있도록 마스크를 만든다. 모션의 경우는 대각선
으로 표현된 마스크를 이용하면서, 이동되는 모습을 구현한다. 
위 모든 방법을 filter2D를 이용했으며, 직접 커널을 만들어서
사용했다. (박스 커널 제외)									*/
/**********************************************************/

#include <opencv2/opencv.hpp> // openCV API를 사용하기 위한 기본 헤더파일 포함
//opencv.hpp 에 대부분의 헤더파일이 포함되어 있음
using namespace cv;
using namespace std;

int main() {

	//convolution에 사용할 임의의 이미지 업로드
	Mat src=imread(".//Image//255x255.png",IMREAD_GRAYSCALE);

	imshow("original Img", src);
	/* Box Filter Algorithm Default */
	//1/9을 평균필터로 사용 -> 3x3 -> default 1/9로 설정
	Mat BoxConv;
	
	//Size Class로 3x3크기의 box convolution 생성, box 이기때문에 1/9 적용.
	//dtype = -1 : 입력 영상과 동일
	//nomalize -> defalut == True 인데, True를 해주어야지 커널 크기로 정규화.
	boxFilter(src, BoxConv, -1, Size(3, 3), Point(-1, -1));

	imshow("BoxFilter", BoxConv);

	/* Gaussian Filter Algorithm 실행시 아래 주석 활성화 */
	/*	Mat GaussianCov;

	//Gaussian 필터 직접 만들기 
	Mat GaussianKernel = (Mat_<float>(5, 5) << .0000, .0000,0.0002,.0000,.0000,
											.0000,.0113,.0873,.0113,.0000,
										.0002,.0837,.6187,.0837,.0002,
										.0000,.0113,.0837,.0113,.0000,
										.0000,.0000,.0002,.0000,.0000);

	//filter2D 를 이용해 직접 만든 가우시안 필터 적용하기
	filter2D(src, GaussianCov, -1, GaussianKernel,Point(-1,-1));
	//이미지 적용
	imshow("Gaussian Conv", GaussianCov);
	*/

	/* 샤프닝 Filter Algorithm 실행시 아래 주석 활성화 */
	/*
	* Sharpening 0 -1 0
	*            -1 5 -1
	*            0 -1 0 을 표현하기 위해서 직접 kenel생성.
	Mat SharpeningKenel = (Mat_<int>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);

	Mat SharpeningConv;
	filter2D(src, SharpeningConv, -1, SharpeningKenel); //filter를 직접 만든 샤프닝과 Conv함으로써 
	결과받기.

	cout << SharpeningKenel << endl;
	imshow("Sharpening Cov", SharpeningConv);
	*/
	
	/* 수평, 수직 Edge Filter Algorithm 실행시 아래 주석 활성화 */
	/* 1차 미분시 1,0,-1 의 Mask값을 얻게되는데 수평 수직으로 늘렸을때 커널을 표현하기 위해
	수평은 1,0,-1
		1,0,-1
		1,0,-1 로 표현
	수직은 1,1,1,
			0,0,0,
			-1,-1,-1 로 표현한다.

	Mat HorizKenel=(Mat_<int>(3,3) <<1,1,1,
									0,0,0,
									-1,-1,-1);
	cout << "HorizeKenel " << HorizKenel << endl;
	Mat VertiKenel=(Mat_<int>(3, 3) << 1, 0, -1,
									1, 0, -1,
									1, 0, -1);
	cout << "VertiKenel " << VertiKenel << endl;

	// 중앙값 -1,-1로 설정
	Mat HoriDst, VertisDst;
	filter2D(src, HoriDst, -1, HorizKenel, Point(-1, -1));
	filter2D(src, VertisDst, -1, VertiKenel, Point(-1, -1));

	//수직 수평 엣지 추출 후 출력
	imshow("horizontal Convolution", HoriDst);
	imshow("vertical Convolution", VertisDst);
	*/

	/* Motion Mask Algorithm 실행시 아래 주석 활성화*/
	/*
	* Motion (즉, 움직이는 효과)를 주기 위해서, 대각선 방향으로 가중치 값을 부여한
	* 결과, 컨볼루션 진행 후에 움직이는 모습을 표현할 수 있다.
	Mat MotionKenel = (Mat_<float>(5, 5) << .0304, .0501, 0, 0, 0,
											.0501, .1771, .0519, 0, 0,
											0, .0519, .1771, .0519, 0,
											0, 0, .0519, .1771, .0501,
											0, 0, 0, .0501, .0304);

	cout << "MotionKenel = " << MotionKenel << endl;

	Mat MotionDst;
	//Motion Mask를 이용해 Filter적용.
	filter2D(src, MotionDst, -1, MotionKenel, Point(-1, -1));

	imshow("Motion Conv", MotionDst);
	*/
	waitKey();// 화면 종료되지 않고 대기
	
}