
// MFC_k2Dlg.h : 標頭檔
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


// CMFC_k2Dlg 對話方塊
class CMFC_k2Dlg : public CDialogEx
{
// 建構
public:
	CMFC_k2Dlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_K2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
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
