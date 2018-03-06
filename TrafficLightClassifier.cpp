#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
using namespace std;
using namespace cv;

int main(void)
{
	CascadeClassifier trafficLightCascader;
	string Cascade_name = "TrafficLight.xml";

	if (!trafficLightCascader.load(Cascade_name))
	{
		cout<<"Can't load the face feature data"<<endl;
		return -1;
	}
	
	vector<Rect> trafficLights;

	//����ͼƬ
	ifstream imfile("E://TL//pics.txt");
	//char read_flag[100];
	string read_flag;

	while(getline(imfile, read_flag))
	{

		//����ͼƬ
		//imfile>>read_flag;

		Mat src = imread(read_flag, -1);	//-1��ԭʼͼƬ�����ı�����Ⱥ�ͨ����
		CvRect AssignRect = Rect(0, 0, src.cols, src.rows/2);
		Mat srcImage = src(AssignRect);
				
		Mat grayImage(srcImage.rows, srcImage.cols, CV_8UC1);

		cvtColor(srcImage, grayImage, CV_BGR2GRAY);
		equalizeHist(grayImage, grayImage);	//ֱ��ͼ��ֵ��

		trafficLightCascader.detectMultiScale(grayImage, trafficLights, 1.1, 1, CV_HAAR_SCALE_IMAGE | CV_HAAR_FEATURE_MAX, Size(3, 3));
		//trafficLightCascader.detectMultiScale(grayImage, trafficLights, 1.1, 3, 0, Size(3,3));
		//detectMultiScale()��cvSize������ʾ��Ѱ�ҽ�ͨ�Ƶ���С������������������󣬻��Զ�ʧС����Ϊ���ۼ��ټ�����

		for (int i=0; i<trafficLights.size(); ++i)
		{
			rectangle(src, trafficLights[i], Scalar(0, 255, 0), 2, 8, 0);
		}

		imshow("src", src);
		waitKey(100);
	}

	return 0;
}