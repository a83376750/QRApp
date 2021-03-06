// BottomView.cpp : CBottomView 类的实现文件
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#include "stdafx.h"
#include "QR_Image.h"
#include "MainFrm.h"
#include "BottomView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBottomView

IMPLEMENT_DYNCREATE(CBottomView, CFormView)

CBottomView::CBottomView()
	: CFormView(CBottomView::IDD)
{
	//{{AFX_DATA_INIT(CBottomView)
	//}}AFX_DATA_INIT

	m_bInitControl = FALSE;
}

CBottomView::~CBottomView()
{
}

void CBottomView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBottomView)
	DDX_Control(pDX, IDC_EDITSOURCEDATA, m_editSoureData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBottomView, CFormView)
	//{{AFX_MSG_MAP(CBottomView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_EN_CHANGE(IDC_EDITSOURCEDATA, OnChangeSourceData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBottomView 诊断

#ifdef _DEBUG
void CBottomView::AssertValid() const
{
	CFormView::AssertValid();
}

void CBottomView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CBottomView 消息处理程序

void CBottomView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (! m_bInitControl)
	{
		m_editSoureData.SetWindowText("");
		m_bInitControl = TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// 菜单项更新

void CBottomView::OnUpdateEditUndo(CCmdUI* pCmdUI)//保存
{
	pCmdUI->Enable(m_editSoureData.CanUndo());
}

void CBottomView::OnUpdateEditCut(CCmdUI* pCmdUI)//剪切
{
	int nStartChar, nEndChar;

	m_editSoureData.GetSel(nStartChar, nEndChar);

	pCmdUI->Enable(nStartChar != nEndChar);
}

void CBottomView::OnUpdateEditCopy(CCmdUI* pCmdUI)//复制
{
	int nStartChar, nEndChar;

	m_editSoureData.GetSel(nStartChar, nEndChar);

	pCmdUI->Enable(nStartChar != nEndChar);
}

void CBottomView::OnUpdateEditPaste(CCmdUI* pCmdUI)//黏贴
{
	pCmdUI->Enable(IsClipboardFormatAvailable(CF_TEXT));
}


/////////////////////////////////////////////////////////////////////////////
// 运行菜单

void CBottomView::OnEditUndo() {m_editSoureData.Undo();}
void CBottomView::OnEditCut() {m_editSoureData.Cut();}
void CBottomView::OnEditCopy() {m_editSoureData.Copy();}
void CBottomView::OnEditPaste() {m_editSoureData.Paste();}
void CBottomView::OnEditSelectAll() {m_editSoureData.SetSel(0, -1);}


/////////////////////////////////////////////////////////////////////////////
// 输入后更新处理

void CBottomView::OnChangeSourceData()
{
	if (m_bInitControl)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowImage();
}
