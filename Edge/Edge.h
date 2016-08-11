#pragma once
#include"cv.h"
#include<highgui.h> 
using namespace cv;
class Edge
{
public:
	Edge();
	~Edge();
	/*void  Sobel(IplImage* Img, IplImage* edge);
	
	IplImage *pSobelImg_8U = NULL;
	IplImage *pGrayImg = NULL;*/
	void Canny(IplImage* Img, IplImage* edge,int min,int max);
    void  Edgemodify(IplImage *edge);
	void CornerDetection(IplImage * edge_roi);
	CvPoint GetCenterPoint(IplImage * src);
	void SetRoI(IplImage * img_edge);
	void ApproxPoly(IplImage *S_edge);
	int picture_counter = 0;
	
	CvPoint *CenterPoint = new CvPoint[100];

	void findinside(IplImage * Img);
	char str[20] = { 0 };

};


