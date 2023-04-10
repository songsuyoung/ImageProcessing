/***********************************************************/
/*       HW#2-6 : Connected Component in OpenCV             */
/*  �ۼ��� : �ۼ���          ��¥ : 2023�� 4��10��          */
/*                                                          */
/* ���� ���� : connected component�Լ��� �̿��ؼ� �Լ��� �� */
/*���� ����, �󺧸��� ������� Ȯ���Ѵ�.                    */
/**********************************************************/

#include <opencv2/opencv.hpp> // openCV API�� ����ϱ� ���� �⺻ ������� ����
//opencv.hpp �� ��κ��� ��������� ���ԵǾ� ����
using namespace cv;
using namespace std;

void main() {
	Mat OriginalImg = imread(".//Image//logo.jpg", IMREAD_GRAYSCALE); //gray level�� ���� 8bit 0~255����
	
    imshow("OriginalImg", OriginalImg); //���� �̹����� ����Ѵ�.

	Mat otsuResult;
	//�Ӱ谪�� ã�� ����ȭ ����
	threshold(OriginalImg, otsuResult, 0, 255, THRESH_OTSU);
	imshow("otsuResultImg", otsuResult);
	//���� �˰����� ����� ���

	Mat labels, stats, centroids, img_color;

	//�׷��� �̹����� �÷��� ����
	cvtColor(OriginalImg, img_color, COLOR_GRAY2BGR);
	
	//�󺧸��� ���� ��ȯ, �̹����� Ȯ���ϰ� �� �̹����� ���̺��� ������
	int numOfLables =connectedComponentsWithStats(otsuResult, labels, stats, centroids,8, CV_32S);

	//�󺧸��� �̹����� Ư�� ���� �÷��� ǥ�����ֱ�  
	for (int y = 0; y < labels.rows; ++y) {

		int* label = labels.ptr<int>(y);
		Vec3b* pixel = labels.ptr<Vec3b>(y);


		for (int x = 0; x < labels.cols; ++x) {

			if (label[x] == 1) {
				pixel[x][0] = 0;
				pixel[x][1] = 255; //ã�� ���̺��� �� ����
				pixel[x][2] = 0;
			}
		}
	}


	//�󺧸� �� �̹����� ���� ���簢������ �ѷ��α� 
	for (int j = 1; j < numOfLables; j++) {

		//�ڽ��� �ѷ��α� ���ؼ� �� ��ġ�� ���� ��ȯ.
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		int x = centroids.at<double>(j, 0); //�߽���ǥ
		int y = centroids.at<double>(j, 1);

		circle(img_color, Point(x, y), 5, Scalar(255, 0, 0), 1);
		//���� �׸� �׸��� �κ�
		rectangle(img_color, Point(left, top), Point(left + width, top + height),
			Scalar(0, 0, 255), 1);
		//���� 
		putText(img_color, to_string(j), Point(left + 10, top + 10),
			FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
	}
	//���
	imshow("labelsImg", img_color);

	waitKey(0);
}
