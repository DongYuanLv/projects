// testCanny.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void addpictuer(Mat & src1, double alpha, Mat & src2, double beta, Mat &dst);
void bold(const Mat &src, Mat & dst);
void DrawCircle(const Mat & src, Mat & dst, Point center);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

int main()
{
	Mat matSrc = imread("bird.jpg", IMREAD_UNCHANGED);
	Mat matresizeSrc, matSrcgray;
	Mat matDst1 = matSrc.clone();
	Mat matDst4 = matSrc.clone();
	Mat matDst2, matDst3;


	if (matSrc.empty())
	{
		exit(-1);
	}

	cvtColor(matSrc, matSrcgray, COLOR_BGR2GRAY);

	blur(matSrcgray, matSrcgray, Size(3, 3));

	Canny(matSrcgray, matDst1, 100, 50, 3);

	bold (matDst1, matDst2);

//	addpictuer(matSrc, 1, matDst2, 1.0, matDst3);

//	DrawCircle(matDst3, matDst4, Point(matDst3.cols / 2, matDst3.rows / 2));

	Mat mask(matSrc.rows, matSrc.cols, matSrc.type(),Scalar(255,255,255));

	circle(mask, Point(matDst2.cols / 2, matDst2.rows / 2), mask.cols / 32, Scalar(255,0,0), 6, 8);

	mask.copyTo(matDst4, matDst2);

	resize(matDst4, matDst4, Size(matDst4.cols / 4.0f, matDst4.rows / 4.0f),(0,0),(0,0),3);//感觉图片缩放之后明显边缘化效果不如以前

	namedWindow("bird1");

	moveWindow("bird1", 0, 0);

	//cout << dStartTime<< endl;

	imshow("bird1", matDst4);

	waitKey(-1);
	/*system("pause");*/
    return 0;
}
//--------------------------------融合函数----------------------------------

void addpictuer(Mat & src1, double alpha, Mat & src2, double beta, Mat &dst)
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
void bold(const Mat &src, Mat & dst)
{
	dst.create(src.size(), src.type());

	for (int j = 0; j < src.rows; j++) {
		const uchar* data1 = src.ptr<uchar>(j);
		uchar* data2 = dst.ptr<uchar>(j);
		for (int i = 0; i < src.cols; i++) {
			if (255 == data1[i])
			{
				data2[i - 1] = 255;
				data2[i] = 255;
				data2[i + 1] = 255;
			}
			else
			{
				data2[i] = data1[i];
			}

		}
	}
}
void DrawCircle(const Mat & src, Mat & dst, Point center)
{
	Mat mask;
	mask.create(src.rows, src.cols, src.type());
	dst.create(src.size(), src.type());
	cvtColor(mask, mask, CV_BGR2GRAY);
	mask = Scalar::all(255);
	dst = Scalar::all(0);
	circle(mask, center, src.cols / 32, Scalar(0), 6, 8);
	src.copyTo(dst, mask);
}