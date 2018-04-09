#ifndef DETECT_HPP_
#define DETECT_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

typedef struct para_t{
	uchar* inframe;
	int width;
	int height;
	Rect* boundRect;
	uchar frameIndex;
	uchar index;
}parm;

class CDetect
{
	public:
		CDetect();
		~CDetect();

		void init(int inwidth,int inheight);
		void destory();
		void detect(uchar* inframe,int width,int height,cv::Rect *boundRect,uchar frameindex);
		void xtMoveDetect(cv::Mat temp, cv::Mat frame,cv::Rect *boundRect);

		CDetect* pThis;

		Mat temp;
		uchar frameindex ;

};



#endif
