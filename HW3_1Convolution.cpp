/***********************************************************/
/*					 HW#3-1 : Convolution		     	     */
/*  �ۼ��� : �ۼ���          ��¥ : 2023�� 4��23��          */
/*                                                          */
/* ���� ���� : Convolution ��ü�� �ǹ̰� ������ ������, ����ũ
���¿� ũ�⿡ ���� ���꿡 ���� �ǹ̸� ������. smoothing ȿ���� 
�ο��ϴ°���þȰ� �ڽ� ����ũ �� ���� 1�� �Ǹ�, convolution�� 
�����ϰ�,������ ȿ���� ���ϴ� ������, ������, ���������� ����
�հ谡 0�� �� �� �ֵ��� ����ũ�� �����. ����� ���� �밢��
���� ǥ���� ����ũ�� �̿��ϸ鼭, �̵��Ǵ� ����� �����Ѵ�. 
�� ��� ����� filter2D�� �̿�������, ���� Ŀ���� ����
����ߴ�. (�ڽ� Ŀ�� ����)									*/
/**********************************************************/

#include <opencv2/opencv.hpp> // openCV API�� ����ϱ� ���� �⺻ ������� ����
//opencv.hpp �� ��κ��� ��������� ���ԵǾ� ����
using namespace cv;
using namespace std;

int main() {

	//convolution�� ����� ������ �̹��� ���ε�
	Mat src=imread(".//Image//255x255.png",IMREAD_GRAYSCALE);

	imshow("original Img", src);
	/* Box Filter Algorithm Default */
	//1/9�� ������ͷ� ��� -> 3x3 -> default 1/9�� ����
	Mat BoxConv;
	
	//Size Class�� 3x3ũ���� box convolution ����, box �̱⶧���� 1/9 ����.
	//dtype = -1 : �Է� ����� ����
	//nomalize -> defalut == True �ε�, True�� ���־���� Ŀ�� ũ��� ����ȭ.
	boxFilter(src, BoxConv, -1, Size(3, 3), Point(-1, -1));

	imshow("BoxFilter", BoxConv);

	/* Gaussian Filter Algorithm ����� �Ʒ� �ּ� Ȱ��ȭ */
	/*	Mat GaussianCov;

	//Gaussian ���� ���� ����� 
	Mat GaussianKernel = (Mat_<float>(5, 5) << .0000, .0000,0.0002,.0000,.0000,
											.0000,.0113,.0873,.0113,.0000,
										.0002,.0837,.6187,.0837,.0002,
										.0000,.0113,.0837,.0113,.0000,
										.0000,.0000,.0002,.0000,.0000);

	//filter2D �� �̿��� ���� ���� ����þ� ���� �����ϱ�
	filter2D(src, GaussianCov, -1, GaussianKernel,Point(-1,-1));
	//�̹��� ����
	imshow("Gaussian Conv", GaussianCov);
	*/

	/* ������ Filter Algorithm ����� �Ʒ� �ּ� Ȱ��ȭ */
	/*
	* Sharpening 0 -1 0
	*            -1 5 -1
	*            0 -1 0 �� ǥ���ϱ� ���ؼ� ���� kenel����.
	Mat SharpeningKenel = (Mat_<int>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);

	Mat SharpeningConv;
	filter2D(src, SharpeningConv, -1, SharpeningKenel); //filter�� ���� ���� �����װ� Conv�����ν� 
	����ޱ�.

	cout << SharpeningKenel << endl;
	imshow("Sharpening Cov", SharpeningConv);
	*/
	
	/* ����, ���� Edge Filter Algorithm ����� �Ʒ� �ּ� Ȱ��ȭ */
	/* 1�� �̺н� 1,0,-1 �� Mask���� ��ԵǴµ� ���� �������� �÷����� Ŀ���� ǥ���ϱ� ����
	������ 1,0,-1
		1,0,-1
		1,0,-1 �� ǥ��
	������ 1,1,1,
			0,0,0,
			-1,-1,-1 �� ǥ���Ѵ�.

	Mat HorizKenel=(Mat_<int>(3,3) <<1,1,1,
									0,0,0,
									-1,-1,-1);
	cout << "HorizeKenel " << HorizKenel << endl;
	Mat VertiKenel=(Mat_<int>(3, 3) << 1, 0, -1,
									1, 0, -1,
									1, 0, -1);
	cout << "VertiKenel " << VertiKenel << endl;

	// �߾Ӱ� -1,-1�� ����
	Mat HoriDst, VertisDst;
	filter2D(src, HoriDst, -1, HorizKenel, Point(-1, -1));
	filter2D(src, VertisDst, -1, VertiKenel, Point(-1, -1));

	//���� ���� ���� ���� �� ���
	imshow("horizontal Convolution", HoriDst);
	imshow("vertical Convolution", VertisDst);
	*/

	/* Motion Mask Algorithm ����� �Ʒ� �ּ� Ȱ��ȭ*/
	/*
	* Motion (��, �����̴� ȿ��)�� �ֱ� ���ؼ�, �밢�� �������� ����ġ ���� �ο���
	* ���, ������� ���� �Ŀ� �����̴� ����� ǥ���� �� �ִ�.
	Mat MotionKenel = (Mat_<float>(5, 5) << .0304, .0501, 0, 0, 0,
											.0501, .1771, .0519, 0, 0,
											0, .0519, .1771, .0519, 0,
											0, 0, .0519, .1771, .0501,
											0, 0, 0, .0501, .0304);

	cout << "MotionKenel = " << MotionKenel << endl;

	Mat MotionDst;
	//Motion Mask�� �̿��� Filter����.
	filter2D(src, MotionDst, -1, MotionKenel, Point(-1, -1));

	imshow("Motion Conv", MotionDst);
	*/
	waitKey();// ȭ�� ������� �ʰ� ���
	
}