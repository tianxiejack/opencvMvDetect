#ifndef BACK_GROUND_HPP_
#define BACK_GROUND_HPP_


#include <stdio.h>
//#include "stdafx.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <iostream>
#include "cvaux.h"
#include "cxmisc.h"

using namespace std;
using namespace cv;

class CBgMvDetect
{
public:
	CBgMvDetect();
	~CBgMvDetect();

	void init(int inwidth,int inheight);
	void destroy();
	void gbMvDetect(uchar* src,uchar *dst,int width,int height,Rect* boundRect,uchar frameindex);
	void BackgroundDiff(IplImage* SrcImg, IplImage* FroundImg, IplImage* BackgroundImg,
			int nFrmNum, int threshold_method);


	CBgMvDetect* pThis;

	//声明IplImage指针
	IplImage* pFrame ;
	IplImage* pFroundImg ;
	IplImage* pBackgroundImg ;

	IplImage* SrcImg_gray 		= 	NULL;//源图像的灰度图像
	IplImage* SrcImg_grayf 		=	NULL;  //单通道浮点图像用于背景建模
	IplImage* FroundImgf 		= 	NULL;
	IplImage* BackgroundImgf 	= 	NULL;
	IplImage* FroundImg_temp 	= 	NULL;

};





















void BackgroundDiff(IplImage* SrcImg, IplImage* FroundImg, IplImage* BackgroundImg, int nFrmNum, int threshold_method);
void cvOtsu(IplImage *src, int *thresholdValue);
void PrintVedioInfo(CvCapture* pCapture, IplImage* img);
void Labeling(IplImage *src, IplImage *dst);




#endif
