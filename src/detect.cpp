#include <stdio.h>
#include "detect.hpp"


#define NUM 8
static char i = 0;

CDetect* pCDetectObj[NUM] = {0};
static uchar numObj = 0;

void createDetect(uchar inNumber,int inwidth,int inheight)
{
	printf("enter Create Detect \n");
	if(inNumber >= 1 && inNumber <=8)
		numObj = inNumber;
	else
	{
		printf("error num of dectectObj\n");
		return ;
	}

	for(int i = 0;i < numObj ;i++)
	{
		pCDetectObj[i] = new CDetect();
		if(NULL == pCDetectObj[i])
		{
			printf("error in new pCDetectObj\n");
			return ;
		}
		pCDetectObj[i]->init(inwidth,inheight);
	}
	printf("create detectOBJ success \n");
	return;
}

void exitDetect()
{
	for(int i=0;i<numObj;i++)
	{
		if(pCDetectObj[i] != NULL)
		{
			delete []pCDetectObj[i];
			pCDetectObj[i] = NULL;
		}
	}
	printf("exit Detect \n");
	return ;
}

void mvDetect(int index,uchar* inframe,uchar* outframe,int width,int height)
{
	if(index >= 1 && index <=8)
	{
		index --;
		pCDetectObj[index] ->detect(inframe,outframe,width,height);
	}
	else
		printf("error index input,must between 1 to 8\n");

	return ;
}



CDetect::CDetect()
{
	pThis = this;
}

CDetect::~CDetect()
{
	free(temp.data);
}

void CDetect::init(int inwidth,int inheight)
{
	temp = Mat(inheight,inwidth,CV_8UC3);
	temp.data = (uchar*)malloc(inheight*inwidth*3);
	return ;
}


Mat CDetect::xtMoveDetect(Mat temp, Mat frame)
{
	Mat result = frame.clone();

    //1.将background和frame转为灰度图
    Mat gray1, gray2;

    cvtColor(temp, gray1, CV_BGR2GRAY);
    cvtColor(frame, gray2, CV_BGR2GRAY);

    //2.将background和frame做差
    Mat diff;
    absdiff(gray1, gray2, diff);
    //imshow("diff", diff);
    //3.对差值图diff_thresh进行阈值化处理
    Mat diff_thresh;
    threshold(diff, diff_thresh, 50, 255, CV_THRESH_BINARY);
    //imshow("diff_thresh", diff_thresh);
    //4.腐蚀
    Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(18, 18));
    erode(diff_thresh, diff_thresh, kernel_erode);
    //imshow("erode", diff_thresh);
    //5.膨胀
    dilate(diff_thresh, diff_thresh, kernel_dilate);
    //imshow("dilate", diff_thresh);

    //6.查找轮廓并绘制轮廓
    vector< vector<Point> > contours;
    findContours(diff_thresh, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //drawContours(result, contours, -1, Scalar(0, 0, 255), 2);//在result上绘制轮廓
    //7.查找正外接矩形
    vector<Rect> boundRect(contours.size());
    int tmpnum = 1;
    if(tmpnum > contours.size())
    	tmpnum = contours.size();
    for (int i = 0; i < tmpnum; i++)
    {
        boundRect[i] = boundingRect(contours[i]);
        printf("boundRect[%d].x = %d,boundRect[%d].y = %d \n",i,boundRect[i].x,i,boundRect[i].y);
        printf("boundRect[%d].width = %d,boundRect[%d].height = %d \n",i,boundRect[i].width,i,boundRect[i].height);
        rectangle(result, boundRect[i], Scalar(0, 0, 255), 2);//在result上绘制正外接矩形
    }
    putchar(10);
    return result;//返回result
}



int CDetect::detect(uchar* inframe,uchar* oframe,int width,int height)
{
	if(height <= 1080 && width <= 1920)
	{
		Mat frame = Mat(height,width,CV_8UC3,inframe);
		Mat result ;

		if (i == 0)//如果为第一帧（temp还为空）
		{
			i++;
			result = xtMoveDetect(frame, frame);//调用MoveDetect()进行运动物体检测，返回值存入result
		}
		else//若不是第一帧（temp有值了）
		{
			result = xtMoveDetect(temp, frame);//调用MoveDetect()进行运动物体检测，返回值存入result
		}
		//imshow("QiQi",result);
		memcpy(oframe,result.data,result.cols*result.rows*3);
		temp = frame.clone();
	}
	return 0;
}
