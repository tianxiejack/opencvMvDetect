#ifndef MVDETECT_HPP_
#define MVDETECT_HPP_

extern void createDetect(uchar inNumber,int inwidth,int inheight);
extern void exitDetect();
extern void mvDetect(uchar index,uchar* inframe,uchar* outframe,int width,int height,cv::vector<cv::Rect> *boundRect);

#endif
