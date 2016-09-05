// BottomView.h : CBottomView 类的声明和接口定义
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#if !defined(AFX_BOTTOMVIEW_H__71E48AFF_E3E1_4C80_B69D_8CA5A9D4017D__INCLUDED_)
#define AFX_BOTTOMVIEW_H__71E48AFF_E3E1_4C80_B69D_8CA5A9D4017D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CBottomView 类

class CBottomView : public CFormView
{
protected:
	CBottomView();
	DECLARE_DYNCREATE(CBottomView)

// 编辑框数据
public:
	//{{AFX_DATA(CBottomView)
	enum { IDD = IDD_BOTTOMVIEW };
	CEdit	m_editSoureData;
	//}}AFX_DATA

// 属性
private:
	BOOL m_bInitControl;
// 操作
public:

// 覆盖
	//{{AFX_VIRTUAL(CBottomView)

	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 数据交换
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// 执行/实施
protected:
	virtual ~CBottomView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_MSG(CBottomView)
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditSelectAll();
	afx_msg void OnChangeSourceData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_BOTTOMVIEW_H__71E48AFF_E3E1_4C80_B69D_8CA5A9D4017D__INCLUDED_)
