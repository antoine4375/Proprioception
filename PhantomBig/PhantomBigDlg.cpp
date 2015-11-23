
// PhantomBigDlg.cpp : ±¸Çö ÆÄÀÏ
//

#include "stdafx.h"
#include "PhantomBig.h"
#include "PhantomBigDlg.h"
#include "afxdialogex.h"
#include "Phantom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ÀÀ¿ë ÇÁ·Î±×·¥ Á¤º¸¿¡ »ç¿ëµÇ´Â CAboutDlg ´ëÈ­ »óÀÚÀÔ´Ï´Ù.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ´ëÈ­ »óÀÚ µ¥ÀÌÅÍÀÔ´Ï´Ù.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Áö¿øÀÔ´Ï´Ù.

// ±¸ÇöÀÔ´Ï´Ù.
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


// CPhantomBigDlg ´ëÈ­ »óÀÚ




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
END_MESSAGE_MAP()


// CPhantomBigDlg ¸Þ½ÃÁö Ã³¸®±â

BOOL CPhantomBigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ½Ã½ºÅÛ ¸Þ´º¿¡ "Á¤º¸..." ¸Þ´º Ç×¸ñÀ» Ãß°¡ÇÕ´Ï´Ù.

	// IDM_ABOUTBOX´Â ½Ã½ºÅÛ ¸í·É ¹üÀ§¿¡ ÀÖ¾î¾ß ÇÕ´Ï´Ù.
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

	// ÀÌ ´ëÈ­ »óÀÚÀÇ ¾ÆÀÌÄÜÀ» ¼³Á¤ÇÕ´Ï´Ù. ÀÀ¿ë ÇÁ·Î±×·¥ÀÇ ÁÖ Ã¢ÀÌ ´ëÈ­ »óÀÚ°¡ ¾Æ´Ò °æ¿ì¿¡´Â
	//  ÇÁ·¹ÀÓ¿öÅ©°¡ ÀÌ ÀÛ¾÷À» ÀÚµ¿À¸·Î ¼öÇàÇÕ´Ï´Ù.
	SetIcon(m_hIcon, TRUE);			// Å« ¾ÆÀÌÄÜÀ» ¼³Á¤ÇÕ´Ï´Ù.
	SetIcon(m_hIcon, FALSE);		// ÀÛÀº ¾ÆÀÌÄÜÀ» ¼³Á¤ÇÕ´Ï´Ù.

	// TODO: ¿©±â¿¡ Ãß°¡ ÃÊ±âÈ­ ÀÛ¾÷À» Ãß°¡ÇÕ´Ï´Ù.

	return TRUE;  // Æ÷Ä¿½º¸¦ ÄÁÆ®·Ñ¿¡ ¼³Á¤ÇÏÁö ¾ÊÀ¸¸é TRUE¸¦ ¹ÝÈ¯ÇÕ´Ï´Ù.
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

// ´ëÈ­ »óÀÚ¿¡ ÃÖ¼ÒÈ­ ´ÜÃß¸¦ Ãß°¡ÇÒ °æ¿ì ¾ÆÀÌÄÜÀ» ±×¸®·Á¸é
//  ¾Æ·¡ ÄÚµå°¡ ÇÊ¿äÇÕ´Ï´Ù. ¹®¼­/ºä ¸ðµ¨À» »ç¿ëÇÏ´Â MFC ÀÀ¿ë ÇÁ·Î±×·¥ÀÇ °æ¿ì¿¡´Â
//  ÇÁ·¹ÀÓ¿öÅ©¿¡¼­ ÀÌ ÀÛ¾÷À» ÀÚµ¿À¸·Î ¼öÇàÇÕ´Ï´Ù.

void CPhantomBigDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ±×¸®±â¸¦ À§ÇÑ µð¹ÙÀÌ½º ÄÁÅØ½ºÆ®ÀÔ´Ï´Ù.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Å¬¶óÀÌ¾ðÆ® »ç°¢Çü¿¡¼­ ¾ÆÀÌÄÜÀ» °¡¿îµ¥¿¡ ¸ÂÃä´Ï´Ù.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ¾ÆÀÌÄÜÀ» ±×¸³´Ï´Ù.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// »ç¿ëÀÚ°¡ ÃÖ¼ÒÈ­µÈ Ã¢À» ²ô´Â µ¿¾È¿¡ Ä¿¼­°¡ Ç¥½ÃµÇµµ·Ï ½Ã½ºÅÛ¿¡¼­
//  ÀÌ ÇÔ¼ö¸¦ È£ÃâÇÕ´Ï´Ù.
HCURSOR CPhantomBigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPhantomBigDlg::View_routine(void)
{
	int i;
	IplImage *img = 0;
	CvPoint pt1,pt2,center;
	double theta;

	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 1, 1);
	char buff[200];

	img = cvCreateImage (cvSize (1000, 1000), IPL_DEPTH_8U, 3);
	center.x = 500;	center.y = 500;

	double pi = 3.14159265359;
	while(1)
	{
		switch(target_count)
		{
			case 8:	theta = 0;					break; 	// 0 deg
			case 4:	theta = 0.7853981633974483;	break;	// 45 deg
			case 7:	theta = 1.570796326794897; 	break; 	// 90 deg
			case 2:	theta =	2.356194490192345;	break; 	// 135 deg
			case 6:	theta = 3.141592653589793;	break; 	// 180 deg
			case 1:	theta = 3.926990816987241;	break; 	// 225 deg
			case 5:	theta =	4.71238898038469;	break; 	// 270 deg
			case 3:	theta = 5.497787143782138;	break; 	// 315 deg
			default:
			break;
		}
		if (target_count < 1)
		{
			pt1.x = 500;		pt1.y = 500;
		}
		else
		{
			pt1.x = 500+400*cos(theta);		pt1.y = 500+400*sin(theta);
		}

		cvZero (img);
		cvCircle(img, pt1, 10, CV_RGB(0,255,0));
		cvCircle(img, center, 10, CV_RGB(255,0,0));

		if (!first_bnt)
		{
			sprintf(buff, "x:%f",mst.position[0]);
			cvPutText(img, buff,cvPoint(700,50),&font, CV_RGB(255,0,0));
			sprintf(buff, "y:%f",mst.position[1]);
			cvPutText(img, buff,cvPoint(700,100),&font, CV_RGB(255,0,0));
			sprintf(buff, "z:%f",mst.position[2]);
			cvPutText(img, buff,cvPoint(700,150),&font, CV_RGB(255,0,0));
		}

		sprintf(buff, "%d",routine_count);
		cvPutText(img, buff,cvPoint(100,50),&font, CV_RGB(255,0,0));

		cvNamedWindow ("Drawing", CV_WINDOW_AUTOSIZE);
		cvShowImage ("Drawing", img);
		cvWaitKey (100);
		
	}
}

void CPhantomBigDlg::OnBnClickedPhantomBnt()
{
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	Omni_Init();
	Omni_Calibrate();
	Omni_Start();
}


void CPhantomBigDlg::OnBnClickedViewBnt()
{
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	View_thread = boost::thread(&CPhantomBigDlg::View_routine,this);
}


void CPhantomBigDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ¿©±â¿¡ ¸Þ½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	View_thread.join();
}

// void CPhantomBigDlg::LogData()
// {
// 	std::ostringstream outstream;
// 	outstream << target_count << " ";
// 	for (int i = 0; i < 3; ++i)	outstream << mst.position[i] << " "; 
// 	std::string str = outstream.str();
// 	log_data.writeLog(str);
// }