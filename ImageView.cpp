// ImageView.cpp : CImageView 类的执行文件
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#include "stdafx.h"
#include "QR_Image.h"
#include "MainFrm.h"
#include "ImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageView

IMPLEMENT_DYNCREATE(CImageView, CView)

CImageView::CImageView()
{
}

CImageView::~CImageView()
{
}


BEGIN_MESSAGE_MAP(CImageView, CView)
	//{{AFX_MSG_MAP(CImageView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_ERASEBKGND()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageView 绘图

void CImageView::OnDraw(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);

	if (pMainFrame->m_bDataEncoded)
	{
		int nSrcSize = pMainFrame->m_nSymbleSize;
		int nDstSize = min(rcClient.Width(), rcClient.Height());

		// 从内存中快速的显示在屏幕上？？
		CDC* pWorkDC = new CDC;
		pWorkDC->CreateCompatibleDC(NULL);

		CBitmap* pWorkBitmap = new CBitmap;
		pWorkBitmap->CreateBitmap(nDstSize, nDstSize, 1, 1, NULL);

		CBitmap* pOldBitmap = pWorkDC->SelectObject(pWorkBitmap);
		pWorkDC->StretchBlt(0, 0, nDstSize, nDstSize, pMainFrame->m_pSymbleDC, 0, 0, nSrcSize, nSrcSize, SRCCOPY);

		pDC->BitBlt(0, 0, nDstSize, nDstSize, pWorkDC, 0, 0, SRCCOPY);

		pWorkDC->SelectObject(pOldBitmap);
		delete pWorkBitmap;
		delete pWorkDC;
	}
	else
	{
		pDC->FillSolidRect(&rcClient, RGB(255, 255, 255));
	}

}

BOOL CImageView::OnEraseBkgnd(CDC* pDC) 
{
	CRect rcClient;
	GetClientRect(&rcClient);
// 显示区域以外填充白色??
	if (rcClient.Width() != rcClient.Height())
	{
		if (rcClient.Width() > rcClient.Height())
			rcClient.left += rcClient.Height();
		else
			rcClient.top += rcClient.Width();

		pDC->FillSolidRect(&rcClient, RGB(255, 255, 255));
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CImageView 诊断

#ifdef _DEBUG
void CImageView::AssertValid() const
{
	CView::AssertValid();
}

void CImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CImageView 消息处理程序

/////////////////////////////////////////////////////////////////////////////
// 有鼠标单击右键弹出菜单 的显示

void CImageView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu Menu;

	// 菜单(资源)加载
	Menu.LoadMenu(IDR_IMAGEMENU);

	// 子（弹出）菜单获取
	CMenu* pPopupMenu = Menu.GetSubMenu(0);

	// 菜单项的启用/禁用
	pPopupMenu->EnableMenuItem(ID_EDIT_COPY, ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_bDataEncoded ? MF_ENABLED : MF_GRAYED);

	// 弹出式菜单的显示
	pPopupMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTBUTTON, point.x, point.y, this);
}


/////////////////////////////////////////////////////////////////////////////
// 菜单项的更新

void CImageView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CImageView::OnUpdateEditCut(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CImageView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_bDataEncoded);
}

void CImageView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// 主菜单的运行(copy)

void CImageView::OnEditCopy() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->CopyImage();
}


/////////////////////////////////////////////////////////////////////////////
// OLE 拖放的实现

void CImageView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_bDataEncoded)
	{
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->CopyImage(&m_OleDataSource);
	}

	CView::OnLButtonDown(nFlags, point);
}
