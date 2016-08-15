
// MFC_k2Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MFC_k2.h"
#include "MFC_k2Dlg.h"
#include "afxdialogex.h"
#include "math.h"
IplImage* CMFC_k2Dlg::img_rgb = nullptr;
IplImage* CMFC_k2Dlg::img_depth = nullptr;
IplImage* CMFC_k2Dlg::img_edge = nullptr;

bool CMFC_k2Dlg::saveImg = false;
bool CMFC_k2Dlg::I2C = false;
bool CMFC_k2Dlg::edgeImgSuccessed = false;
//char CMFC_k2Dlg::edgepath=
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

int CMFC_k2Dlg::s_cannyMax = 15;
int CMFC_k2Dlg::s_cannyMin = 10;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_k2Dlg 對話方塊



CMFC_k2Dlg::CMFC_k2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_K2_DIALOG, pParent)
	, m_cannyMin(0)
	, m_cannyMax(0)
	, m_ImgX(0)
	, m_CamX(0)
	, m_CamY(0)
	, m_CamZ(0)
	, m_ImgY(0)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_k2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE_RGB, m_img_RGB);
	DDX_Control(pDX, IDC_IMAGE_Depth, m_img_Depth);
	DDX_Control(pDX, IDC_img_test, m_img_test);

	DDX_Text(pDX, IDC_EDIT_cannyMin, m_cannyMin);
	DDX_Text(pDX, IDC_EDIT_cannyMax, m_cannyMax);

	DDX_Text(pDX, IDC_EDIT_ImgX, m_ImgX);
	DDX_Text(pDX, IDC_EDIT_ImgY, m_ImgY);
	DDX_Text(pDX, IDC_EDIT_CamX, m_CamX);
	DDX_Text(pDX, IDC_EDIT_CamY, m_CamY);
	DDX_Text(pDX, IDC_EDIT_CamZ, m_CamZ);
	DDX_Control(pDX, IDC_IMAGE_Corner, m_Img_Corner);
	DDX_Control(pDX, IDC_IMAGE_Selected, m_Img_Selected);
}

BEGIN_MESSAGE_MAP(CMFC_k2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RGB, &CMFC_k2Dlg::OnBnClickedButtonRgb)
	ON_BN_CLICKED(IDC_BUTTON_Depth, &CMFC_k2Dlg::OnBnClickedButtonDepth)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC_k2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_SaveImg, &CMFC_k2Dlg::OnBnClickedButtonSaveimg)
	
	ON_BN_CLICKED(IDC_BUTTON_canny, &CMFC_k2Dlg::OnBnClickedButtoncanny)
	ON_BN_CLICKED(IDC_BUTTON_CloseKomect, &CMFC_k2Dlg::OnBnClickedButtonClosekomect)
	ON_BN_CLICKED(IDC_BUTTON_Img2Cam, &CMFC_k2Dlg::OnBnClickedButtonImg2cam)
	
	ON_BN_CLICKED(IDC_BUTTON_CornerImg, &CMFC_k2Dlg::OnBnClickedButtonCornerimg)
	ON_BN_CLICKED(IDC_BUTTON_ImgSelect, &CMFC_k2Dlg::OnBnClickedButtonImgselect)
END_MESSAGE_MAP()


// CMFC_k2Dlg 訊息處理常式

BOOL CMFC_k2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	
	
	m_img_RGB.SetWindowPos(NULL, 10, 10, 320, 240, SWP_SHOWWINDOW);;
	m_img_Depth.SetWindowPos(NULL, 10 + 320, 10, 320, 240, SWP_SHOWWINDOW);
	m_img_test.SetWindowPos(NULL, 10, 10+240, 320, 240, SWP_SHOWWINDOW);
    m_Img_Corner.SetWindowPos(NULL, 10 + 320, 10 + 240, 320, 240, SWP_SHOWWINDOW);
	m_Img_Selected.SetWindowPos(NULL, 10 + 320+320, 10 , 320, 240, SWP_SHOWWINDOW);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFC_k2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFC_k2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFC_k2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_k2Dlg::OnBnClickedButtonRgb()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_threadPara.m_case = 0;
	m_threadPara.hWnd = m_hWnd;
	m_lpThread = AfxBeginThread(&CMFC_k2Dlg::MythreadFun, (LPVOID)&m_threadPara);
}
void CMFC_k2Dlg::ShowImage(IplImage * Image, CWnd * pWnd, int channels)
{
	CDC	*dc = pWnd->GetWindowDC();
	IplImage *Temp = NULL;
	if (channels != 4) {
		Temp = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, channels);
		cvResize(Image, Temp, CV_INTER_LINEAR);
	}
	if (channels == 4)
	{
		Temp = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
		IplImage *Temp_transfer = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 4);
		cvResize(Image, Temp_transfer, CV_INTER_LINEAR);
		cvCvtColor(Temp_transfer, Temp, CV_BGRA2BGR);
		cvReleaseImage(&Temp_transfer);
	}

	CvvImage Temp2;
	Temp2.CopyOf(Temp);
	Temp2.Show(*dc, 0, 0, Temp->width, Temp->height);
	cvReleaseImage(&Temp);
	ReleaseDC(dc);
}
void CMFC_k2Dlg::Thread_Image_RGB(LPVOID lParam)
{
	CMythreadParam * Thread_Info = (CMythreadParam *)lParam;
	CMFC_k2Dlg * hWnd = (CMFC_k2Dlg *)CWnd::FromHandle((HWND)Thread_Info->hWnd);
	Kinect2Capture kinect;
	Edge edgefind;
	kinect.Open(1, 1, 1);

	while (1)
	{
		
		img_rgb = kinect.RGBAImage();
		if (img_rgb != NULL) {
	IplImage* ImgRGB3 = cvCreateImage(cvGetSize(img_rgb), img_rgb->depth,3);
	cvCvtColor(img_rgb, ImgRGB3,CV_BGRA2BGR);
			hWnd->ShowImage(img_rgb, hWnd->GetDlgItem(IDC_IMAGE_RGB), 4);
			if (saveImg) {
				cvSaveImage("E:\\rgb.jpg", img_rgb);
				saveImg = false;
			}
			cvReleaseImage(&img_rgb);
			cvReleaseImage(&ImgRGB3);
		}
	}

}
UINT CMFC_k2Dlg::MythreadFun(LPVOID LParam)
{
	CMythreadParam* para = (CMythreadParam*)LParam;
	CMFC_k2Dlg* lpview = (CMFC_k2Dlg*)(para->m_lpPara);
	para->m_blthreading = TRUE;

	switch (para->m_case)
	{
	case 0:
		lpview->Thread_Image_RGB(LParam);
		break;
	case 1:
		lpview->Thread_Image_Depth(LParam);
	case 2:
		lpview->Thread_Image_test(LParam);
	default:
		break;
	}

	para->m_blthreading = FALSE;
	para->m_case = 0xFF;
	return 0;

}
void CMFC_k2Dlg::Thread_Image_Depth(LPVOID lParam)
{
	CMythreadParam * Thread_Info = (CMythreadParam *)lParam;
	CMFC_k2Dlg * hWnd = (CMFC_k2Dlg *)CWnd::FromHandle((HWND)Thread_Info->hWnd);
	Kinect2Capture kinect;
	Edge edge;

	kinect.Open(1, 1, 1);
	while (1)
	{
		img_depth = kinect.DepthImage();
		if (img_depth != NULL)
		{
			hWnd->ShowImage(img_depth, hWnd->GetDlgItem(IDC_IMAGE_Depth), 1);
			if (saveImg) {
				cvSaveImage("E:\\depthBG.jpg", img_depth);
				saveImg = false;
			}
		}
		
		cvReleaseImage(&img_depth);
	
	
	}

}
void CMFC_k2Dlg::OnBnClickedButtonDepth()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_threadPara.m_case = 1;
	m_threadPara.hWnd = m_hWnd;
	m_lpThread = AfxBeginThread(&CMFC_k2Dlg::MythreadFun, (LPVOID)&m_threadPara);
}


void CMFC_k2Dlg::OnBnClickedButton3()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_threadPara.m_case = 2;
	m_threadPara.hWnd = m_hWnd;
	m_lpThread = AfxBeginThread(&CMFC_k2Dlg::MythreadFun, (LPVOID)&m_threadPara);
}
void CMFC_k2Dlg::Thread_Image_test(LPVOID lParam)
{
	CMythreadParam * Thread_Info = (CMythreadParam *)lParam;
	CMFC_k2Dlg * hWnd = (CMFC_k2Dlg *)CWnd::FromHandle((HWND)Thread_Info->hWnd);
	Kinect2Capture kinect;
	Edge edgefind;
	kinect.Open(1, 1, 1);
	while (1)
	{
		img_depth = kinect.DepthImage();
		if (img_depth != NULL) {
		  img_edge = cvCreateImage(cvGetSize(img_depth), img_depth->depth,1);
		  
		   edgefind.Canny(img_depth, img_edge,s_cannyMin, s_cannyMax);
		   
		   
			hWnd->ShowImage(img_edge, hWnd->GetDlgItem(IDC_img_test), 1);
			hWnd->ShowImage(img_depth, hWnd->GetDlgItem(IDC_IMAGE_Depth),1);
			if (saveImg) {
			
				cvSaveImage("E:\\img_edge.jpg", img_edge);
				edgeImgSuccessed = true;
				saveImg = false;
			}
			if (I2C){
				CString str;

				hWnd->GetDlgItem(IDC_EDIT_ImgX)->GetWindowText(str);
				int x1 = _ttoi(str);
				hWnd->GetDlgItem(IDC_EDIT_ImgY)->GetWindowText(str);
				int y1 = _ttoi(str);
		     	kinect.Depth2CameraSpace(x1, y1);
			

					str.Format(_T("%.4f"), kinect.CameraX * 1000);
					hWnd->GetDlgItem(IDC_EDIT_CamX)->SetWindowText(str);
					str.Format(_T("%.4f"), kinect.CameraY * 1000);
					hWnd->GetDlgItem(IDC_EDIT_CamY)->SetWindowText(str);
					str.Format(_T("%.4f"), kinect.CameraZ * 1000);
					hWnd->GetDlgItem(IDC_EDIT_CamZ)->SetWindowText(str);

					float SCARACommamndX =132.2821+295- kinect.CameraY * 1000;//Cam.Y+SCA.X
					str.Format(_T("%.4f"), SCARACommamndX);
					hWnd->GetDlgItem(IDC_EDIT_SCARACommandX)->SetWindowText(str);

					float SCARACommamndY = 166.3964+404 - kinect.CameraX * 1000;//Cam.X+SCA.Y
					str.Format(_T("%.4f"), SCARACommamndY);
					hWnd->GetDlgItem(IDC_EDIT_SCARACommandY)->SetWindowText(str);

					if (sqrt(pow(SCARACommamndX, 2) + pow(SCARACommamndY, 2)) > 550)
					MessageBox(_T("手臂過短"));

					float SCARACommamndZ = kinect.CameraZ * 1000 - 560;
					if (SCARACommamndZ - 200 < 2 &&  SCARACommamndZ-200>0)
						SCARACommamndZ = 200;
					str.Format(_T("%.4f"), SCARACommamndZ);
					hWnd->GetDlgItem(IDC_EDIT_SCARACommandZ)->SetWindowText(str);
					I2C = false;
					
			}
			cvReleaseImage(&img_depth);
			cvReleaseImage(&img_edge);
		}
		
	}
}

void CMFC_k2Dlg::OnBnClickedButtonSaveimg()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	saveImg = true;
}



void CMFC_k2Dlg::OnBnClickedButtoncanny()
{
	UpdateData(true);
	s_cannyMax = m_cannyMax;
	s_cannyMin = m_cannyMin;

}


void CMFC_k2Dlg::OnBnClickedButtonClosekomect()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	Kinect2Capture kinect;
	kinect.Close();
}


void CMFC_k2Dlg::OnBnClickedButtonImg2cam()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	I2C = true;
}





void CMFC_k2Dlg::OnBnClickedButtonCornerimg()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	Edge edgefind;
	CString str;
	if (edgeImgSuccessed) {
		IplImage*img_edgeload = cvLoadImage("E:\\img_edge.jpg", 0);

		IplImage* CornerImg_Modified = cvCreateImage(cvGetSize(img_edgeload), img_edgeload->depth, 3);
		cvSetZero(CornerImg_Modified);

		edgefind.CornerDetection(img_edgeload, CornerImg_Modified,2);//角點的半徑2

		IplImage* CornerImg_ModifiedC1 = cvCreateImage(cvGetSize(img_edgeload), img_edgeload->depth, 1);
		cvCvtColor(CornerImg_Modified, CornerImg_ModifiedC1, CV_RGB2GRAY);
	
		edgefind.ApproxPoly(img_edgeload);
		IplImage *ApproxPolyImg = cvCreateImage(cvGetSize(img_edgeload), img_edgeload->depth, 1);
		if (imageSelect){

			char ApproxPolyImgpath[20] = { 0 };
			GetDlgItem(IDC_EDIT_ApproxPolyImgNo)->GetWindowText(str);
			int picture_counter = _ttoi(str);
			sprintf_s(ApproxPolyImgpath, "./inside%d.jpg", picture_counter);
			ApproxPolyImg = cvLoadImage(ApproxPolyImgpath, 0);
			cvSaveImage("./Corner.jpg", CornerImg_ModifiedC1);
			cvAnd(CornerImg_ModifiedC1, ApproxPolyImg, CornerImg_ModifiedC1);
			cvReleaseImage(&ApproxPolyImg);
			cvSetZero(CornerImg_Modified);
			edgefind.CornerFind(CornerImg_ModifiedC1, CornerImg_Modified,0);
			if (edgefind.CornerCounter == 3)
			{
				CvPoint CornerNo1 = edgefind.CornerPoint[0];
				CvPoint CornerNo2 = edgefind.CornerPoint[1];
				CvPoint CornerNo3 = edgefind.CornerPoint[2];
				CvPoint CornerNo4 = edgefind.CornerPoint[4];
			
			}

			cvCvtColor(CornerImg_Modified, CornerImg_ModifiedC1, CV_RGB2GRAY);
			cvReleaseImage(&CornerImg_Modified);
			ShowImage(CornerImg_ModifiedC1, GetDlgItem(IDC_IMAGE_Corner),1);
			imageSelect = false;
	}
		
		cvReleaseImage(&CornerImg_ModifiedC1);
		
	}
}


void CMFC_k2Dlg::OnBnClickedButtonImgselect()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	imageSelect = true;
	CString str;
	char ApproxPolyImgpath[20] = { 0 };
	GetDlgItem(IDC_EDIT_ApproxPolyImgNo)->GetWindowText(str);
	int picture_counter = _ttoi(str);
	sprintf_s(ApproxPolyImgpath, "./inside%d.jpg", picture_counter);

	IplImage*ApproxPolyImg = cvLoadImage(ApproxPolyImgpath, 0);
	ShowImage(ApproxPolyImg, GetDlgItem(IDC_IMAGE_Selected), 1);
	cvReleaseImage(&ApproxPolyImg);
	

}
