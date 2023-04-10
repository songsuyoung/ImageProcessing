/********************************************************/
/*          HW#2-3 : Bit Plane Slicing                  */
/*  �ۼ��� : �ۼ���          ��¥ : 2023�� 4��10��      */
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
	Mat srcImage = imread(".//Image//Fig0314.tif", cv::IMREAD_GRAYSCALE); //gray level�� ���� 8bit 0~255����
	imshow("Original Img", srcImage);
	int cols, rows, x, y;

	cols = srcImage.cols;
	rows = srcImage.rows;

	printf("%d %d \n", srcImage.rows, srcImage.cols);
	Mat out[9];

    //CV_8UC1 8bit + unsigned + channel 1�� out[i] �ϳ��� level�� ���ϰ�, srcImage�� ũ���� ��� Mat�� 0���� �ʱ�ȭ
	for (int i = 0; i <= 8; i++) {
		out[i] = Mat(rows, cols, CV_8UC1, Scalar(0));
	}

	for (int i = 0; i <= 8; i++) { //bit plane ���� �ǹ�
		for (int x = 0; x < rows; x++) { //row
			for (int y = 0; y < cols; y++) { //col�� srcImage�� �� ������ �ش��ϴ� ���� �ֱ� ���� ����.
				//�ش� �ڸ����� ���� �ִ��� ������ true false�� Ȯ���ϱ� ���ؼ� and���� �ǽ�. 
				out[i].at<uchar>(x, y) = (srcImage.at<uchar>(x, y) & uchar(pow(2,i)))? uchar(255) : uchar(0);
			}
		}
		string s = "dstImage";
		s += to_string(i);
		imshow(s, out[i]);
	}


	waitKey();
}