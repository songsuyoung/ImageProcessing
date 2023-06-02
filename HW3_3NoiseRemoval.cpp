/********************************************************/
/*             HW#3-3 : Noise Removal                      */
/*  �ۼ��� : �ۼ���          ��¥ : 2023�� 4�� 25��      */
/*                                                      */
/* ���� ���� : salt&pepper Noise�� �̿��Ͽ� ������ ������
����, �� ������ ����þ� ���Ϳ� �޵�� ���ͷ� �����ϴ�
�˰����� �����ߴ�. ����þ��� ��� ����� �����ְ�,
ȭ�鸸 �帴���� �ݸ鿡, �޵�� ������ ��� ����� ����
������� ������ �κ��� ������� ������, ���� ������ ����
��. �׷��� ���ݱ��� ��� ���� �� ���޽� ������� ����
������ ���̴� ���� �޵�� ���Ͷ�� Ȯ���� �� �־���. */
/*******************************************************/

#include <opencv2/opencv.hpp> // openCV API�� ����ϱ� ���� �⺻ ������� ����
//opencv.hpp �� ��κ��� ��������� ���ԵǾ� ����
using namespace cv;
using namespace std;

//salt and pepper noise ���� �Լ�
Mat GetSaltAndPepperNoise(const Mat &src,int noiseNum) {

	Mat imgAddNoise(src);

	//�� �ٸ����� ������ ���� �ʱ�ȭ
	srand((int)time(NULL));

	for (int i = 0; i < noiseNum; i++) {

		//rows cols�� ����� �ȵǱ⶧���� ������ ����ó��
		int randRows = rand() % src.rows;
		int randCols = rand() % src.cols;

		//0 or 1 ��ȯ�� 1�϶� 255�θ� �������ν� �� ���� �ϼ�
		int saltAndPepper = (rand() % 2) * 255;
		//rows cols ��ġ�� 255 or 0����
		imgAddNoise.at<uchar>(randRows, randCols) = saltAndPepper;
		
	}

	return imgAddNoise;
}

int main() {
	//load
	Mat srcImage = imread(".//Image//255x255.png", cv::IMREAD_GRAYSCALE);

	imshow("Original Img", srcImage);

	Mat noiseImg=GetSaltAndPepperNoise(srcImage, 1000);

	//noise ���Ÿ� ���� ���� �˰��� ����
	// ��� ���� : Median Filtering | Gaussian Filter 

	//1. Median Filtering : salt&pepper ����� ����µ� �����ϰ�, ��踦 ������ 
	imshow("Add Noise", noiseImg);
	Mat medianImg;
	//ũ�⸦ 5x5�� �����Ͽ�, median ���͸� ����
	medianBlur(noiseImg, medianImg, 5);
	imshow("Median filter�� �̿��� Noise ����", medianImg);

	//2. Gaussian Filter
	Mat GaussianImg;
	//GaussianBlur �Լ� ���ο���, ���͸� �����ϰ� ������ ���Ÿ� ������
	GaussianBlur(noiseImg, GaussianImg, Size(5,5), 3.0);
	//Ȯ�ο�
	imshow("Gaussian Filter�� �̿��� Noise ����", GaussianImg);

	waitKey();

	return 0;
}