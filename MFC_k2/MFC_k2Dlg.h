
// MFC_k2Dlg.h : ���Y��
//
#include "afxwin.h"
#include"Kinect.h"
#include"..//Kinect2Capture//Kinect2Capture.h"
#include "opencv.hpp"
#include <iostream>
#include <stdio.h>
#include"Cvvimage.h"
#pragma once
#include "afxwin.h"
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
};
