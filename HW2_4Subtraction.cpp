/***********************************************************/
/*                 HW#2-4 : Subtraction                     */
/*  �ۼ��� : �ۼ���          ��¥ : 2023�� 4��10��          */
/*                                                          */
/* ���� ���� : ��Ģ����� ���ݱ��� ��� ������ ������, ���� */
/* �غ���.�� �̹����� ���̸� �̿���, �޶��� ���� Ȯ���ϰ� ��*/
/* �ο� ������� �̿��Ͽ� ���� ������ �� ������ �����Ѵ�.   */
/**********************************************************/

#include <opencv2/opencv.hpp> // openCV API�� ����ϱ� ���� �⺻ ������� ����
//opencv.hpp �� ��κ��� ��������� ���ԵǾ� ����
using namespace cv;
using namespace std;


Mat ShowDiff_C(Mat SubImg);
Mat ShowDiff_D(Mat SubImg);

void main() {
	Mat MaskImg = imread(".//Image//Fig0228(a).tif", IMREAD_GRAYSCALE); //gray level�� ���� 8bit 0~255����
	Mat AliveImg = imread(".//Image//Fig0228(b).tif", IMREAD_GRAYSCALE); //gray level�� ���� 8bit 0~255����
	
	Mat SubImg1,SubImg2;
	subtract(MaskImg, AliveImg, SubImg1);
	subtract(MaskImg, AliveImg, SubImg2); //�� �̹����� ����

	SubImg1 =ShowDiff_C(SubImg1); //c �̹����� �����Ѵ�
	SubImg2= ShowDiff_D(SubImg2); //d �̹����� �����Ѵ�
	imshow("SubImg2", SubImg2);
    imshow("SubImg1", SubImg1);
	waitKey(0);
}

Mat ShowDiff_C(Mat SubImg) {
	//������ �������� �̿��Ͽ�, ���� �κа� ���� �κ��� �����Ѵ�.
	double alpha = 2, beta = 0.8;
	SubImg.convertTo(SubImg, -1, alpha, beta);
	//�����ϱ� ���ؼ�, ������ �ǽ��Ѵ�.
	SubImg = 200 - SubImg;

	return SubImg; 
}

Mat ShowDiff_D(Mat SubImg) {
	//�������� �����ϱ� ���ؼ� *5�� �Ѵ�.
	SubImg *= 5;
	//���� �κ��� ȸ������, ȸ���κ��� ��� ������ ��ȯ�ϱ� ���ؼ� ������ �ǽ��Ѵ�.
	SubImg = 200 - SubImg;

	return SubImg;
}