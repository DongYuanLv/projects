// testCanny.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

void matrhreshold (Mat &, Mat &, int , int, Mat &);


int main()
{
	Mat matSrc = imread("1.tiff", IMREAD_UNCHANGED);
	Mat matSrcHSV; //���HSVͼƬ H��ʾɫ�� S��ʾ���Ͷ� V��ʾ����
//	Mat matSrcgray; //��ŻҶ�ͼƬ
	Mat matDst1 = matSrc.clone();
	Mat matSrcMaskL, matSrcMaskH;
	vector<Mat> matSrcsplit;
	Mat matH, matS, matV;
	int ThresholdSL, ThresholdVL, ThresholdSH, ThresholdVH;//S V��ɫ�ռ���ֵ

	if (matSrc.empty())
	{
		exit(-1);
	}
	
	
	cvtColor(matSrc, matSrcHSV, COLOR_BGR2HSV); //ת��ΪHSV�ռ�
//	cvtColor(matSrc, matSrcgray, COLOR_BGR2GRAY);

	//blur(matSrcgray, matSrcgray, Size(3, 3));

	//Canny(matSrcgray, matDst1, 70, 140, 3);


 //   //double dStartTime = static_cast<double>(getTickCount());

 //   cvtColor(matDst1, matDst1, CV_GRAY2BGR); //��һͨ����ת��Ϊ��ͨ��

	//matDst2 = 1.0 * matSrc + 1.0 * matDst1;
 //   //dStartTime = (static_cast<double>(getTickCount()) - dStartTime)/ getTickFrequency();
	 

	split(matSrcHSV,matSrcsplit); //������ɫͨ��
	
	matH = matSrcsplit.at(0);  //  ��ʾ��������ɫ�ռ��ֵ
	matS = matSrcsplit.at(1);
	matV = matSrcsplit.at(2);


//	matH = matH * 2;
	matS = matS /255 * 100;  //opencv�з�Χ��һ�£���Ҫת��һ��
	matV = matV /255 * 100;

	ThresholdSL = 25; // ���ռ��ʼ������ֵ
	ThresholdVL = 50;

	ThresholdSH = 20; // ���ռ��ʼ������ֵ
	ThresholdVH = 78;

	matrhreshold(matS, matV, ThresholdSL, ThresholdVL, matSrcMaskL);

	matrhreshold(matS, matV, ThresholdSH, ThresholdVH, matSrcMaskH);


	namedWindow("colne");
	namedWindow("colne2");
	namedWindow("colne3");
//	namedWindow("colne4");
//	namedWindow("colne5");
//	namedWindow("colne6");


	moveWindow("colne", 0, 0);
	moveWindow("colne2", matSrcHSV.cols, 0);
	moveWindow("colne3", matSrcHSV.cols * 2,0);
//	moveWindow("colne4", 0, matSrcHSV.rows);
//	moveWindow("colne5", matSrcHSV.cols, matSrcHSV.rows);
	moveWindow("colne6", matSrcHSV.cols*2, matSrcHSV.rows);
	

	//cout << dStartTime<< endl;

	imshow("colne",  matSrc);
	imshow("colne2", matSrcHSV);
	imshow("colne3", matSrcMaskL);
//	imshow("colne4", matS);
//	imshow("colne5", matV);
	imshow("colne6", matSrcMaskH);
	


	waitKey(-1);
	/*system("pause");*/
    return 0;
}
//--------------------------------��ֵ����----------------------------------

void matrhreshold(  Mat & matInputS, Mat & matInputV ,int ThresholdS, int ThresholdV, Mat & matOutput)
{   
	if ((matInputS.empty())&&(matInputV.empty()))
	{
		exit(-1);
	}
	Mat  matS, matV; // ��ʱ���ֵ����ͼ

	threshold(matInputS, matS, ThresholdS, 255, 1); //��ֵ����
	threshold(matInputV, matV, ThresholdV, 255, 0);

	matOutput  = 0.5*matS + 0.5*matV;// ѡ��S�ռ�СV�ռ��ĵط�

	threshold(matOutput, matOutput, 160, 255, 0); //�������ֵ��

	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(5, 5)); //�Ŵ����ߵ� ������������
	dilate(matOutput, matOutput, element);
	
}
//---------------------------��������---------------------------
void  transfomHSV( Mat src1, Mat & src2)
{   
	src2.create(src1.size(), src1.type());

	for (int j = 0; j < src1.rows; j++) {
		uchar* data1 = src1.ptr<uchar>(j);
		uchar* data2 = src2.ptr<uchar>(j);
		for (int i = 0; i < src1.cols; i++) {
			if (data1[i] == 255)
			{   
				data2[i - 2] = 255;
				data2[i - 1] = 255;
				data2[i] = 255;
				data2[i + 1] = 255;
				data2[i + 2] = 255;
			}
			else
			{
				data2[i] = data1[i];
			}

		}
	}


}