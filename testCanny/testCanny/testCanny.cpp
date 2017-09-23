// testCanny.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void addpictuer(Mat & src1, double alpha, Mat src2, double beta, Mat & dst);
void bold(Mat  src1, Mat & src2);


int main()
{
	Mat matSrc = imread("bird.jpg", IMREAD_UNCHANGED);
	Mat matresizeSrc, matSrcgray;
	Mat matDst1 = matSrc.clone();
	Mat matDst2 = matSrc.clone();
	Mat matDst3, matDst4;

	if (matSrc.empty())
	{
		exit(-1);
	}

	cvtColor(matSrc, matSrcgray, COLOR_BGR2GRAY);

	blur(matSrcgray, matSrcgray, Size(3, 3));

	Canny(matSrcgray, matDst1, 70, 100, 3);
	Canny(matSrcgray, matDst2, 120, 170, 3);

	Mat element = getStructuringElement(MORPH_RECT, Size(2, 2));

	morphologyEx(matDst1, matDst3, MORPH_DILATE, element);
	morphologyEx(matDst2, matDst4, MORPH_DILATE, element);

	//bold (matDst1, matDst3);
	//bold (matDst2, matDst4);

	addpictuer(matSrc, 1, matDst3, 1.0, matDst3);
	addpictuer(matSrc, 1, matDst4, 1.0, matDst4);


	//resize(matDst1, matDst1, Size(matDst1.cols/ 4.0f, matDst1.rows / 4.0f));
	//resize(matDst2, matDst2, Size(matDst2.cols / 4.0f, matDst2.rows / 4.0f));
	//resize(matSrc, matresizeSrc, Size(matSrc.cols / 4.0f, matSrc.rows / 4.0f));

	double dStartTime = static_cast<double>(getTickCount());

	//addpictuer(matresizeSrc, 1.0, matDst1, 1.0, matDst3);
	//addpictuer(matresizeSrc, 1.0, matDst2, 1.0, matDst4);

    //cvtColor(matDst1, matDst1, CV_GRAY2BGR); 将一通道的转化为二通道
	//cvtColor(matDst2, matDst2, CV_GRAY2BGR);

	//addWeighted(matresizeSrc, 1.0, matDst1, 1.0, 0.0, matDst3);
	//addWeighted(matresizeSrc, 1.0, matDst2, 1.0, 0.0, matDst4);


	//matDst3 = 1.0 * matresizeSrc + 1.0 * matDst1;
	//matDst4 = 1.0 * matresizeSrc + 1.0 * matDst2;
	dStartTime = (static_cast<double>(getTickCount()) - dStartTime)/ getTickFrequency();
	
	resize(matDst3, matDst3, Size(matDst3.cols / 4.0f, matDst3.rows / 4.0f),(0,0),(0,0),3);//感觉图片缩放之后明显边缘化效果不如以前
	resize(matDst4, matDst4, Size(matDst4.cols / 4.0f, matDst4.rows / 4.0f), (0, 0), (0, 0), 3);
	resize(matSrc, matresizeSrc, Size(matSrc.cols / 4.0f, matSrc.rows / 4.0f), (0, 0), (0, 0), 3);


	namedWindow("bird1");
	namedWindow("bird2");


	moveWindow("bird1", 0, 0);
	moveWindow("bird2", matDst3.cols, 0);

	//cout << dStartTime<< endl;

	imshow("bird1", matDst3);
	imshow("bird2", matDst4);


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
//---------------------------加粗函数---------------------------
void bold( Mat src1, Mat & src2)
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