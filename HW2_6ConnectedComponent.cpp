/***********************************************************/
/*       HW#2-6 : Connected Component in OpenCV             */
/*  작성자 : 송수영          날짜 : 2023년 4월10일          */
/*                                                          */
/* 문제 정의 : connected component함수를 이용해서 함수를 적 */
/*용해 보고, 라벨링의 결과값을 확인한다.                    */
/**********************************************************/

#include <opencv2/opencv.hpp> // openCV API를 사용하기 위한 기본 헤더파일 포함
//opencv.hpp 에 대부분의 헤더파일이 포함되어 있음
using namespace cv;
using namespace std;

void main() {
	Mat OriginalImg = imread(".//Image//logo.jpg", IMREAD_GRAYSCALE); //gray level은 보통 8bit 0~255사이
	
    imshow("OriginalImg", OriginalImg); //원래 이미지를 출력한다.

	Mat otsuResult;
	//임계값을 찾아 이진화 진행
	threshold(OriginalImg, otsuResult, 0, 255, THRESH_OTSU);
	imshow("otsuResultImg", otsuResult);
	//오츠 알고리즘을 사용해 출력

	Mat labels, stats, centroids, img_color;

	//그레이 이미지를 컬러로 변경
	cvtColor(OriginalImg, img_color, COLOR_GRAY2BGR);
	
	//라벨링된 갯수 반환, 이미지를 확인하고 그 이미지에 레이블링을 저굥ㅇ
	int numOfLables =connectedComponentsWithStats(otsuResult, labels, stats, centroids,8, CV_32S);

	//라벨링된 이미지중 특정 라벨을 컬러로 표현해주기  
	for (int y = 0; y < labels.rows; ++y) {

		int* label = labels.ptr<int>(y);
		Vec3b* pixel = labels.ptr<Vec3b>(y);


		for (int x = 0; x < labels.cols; ++x) {

			if (label[x] == 1) {
				pixel[x][0] = 0;
				pixel[x][1] = 255; //찾은 레이블에만 색 적용
				pixel[x][2] = 0;
			}
		}
	}


	//라벨링 된 이미지에 각각 직사각형으로 둘러싸기 
	for (int j = 1; j < numOfLables; j++) {

		//박스를 둘러싸기 위해서 각 위치의 점을 반환.
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		int x = centroids.at<double>(j, 0); //중심좌표
		int y = centroids.at<double>(j, 1);

		circle(img_color, Point(x, y), 5, Scalar(255, 0, 0), 1);
		//실제 그림 그리는 부분
		rectangle(img_color, Point(left, top), Point(left + width, top + height),
			Scalar(0, 0, 255), 1);
		//개수 
		putText(img_color, to_string(j), Point(left + 10, top + 10),
			FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
	}
	//출력
	imshow("labelsImg", img_color);

	waitKey(0);
}
