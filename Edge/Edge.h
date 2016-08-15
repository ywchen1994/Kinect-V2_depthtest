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
	void CornerDetection(IplImage * edge_roi, IplImage * CornerImg_Modified, int radius);

	CvPoint GetCornerPoint(IplImage * src, IplImage * dst, int radius);
	

	void CornerFind(IplImage * Cornerimage, IplImage * dst, int radius);
	
	CvPoint GetCenterPoint(IplImage * src);
	void SetRoI(IplImage * img_edge);
	void ApproxPoly(IplImage *S_edge);
	int picture_counter = 0;
	int CornerCounter = 0;
	CvPoint *CenterPoint = new CvPoint[30];
	CvPoint *CornerPoint = new CvPoint[15];
	void findinside(IplImage * Img);
	char str[20] = { 0 };
private:
	
};


