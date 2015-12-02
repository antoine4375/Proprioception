
// PhantomBigDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CPhantomBigDlg ��ȭ ����




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


// CPhantomBigDlg �޽��� ó����

BOOL CPhantomBigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	prevx = 0;
	prevy = 0;
	cx=0;
	cy=0;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CPhantomBigDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
	double temp;
	while(1)
	{
		if (animation_flag)
		{
			pt1.x = 500;	pt1.y = 500;

			srand((unsigned)time(NULL));
			while(1)
			{
				irandom = rand() % 16 + 1;
				switch(irandom)
				{
					case 1:	theta = 0;					break; 	// 0 deg
					case 2:	theta = 0.7853981633974483;	break;	// 45 deg
					case 3:	theta = 1.570796326794897; 	break; 	// 90 deg
					case 4:	theta =	2.356194490192345;	break; 	// 135 deg
					case 5:	theta = 3.141592653589793;	break; 	// 180 deg
					case 6:	theta = 3.926990816987241;	break; 	// 225 deg
					case 7:	theta =	4.71238898038469;	break; 	// 270 deg
					case 8:	theta = 5.497787143782138;	break; 	// 315 deg
					case 9: theta = 22.5*pi/180;		break;
					case 10: theta = 67.5*pi/180;		break;
					case 11: theta = 112.5*pi/180;		break;
					case 12: theta = 157.5*pi/180;		break;
					case 13: theta = 202.5*pi/180;		break;
					case 14: theta = 247.5*pi/180;		break;
					case 15: theta = 292.5*pi/180;		break;
					case 16: theta = 337.5*pi/180;		break;
					default:
					break;
				}

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
			pt2.x = 500 + mst.position[0]*2.5;	pt2.y = 500 - mst.position[1]*2.5;

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Omni_Init();
	Omni_Calibrate();
	Omni_Start();
}


void CPhantomBigDlg::OnBnClickedViewBnt()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	View_thread = boost::thread(&CPhantomBigDlg::View_routine,this);
}


void CPhantomBigDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	positioning_flag = true;
}
