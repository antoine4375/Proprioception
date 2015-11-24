
// PhantomBigDlg.h : 헤더 파일
//

#pragma once

#include "afxcmn.h"
#include <cstdlib>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include "LogerMsg.h"

#include "afxwin.h"
#include "spline.h"


// CPhantomBigDlg 대화 상자
class CPhantomBigDlg : public CDialogEx
{
// 생성입니다.
public:
	CPhantomBigDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PHANTOMBIG_DIALOG };

	boost::thread View_thread;
	boost::thread Phantom_thread;
	LogerMsg log_data;

	void View_routine(void);
	void LogData();

	double prevx,prevy;
	double cx,cy;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPhantomBnt();
	afx_msg void OnBnClickedViewBnt();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton1();
};
