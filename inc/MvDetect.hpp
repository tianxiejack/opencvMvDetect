#ifndef MVDETECT_HPP_
#define MVDETECT_HPP_

//inNumber 代表创建 检测OBJ的实例个数  有效值从1到8
extern void createDetect(uchar inNumber,int inwidth,int inheight);
extern void exitDetect();

//index 代表第几个 检测OBJ 执行，boundRect 输出 目标的矩形框参数
extern void mvDetect(uchar index,uchar* inframe,uchar* outframe,int width,int height,Rect *boundRect);

#endif
