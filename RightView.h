// RightView.h : CRightView 类声明和接口定义
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#if !defined(AFX_RIGHTVIEW_H__F346E2CF_81BB_46DF_9F23_8351B7F80F49__INCLUDED_)
#define AFX_RIGHTVIEW_H__F346E2CF_81BB_46DF_9F23_8351B7F80F49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "QRData.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CRightView 类
class CRightView : public CFormView
{
protected:
	CRightView();
	DECLARE_DYNCREATE(CRightView)

// 表格数据
public:
	//{{AFX_DATA(CRightView)
	enum { IDD = IDD_RIGHTVIEW };
	CComboBox m_comboLevel;
	CComboBox m_comboVersion;
	CStatic m_staticVersion;
	CButton m_checkAutoExtent;
	CComboBox m_comboMaskingNo;
	CStatic m_staticMaskingNo;
	CEdit m_editModuleSize;
	CSpinButtonCtrl m_spinModuleSize;
	CStatic m_staticBmpSize;
	CButton	m_buttonCopy;
	CButton	m_buttonSave;
	//}}AFX_DATA

// 属性、表征
private:
	BOOL m_bInitControl;

// 操作
public:

// 覆盖
	//{{AFX_VIRTUAL(CRightView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// 待机状态
protected:
	virtual ~CRightView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_MSG(CRightView)
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditSelectAll();
	afx_msg void OnSelChangeLevel();
	afx_msg void OnSelChangeVersion();
	afx_msg void OnAutoExtent();
	afx_msg void OnSelChangeMaskNo();
	afx_msg void OnChangeDrawSize();
	afx_msg void OnKillFocusDrawSize();
	afx_msg void OnCopy();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_RIGHTVIEW_H__F346E2CF_81BB_46DF_9F23_8351B7F80F49__INCLUDED_)

