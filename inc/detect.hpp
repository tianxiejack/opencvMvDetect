#ifndef DETECT_HPP_
#define DETECT_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void createMvDetect();
void exitMvDetect();
void mvDetect(uchar index,uchar* src,uchar* out,int height,int width,Rect *boundRect);


class CDetect
{
	public:
		CDetect();
		~CDetect();

		void init(int inwidth,int inheight);
		void destory();
		int detect(uchar* inframe,uchar* oframe,int width,int height,Rect *boundRect);
		Mat xtMoveDetect(Mat temp, Mat frame,Rect *boundRect);

		CDetect* pThis;

		Mat temp;

};











#endif
