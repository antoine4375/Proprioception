
// PhantomBigDlg.h : ��� ����
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


// CPhantomBigDlg ��ȭ ����
class CPhantomBigDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CPhantomBigDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PHANTOMBIG_DIALOG };

	boost::thread View_thread;
	boost::thread Phantom_thread;
	LogerMsg log_data;

	void View_routine(void);
	void LogData();

	double prevx,prevy;
	double cx,cy;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
