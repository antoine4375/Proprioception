
// PhantomBigDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "PhantomBig.h"
#include "PhantomBigDlg.h"
#include "afxdialogex.h"
#include "Phantom.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPhantomBigDlg 대화 상자




CPhantomBigDlg::CPhantomBigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPhantomBigDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhantomBigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPhantomBigDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PHANTOM_BNT, &CPhantomBigDlg::OnBnClickedPhantomBnt)
	ON_BN_CLICKED(IDC_VIEW_BNT, &CPhantomBigDlg::OnBnClickedViewBnt)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CPhantomBigDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPhantomBigDlg 메시지 처리기

BOOL CPhantomBigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPhantomBigDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPhantomBigDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPhantomBigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPhantomBigDlg::View_routine(void)
{
	int i;
	IplImage *img = 0;
	CvPoint pt1,pt2,center;
	int irandom;
	double theta;
	char buff[100];
	CvFont font;
	
	cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 1, 1);

	img = cvCreateImage (cvSize (1000, 1000), IPL_DEPTH_8U, 3);
	center.x = 500;	center.y = 500;

	double pi = 3.14159265359;
	while(1)
	{
		if (animation_flag)
		{
			pt1.x = 500;	pt1.y = 500;
			srand((unsigned)time(NULL));
			while(1)
			{
				theta = (rand() % 360)*pi/360;
				cx = prevx + 400*cos(theta);		cy = prevy + 400*sin(theta);
				if (sqrt(cx*cx + cy*cy) <= 400)
				{
					break;
				}
			}

			for (int j = 1; j < 501; ++j)
			{
				std::ostringstream outstream;
				pt2.x = 500+prevx-(prevx-cx)*0.002*j;	pt2.y = 500+prevy-(prevy-cy)*0.002*j;
				outstream << target_count << " ";
				outstream << pt2.x << " "; 
				outstream << 500 - (prevy-(prevy-cy)*0.002*j) << " "; 
				for (int i = 0; i < 3; ++i)	outstream << 500 + mst.position[i]*3 << " "; 
				std::string str = outstream.str();
				log_data.writeLog(str);

				cvZero (img);
				cvCircle(img, pt2, 10, CV_RGB(0,255,0));
				cvCircle(img, center, 10, CV_RGB(0,0,255));

				cvNamedWindow ("Drawing", CV_WINDOW_AUTOSIZE);
				cvShowImage ("Drawing", img);
				cvWaitKey (10);
			}
			center.x = 500+prevx-(prevx-cx);
			center.y = 500+prevy-(prevy-cy);
			prevx = cx; 	prevy = cy;
			animation_flag = false;
		}
		else
		{
			cvZero (img);
			pt2.x = 500 + mst.position[0]*3;	pt2.y = 500 - mst.position[1]*3;

			sprintf(buff, "c:%d",target_count);
			cvPutText(img, buff,cvPoint(100,50),&font, CV_RGB(255,0,0));
			
			cvCircle(img, pt2, 10, CV_RGB(0,255,0));
			cvCircle(img, center, 10, CV_RGB(255,0,0));
			cvNamedWindow ("Drawing", CV_WINDOW_AUTOSIZE);
			cvShowImage ("Drawing", img);
			cvWaitKey (100);
		}
	}
}

void CPhantomBigDlg::OnBnClickedPhantomBnt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Omni_Init();
	Omni_Calibrate();
	Omni_Start();
}


void CPhantomBigDlg::OnBnClickedViewBnt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	View_thread = boost::thread(&CPhantomBigDlg::View_routine,this);
}


void CPhantomBigDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	View_thread.join();
}

void CPhantomBigDlg::LogData()
{
	std::ostringstream outstream;
	outstream << target_count << " ";
	for (int i = 0; i < 3; ++i)	outstream << mst.position[i] << " "; 
	std::string str = outstream.str();
	log_data.writeLog(str);
}

void CPhantomBigDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	positioning_flag = true;
}
