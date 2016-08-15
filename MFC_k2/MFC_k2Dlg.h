
// MFC_k2Dlg.h : ���Y��
//
#include "afxwin.h"
#include"Kinect.h"
#include"..//Kinect2Capture//Kinect2Capture.h"
#include"..//Edge/Edge.h"
#include "opencv.hpp"
#include <iostream>
#include <stdio.h>
#include"Cvvimage.h"
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
struct CMythreadParam
{
public:
	HWND hWnd;
	LPVOID m_lpPara;
	UINT   m_case;
	BOOL m_blthreading;
};


// CMFC_k2Dlg ��ܤ��
class CMFC_k2Dlg : public CDialogEx
{
// �غc
public:
	CMFC_k2Dlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_K2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	static UINT MythreadFun(LPVOID LParam);
	void Thread_Image_Depth(LPVOID lParam);
	void Thread_Image_RGB(LPVOID lParam);
	CMythreadParam m_threadPara;
	CWinThread*  m_lpThread;
	CStatic m_img_RGB;
	CStatic m_img_Depth;
	afx_msg void OnBnClickedButtonRgb();
	void ShowImage(IplImage * Image, CWnd * pWnd, int channels);
	static IplImage *img_rgb;
	static IplImage* img_depth;
	afx_msg void OnBnClickedButtonDepth();
	afx_msg void OnBnClickedButton3();
	void Thread_Image_test(LPVOID lParam);
	CStatic m_img_test;
	static IplImage *img_edge ;
	afx_msg void OnBnClickedButtonSaveimg();
	static bool saveImg;

	
	int m_cannyMin;
	int m_cannyMax;
	static int s_cannyMin;
	static int s_cannyMax;
	afx_msg void OnBnClickedButtoncanny();
	static char edgepath[10];
	static char depthpath[10];
	int picnum = 0;
	afx_msg void OnBnClickedButtonClosekomect();
	afx_msg void OnBnClickedButtonImg2cam();


	int m_ImgX;
	int m_ImgY;
	static bool I2C;
	float m_CamX;
	float m_CamY;
	float m_CamZ;


	afx_msg void OnBnClickedButtonCornerimg();
	CStatic m_Img_Corner;
	static bool edgeImgSuccessed;
	afx_msg void OnBnClickedButtonImgselect();
	bool imageSelect=false;
	CStatic m_Img_Selected;
};
