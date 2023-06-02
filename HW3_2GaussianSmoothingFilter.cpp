/***********************************************************/
/*		    HW#3-2 : Gaussian Smoothing Filter             */
/*  �ۼ��� : �ۼ���          ��¥ : 2023�� 4�� 24��          */
/*                                                          */
/* ���� ���� :getGaussianKernel�� GaussianBlur�� sig���� ��ġ�� ��
getGaussianKenel�� filter2D�� �̿��� ���� ��ȿ���� �����߰�,
GaussianBlur�� ��쿡 cv2���� �������ִ� �Լ��� ���� �̿��ߴ�.
������, �� ����� �ٸ��� ���� �� �ٸ��� ã�ƺ�����,getGaussianKenel��
1���� ����þ� ������ �̿��ϰ�, GaussianBlur�� 2���� ����þ� ����
�� ����Ѵٴ� ���� �˰� �Ǿ���.                            */
/**********************************************************/

#include <opencv2/opencv.hpp> // openCV API�� ����ϱ� ���� �⺻ ������� ����
//opencv.hpp �� ��κ��� ��������� ���ԵǾ� ����
using namespace cv;
using namespace std;

int main() {
	Mat src = imread(".//Image//255x255.png", IMREAD_GRAYSCALE);
	imshow("original Img", src);


	/*Gaussian�� ��� ǥ�������� Ŀ����, �����ĸ� ���� ����ϰ�, �۾����� ���� ����ϴ� ������ ����
	��, �������� ������ ǥ�������� ���� ������ ����.*/

	vector<Mat> SigKernel(4);

	for (int i = 0; i < SigKernel.size(); i++) {
		SigKernel[i] = getGaussianKernel(5, i+1); //sig=1 �϶�
	}

	//�� 4������ �̿��� ����þ� Ŀ���� �̿��� ���͸� ������ �� �����̴�.

	vector<Mat> Sigdst(4);

	for (int i = 0; i < Sigdst.size(); i++) {
		filter2D(src, Sigdst[i], -1, SigKernel[i]); //1���� ����̱⶧����, �ι�° ������ ����þ� ���Ϳ��� ����� �ٸ��� �� �� ����
	}

	//�� ���� ������ ����� imshow �� �����ε�, �� ����� ����þ� ������ ���͸� �ٷ� ����
	//�������� ���̸� �˾ƺ� ����!

	for (int i = 0; i < 4; i++) {
		imshow("Sig" + to_string(i+1), Sigdst[i]);
	}
	//����þ� �� ���͸� ��������� ����� �˾ƺ�.
	vector<Mat> GaussainFilter(4);

	for (int i = 0; i < GaussainFilter.size(); i++) {
		GaussianBlur(src, GaussainFilter[i], Size(5, 5), i+1); //���� �޸� 2���� ����þ� ������!!! y sig�� �������ϸ�, x���� ��ġ ��Ű�� ������
		//����þ� ���� �̿��������� �� �帴������ ����� ���� �� �־���.
		imshow("GaussBlur Filter " + to_string(i+1), GaussainFilter[i]);
	}

	waitKey(0);
}