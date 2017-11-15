// testCanny.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void  transfomHSV(Mat, Mat);


int main()
{
	Mat matSrc = imread("37.tiff", IMREAD_UNCHANGED);
	Mat matSrcHSV; //存放HSV图片 H表示色调 S表示饱和度 V表示亮度
	Mat matSrcgray; //存放灰度图片
	Mat matDst1 = matSrc.clone();
	Mat matSrcMask, matSrcgrayMask;
	vector<Mat> matSrcsplit;
	Mat matH, matS, matV;
	int ThresholdS, ThresholdV;//S V颜色空间阈值

	if (matSrc.empty())
	{
		exit(-1);
	}
	
	
	cvtColor(matSrc, matSrcHSV, COLOR_BGR2HSV); //转化为HSV空间
	cvtColor(matSrc, matSrcgray, COLOR_BGR2GRAY);

	threshold(matSrcgray, matSrcgrayMask, 185, 255, 0);

	//blur(matSrcgray, matSrcgray, Size(3, 3));

	//Canny(matSrcgray, matDst1, 70, 140, 3);


 //   //double dStartTime = static_cast<double>(getTickCount());

 //   cvtColor(matDst1, matDst1, CV_GRAY2BGR); //将一通道的转化为二通道

	//matDst2 = 1.0 * matSrc + 1.0 * matDst1;
 //   //dStartTime = (static_cast<double>(getTickCount()) - dStartTime)/ getTickFrequency();
	 

	split(matSrcHSV,matSrcsplit); //分离颜色通道
	
	matH = matSrcsplit.at(0);  //  显示出各层颜色空间的值
	matS = matSrcsplit.at(1);
	matV = matSrcsplit.at(2);


//	matH = matH * 2;
	matS = matS /255 * 100;  //opencv中范围不一致，需要转换一下
	matV = matV /255 * 100;

	ThresholdS = 25; // 各空间初始化阈值
	ThresholdV = 50;

	threshold(matS, matS, ThresholdS,255, 1); //阈值函数
	threshold(matV, matV, ThresholdV,255, 0);

	matSrcMask = 0.5*matS + 0.5*matV; // 选出S空间小V空间大的地方

	threshold(matSrcMask, matSrcMask, 160, 255, 0); //将亮点二值化

	Mat element =getStructuringElement(MORPH_ELLIPSE,Size(5,5)); //放大亮斑点 运用膨胀运算
	dilate(matSrcMask, matSrcMask, element);
	dilate(matSrcgrayMask, matSrcgrayMask, element);

	namedWindow("colne");
	namedWindow("colne2");
	namedWindow("colne3");
//	namedWindow("colne4");
//	namedWindow("colne5");
	namedWindow("colne6");


	moveWindow("colne", 0, 0);
	moveWindow("colne2", matSrcHSV.cols, 0);
	moveWindow("colne3", matSrcHSV.cols * 2,0);
//	moveWindow("colne4", 0, matSrcHSV.rows);
//	moveWindow("colne5", matSrcHSV.cols, matSrcHSV.rows);
	moveWindow("colne6", matSrcHSV.cols*2, matSrcHSV.rows);
	

	//cout << dStartTime<< endl;

	imshow("colne",  matSrc);
	imshow("colne2", matSrcHSV);
	imshow("colne3", matSrcMask);
//	imshow("colne4", matS);
//	imshow("colne5", matV);
//	imshow("colne6", matH);
	imshow("colne6", matSrcgrayMask);	


	waitKey(-1);
	/*system("pause");*/
    return 0;
}
//--------------------------------融合函数----------------------------------

void addpictuer(  Mat & src1, double alpha, Mat  src2, double beta, Mat & dst)
{   
	if ((src1.empty())&&(src2.empty()))
	{
		exit(-1);
	}
	
	dst.create(src1.size(), src1.type());

	for (int j = 0; j < src1.rows; j++) {
		Vec3b* data1 = src1.ptr<Vec3b>(j);
		uchar* data2 = src2.ptr<uchar>(j);
		Vec3b* data3 = dst.ptr<Vec3b>(j);
		for (int i = 0; i < src1.cols; i++) {
			
			data3[i][0] = saturate_cast<uchar>(alpha*data1[i][0] + beta*data2[i]);
			data3[i][1] = saturate_cast<uchar>(alpha*data1[i][1] + beta*data2[i]);
			data3[i][2] = saturate_cast<uchar>(alpha*data1[i][2] + beta*data2[i]);
			
		}
	}
			
}
//---------------------------遍历函数---------------------------
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