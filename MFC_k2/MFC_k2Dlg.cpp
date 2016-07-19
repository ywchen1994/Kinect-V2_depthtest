
// MFC_k2Dlg.cpp : ��@��
//

#include "stdafx.h"
#include "MFC_k2.h"
#include "MFC_k2Dlg.h"
#include "afxdialogex.h"
IplImage* CMFC_k2Dlg::img_rgb = nullptr;
IplImage* CMFC_k2Dlg::img_depth = nullptr;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
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


// CMFC_k2Dlg ��ܤ��



CMFC_k2Dlg::CMFC_k2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_K2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_k2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE_RGB, m_img_RGB);
	DDX_Control(pDX, IDC_IMAGE_Depth, m_img_Depth);
}

BEGIN_MESSAGE_MAP(CMFC_k2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RGB, &CMFC_k2Dlg::OnBnClickedButtonRgb)
	ON_BN_CLICKED(IDC_BUTTON_Depth, &CMFC_k2Dlg::OnBnClickedButtonDepth)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC_k2Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFC_k2Dlg �T���B�z�`��

BOOL CMFC_k2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
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

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w
	m_img_RGB.SetWindowPos(NULL, 10, 10, 320, 240, SWP_SHOWWINDOW);;
	m_img_Depth.SetWindowPos(NULL, 10 + 320, 10, 320, 240, SWP_SHOWWINDOW);
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
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

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CMFC_k2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CMFC_k2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_k2Dlg::OnBnClickedButtonRgb()
{
	// TODO: �b���[�J����i���B�z�`���{���X
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
	IplImage *rgb_show = nullptr;
	Kinect2Capture kinect;
	kinect.Open(1, 1, 1);


	while (1)
	{
		img_rgb = kinect.RGBAImage();
		if (img_rgb != NULL) {
			hWnd->ShowImage(img_rgb, hWnd->GetDlgItem(IDC_IMAGE_RGB), 4);
			cvReleaseImage(&img_rgb);
		}
	}

}UINT CMFC_k2Dlg::MythreadFun(LPVOID LParam)
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
	kinect.Open(1, 1, 1);
	while (1)
	{
		img_depth = kinect.DepthImage();
		if (img_depth != NULL)
			hWnd->ShowImage(img_depth, hWnd->GetDlgItem(IDC_IMAGE_Depth), 1);
		cvReleaseImage(&img_depth);
	}

}
void CMFC_k2Dlg::OnBnClickedButtonDepth()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	m_threadPara.m_case = 1;
	m_threadPara.hWnd = m_hWnd;
	m_lpThread = AfxBeginThread(&CMFC_k2Dlg::MythreadFun, (LPVOID)&m_threadPara);
}


void CMFC_k2Dlg::OnBnClickedButton3()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	Kinect2Capture kinect;
	
}
