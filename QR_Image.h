// QR_Image.h : QR_Image Ӧ�õ���Ҫͷ���ļ�
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#if !defined(AFX_QR_IMAGE_H__963AB23C_78F7_45EE_A7C5_B3D029D08C3D__INCLUDED_)
#define AFX_QR_IMAGE_H__963AB23C_78F7_45EE_A7C5_B3D029D08C3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h" // ��Ҫ����

/////////////////////////////////////////////////////////////////////////////
// CQR_ImageApp ��

class CQR_ImageApp : public CWinApp
{
public:
	CQR_ImageApp();

// ����
	//{{AFX_VIRTUAL(CQR_ImageApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

private:
// �ڴ�й©����ã�ֻ����ʱ��
#ifdef _DEBUG
	CMemoryState mStart, mEnd, mDiff;
#endif //_DEBUG

// ����״̬
public:
	//{{AFX_MSG(CQR_ImageApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_QR_IMAGE_H__963AB23C_78F7_45EE_A7C5_B3D029D08C3D__INCLUDED_)
