/***********************************************************/
/*                 HW#2-5 : Logic Operation                 */
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
	Mat MaskImg = imread(".//Image//Fig0230(b).tif", IMREAD_GRAYSCALE); //gray level�� ���� 8bit 0~255����
	Mat SourceImg = imread(".//Image//Fig0230(a).tif", IMREAD_GRAYSCALE); //gray level�� ���� 8bit 0~255����
	
	Mat OutImg;
	bitwise_and(SourceImg, MaskImg, OutImg);
    imshow("SubImg1", OutImg);
	waitKey(0);
}
