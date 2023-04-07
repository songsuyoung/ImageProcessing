/********************************************************/
/*          HW#2-2 : Piecewise-Linear Transform         */
/*  �ۼ��� : �ۼ���          ��¥ : 2023�� 4�� 7��      */
/*                                                      */
/* ���� ���� : �� �̹����� ȭ�ҿ� ����, 3���� �����ǹ���*/
/*���� ���ϰ�, �� �����Ŀ� ���� ���� �ٸ��� �����Ѵ�. */
/*����� ������ ������ y=s*(originalVal-x1)+y1����, ũ��*/
/*�� ���� �ٸ� ������� �����´�.                    * /
/*******************************************************/

#include <opencv2/opencv.hpp> // openCV API�� ����ϱ� ���� �⺻ ������� ����
//opencv.hpp �� ��κ��� ��������� ���ԵǾ� ����
using namespace cv;
using namespace std;


void main() {
	Mat srcImage = imread(".//Image//Fig0310.tif", cv::IMREAD_GRAYSCALE); //gray level�� ���� 8bit 0~255����

	//���� ���� �ƴѰ�?
	//(0,0) (8,8) y2-y1/x2-x1   (64,64) (255,255)
	double r1 = 100, s1 = 50, r2 = 125, s2 = 200;
	Mat dstImage=srcImage.clone();
	double scale;
	
	//�� �ȼ��� ȭ�ҿ� ���� ���� ����� ����
	for (int i = 0; i < srcImage.rows; i++) {
		for (int j = 0; j < srcImage.cols; j++) {
			uchar originalVal = srcImage.at<uchar>(i, j);
			if (originalVal <= r1) {
				//r1���� ���� ��, ���� ���
				scale = s1 / r1;
				dstImage.at<uchar>(i, j) = (originalVal-r1) * scale+s1;
			}
			else if (originalVal >= r2) {
				//r2���� Ŭ ��, ���� ���, gray ;evel�ϰ�� 8��Ʈ��, 0~255������ �̷����.
				scale = (255.0-s2)/ (255.0 - r2);
				dstImage.at<uchar>(i, j) = (originalVal-r2) * scale + s2;
			}
			else {
				//r1<=x<=r2 �����϶�, (r1,s1) - (r2,s2) ������ ������ ������ ���� �̿���, ���.
				scale = (s2-s1) / (r2-r1);
				dstImage.at<uchar>(i, j) = (originalVal - r2) * scale + s2;
			}
			// ������ ������ ���� : scale * (originalVal-r1) + s1
			// �Ѵ� �ش���� ������� ���� r1=s2�� ������.
		}
	}
	imshow("dstImage", dstImage);
	waitKey();
}