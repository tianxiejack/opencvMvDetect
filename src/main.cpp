#include "detect.hpp"
#include "background.hpp"
#include "stdio.h"

#define NUM 8
static uchar frameindex = 0;

CDetect* pCDetectObj[NUM] = {0};
CBgMvDetect* pCBgMvDetectObj[NUM] ={0};

static uchar numObj = 0;

void createDetect(uchar inNumber,int inwidth,int inheight)
{
	printf("enter Create Detect \n");
	frameindex = 0;
	if(inNumber >= 1 && inNumber <=8)
		numObj = inNumber;
	else
	{
		printf("error num of dectectObj\n");
		return ;
	}

	for(int i = 0;i < numObj ;i++)
	{
		//if(whichAnaly)
		if(1)
		{
			pCDetectObj[i] = new CDetect();
			if(NULL == pCDetectObj[i])
			{
				printf("error in new pCDetectObj\n");
				return ;
			}
			pCDetectObj[i]->init(inwidth,inheight);
		}
		else
		{
			pCBgMvDetectObj[i] = new CBgMvDetect();
			if(NULL == pCBgMvDetectObj[i])
			{
				printf("error in new pCBgMvDetectObj\n");
				return ;
			}
			pCBgMvDetectObj[i]->init(inwidth,inheight);
		}
	}
	printf("create detectOBJ success \n");
	return;
}

void exitDetect()
{
	for(int i=0;i<numObj;i++)
	{
		//if(whichAnaly)
		if(1)
		{
			if(pCDetectObj[i] != NULL)
			{
				delete []pCDetectObj[i];
				pCDetectObj[i] = NULL;
			}
		}
		else
		{
			if(pCBgMvDetectObj[i] != NULL)
			{
				delete []pCBgMvDetectObj[i];
				pCBgMvDetectObj[i] = NULL;
			}
		}

	}
	printf("exit Detect \n");
	return ;
}

void mvDetect(uchar index,uchar* inframe,int width,int height,Rect *boundRect)
{
	//if(whichAnaly)
	if(1)
	{
		if(index >= 1 && index <=8)
		{
			index --;
			pCDetectObj[index] ->detect(inframe,width,height,boundRect,frameindex);
			if(frameindex == 0)
				frameindex++;
		}
		else
			printf("error index input,must between 1 to 8\n");
	}
	else
	{
		if(index >= 1 && index <=8)
		{
			index --;
			pCBgMvDetectObj[index] ->gbMvDetect(inframe,NULL,width,height,boundRect,frameindex);
			if(frameindex == 0)
				frameindex++;
		}
		else
			printf("error index input,must between 1 to 8\n");
	}

	return ;
}
