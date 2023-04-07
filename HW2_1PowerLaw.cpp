/********************************************************/
/*             HW#1 : Power Law                         */
/*  �ۼ��� : �ۼ���          ��¥ : 2023�� 4�� 6��      */
/*                                                      */
/* ���� ���� : pow�Լ��� �̿��� �̹����� gray level�� ��*/
/* �� ������ �����Ѵ�. r>1 ���α׸� �ǹ�, r<1�̸� �α׺�*/
/* ȯ�� �ǹ��Ѵ�. ������ ���� �޶����� �̹����� Ȯ���غ�*/
/* ��. ���� �� ���������� 1.0 3.0 4.0 5.0�� ���� ���캸 */
/* �Ҵ�.                                                */
/*******************************************************/

#include <opencv2/opencv.hpp> // openCV API�� ����ϱ� ���� �⺻ ������� ����
//opencv.hpp �� ��κ��� ��������� ���ԵǾ� ����
using namespace cv;
using namespace std;

void powImage(Mat, double);

int main()
{
	Mat srcImage = imread(".//Image//Fig0309.tif", IMREAD_GRAYSCALE); //�̹����� �о�´�

	if (srcImage.empty()) { //�̹����� ���� ��, ���α׷� ����
		return - 1;
	}

	Mat flmage; //���� ����� ���� Mat ��ü
	srcImage.convertTo(flmage, CV_32F); //���� ����� ���� CV_32F �ڷ������� ��ȯ
	powImage(flmage, 3.0); //�Լ��� ���������ν�, main�Լ� �ܼ�ȭ

	waitKey();
	return 0;
}

/*normarlize�Լ��� �ʿ��� ������ �˱� ���ؼ�, �ּ�ó�� �� ������ ���
r>1�̸�, ���α׿� ��������.. ���� ������ �������� ȿ���� ���Եƴ�.
normalize�� �����ϰ� �Ǹ� ����ȭ ������ ��ġ�鼭 ������ ������׷� ������ ������ �ȴ� */
//�ߺ��� �ڵ带 ���̱� ���� �Լ� ����
void powImage(Mat originalImg,double power) {
	Mat powImage;
	pow(originalImg, power, powImage); //powImage = originalImg ^ power
	normalize(powImage, powImage, 0, 1.0, NORM_MINMAX); //pow���� powImage normalize��Ŵ
	imshow("powFunction_"+to_string(power), powImage); //���
}