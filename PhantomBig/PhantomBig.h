
// PhantomBig.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CPhantomBigApp:
// �� Ŭ������ ������ ���ؼ��� PhantomBig.cpp�� �����Ͻʽÿ�.
//

class CPhantomBigApp : public CWinApp
{
public:
	CPhantomBigApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPhantomBigApp theApp;