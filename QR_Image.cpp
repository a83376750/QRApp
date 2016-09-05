// QR_Image.cpp : 应用程序类的功能定义
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#include "stdafx.h"
#include "QR_Image.h"

#include "QR_Encode.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQR_ImageApp

BEGIN_MESSAGE_MAP(CQR_ImageApp, CWinApp)
	//{{AFX_MSG_MAP(CQR_ImageApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CQR_ImageApp 类的构造函数

CQR_ImageApp::CQR_ImageApp()
{
}


/////////////////////////////////////////////////////////////////////////////
// 唯一的 CQR_ImageApp 对象
CQR_ImageApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CQR_ImageApp 类的初始化

BOOL CQR_ImageApp::InitInstance()
{
	// OLE 初始化
	if (! AfxOleInit())
	   return FALSE;

// 内存泄漏检测检查点的设置（调试时用）
//※ToolTip相关的泄漏是没有问题
#ifdef _DEBUG
	mStart.Checkpoint();
#endif //_DEBUG

#if _MFC_VER <= 0x0600
	#ifdef _AFXDLL
		Enable3dControls();
	#else
		Enable3dControlsStatic();
	#endif
#endif

	//  创建主窗口
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// 从资源加载框架
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW, NULL, NULL);

	//应用程序图标集
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pFrame->SetIcon(hIcon, TRUE);

	// 主窗口的显示、更新
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

int CQR_ImageApp::ExitInstance() 
{
// 内存泄漏信息显示（调试时用）
#ifdef _DEBUG
	mEnd.Checkpoint();

	if (mDiff.Difference(mStart, mEnd))
	{
		TRACE("\n-------- Detected memory leaks. DUMP(DumpStatistics) Start --------\n");
		mDiff.DumpStatistics();
		TRACE("-------- Detected memory leaks. DUMP(DumpStatistics) End --------\n");

		TRACE("\n-------- Detected memory leaks. DUMP(DumpAllObjectsSince) Start --------\n");
		mDiff.DumpAllObjectsSince();
		TRACE("-------- Detected memory leaks. DUMP(DumpAllObjectsSince) End --------\n\n");

//		AfxMessageBox("Detected memory leaks.", MB_OK | MB_ICONEXCLAMATION);
	}
	else
	{
		TRACE("\n-------- No detected memory leaks. OK !! --------\n\n");
	}
#endif //_DEBUG

	return CWinApp::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// 用于CAboutDlg对话框的版本信息

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	HCURSOR m_hCurArrow, m_hCurWait, m_hCurHand;
	HFONT   m_hFont;  //  URL/MailTo 查看文本字体


	// 对话框数据
	BOOL m_bPointOnUrl;
	BOOL m_bPointOnMailTo;

	// 儅僂僗儃僞儞墴忋帪偵僐儅儞僪幚峴偡傞偨傔偺僼儔僌
	BOOL m_bBtnDownUrl;
	BOOL m_bBtnDownMailTo;

// 僟僀傾儘僌 僨乕僞
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 偺僒億乕僩
	//}}AFX_VIRTUAL

// 僀儞僾儕儊儞僥乕僔儑儞
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// 僟僀傾儘僌傪幚峴偡傞偨傔偺傾僾儕働乕僔儑儞僐儅儞僪
void CQR_ImageApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_hCurArrow = LoadCursor(NULL, IDC_ARROW);
	m_hCurWait  = LoadCursor(NULL, IDC_WAIT);
	m_hCurHand  = AfxGetApp()->LoadCursor(IDC_RHAND);

	m_bPointOnUrl = m_bPointOnMailTo = FALSE;
	m_bBtnDownUrl = m_bBtnDownMailTo = FALSE;

	// 僼僅儞僩嶌惉乮傾儞僟乕儔僀儞晅壛乯
	LOGFONT lf;
	lf.lfHeight			= 12;
	lf.lfWidth			= 0;
	lf.lfEscapement		= 0;
	lf.lfOrientation	= 0;
	lf.lfWeight			= FW_DONTCARE;
	lf.lfItalic			= FALSE;
	lf.lfUnderline		= TRUE;
	lf.lfStrikeOut		= FALSE;
	lf.lfCharSet		= SHIFTJIS_CHARSET;
	lf.lfOutPrecision	= CLIP_DEFAULT_PRECIS;
	lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	lf.lfQuality		= PROOF_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH;
	lstrcpy(lf.lfFaceName, "俵俽 俹僑僔僢僋");

	m_hFont = CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATICURL)->SendMessage(WM_SETFONT, (WPARAM)m_hFont, TRUE);
	GetDlgItem(IDC_STATICMAILTO)->SendMessage(WM_SETFONT, (WPARAM)m_hFont, TRUE);

	return TRUE;
}

void CAboutDlg::OnDestroy()
{
	CDialog::OnDestroy();
	
	// 巊梡僆僽僕僃僋僩攋婞
	DeleteObject(m_hFont);
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	int nID = pWnd->GetDlgCtrlID();

	if (nID == IDC_STATICURL)
		pDC->SetTextColor(m_bPointOnUrl ? RGB(255, 128, 0) : RGB(0, 0, 128));

	if (nID == IDC_STATICMAILTO)
		pDC->SetTextColor(m_bPointOnMailTo ? RGB(255, 128, 0) : RGB(0, 0, 128));

	return hbr;
}

void CAboutDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// 儅僂僗嵗昗埵抲僠僃僢僋
	ClientToScreen(&point);

	CRect rectUrl;
	GetDlgItem(IDC_STATICURL)->GetWindowRect(rectUrl);

	CRect rectMailTo;
	GetDlgItem(IDC_STATICMAILTO)->GetWindowRect(rectMailTo);

	// 僇乕僜儖曄峏
	SetCursor(rectUrl.PtInRect(point) || rectMailTo.PtInRect(point) ? m_hCurHand : m_hCurArrow);

	if (m_bPointOnUrl != rectUrl.PtInRect(point))
	{
		// URL 昞帵僥僉僗僩怓曄峏
		GetDlgItem(IDC_STATICURL)->InvalidateRect(NULL);
		m_bPointOnUrl = rectUrl.PtInRect(point);

		if (m_bPointOnUrl)
			SetCapture();
		else
			ReleaseCapture();
	}

	if (m_bPointOnMailTo != rectMailTo.PtInRect(point))
	{
		// mailto 昞帵僥僉僗僩怓曄峏
		GetDlgItem(IDC_STATICMAILTO)->InvalidateRect(NULL);
		m_bPointOnMailTo = rectMailTo.PtInRect(point);

		if (m_bPointOnMailTo)
			SetCapture();
		else
			ReleaseCapture();
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 儅僂僗嵗昗埵抲僠僃僢僋
	ClientToScreen(&point);

	CRect rectUrl;
	GetDlgItem(IDC_STATICURL)->GetWindowRect(rectUrl);

	CRect rectMailTo;
	GetDlgItem(IDC_STATICMAILTO)->GetWindowRect(rectMailTo);

	// 僇乕僜儖曄峏
	SetCursor(rectUrl.PtInRect(point) || rectMailTo.PtInRect(point) ? m_hCurHand : m_hCurArrow);

	m_bBtnDownUrl    = rectUrl.PtInRect(point);
	m_bBtnDownMailTo = rectMailTo.PtInRect(point);

	CDialog::OnLButtonDown(nFlags, point);
}

void CAboutDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bBtnDownUrl)
	{
		// 儅僂僗嵗昗埵抲僠僃僢僋
		ClientToScreen(&point);

		CRect rectUrl;
		GetDlgItem(IDC_STATICURL)->GetWindowRect(rectUrl);

		if (rectUrl.PtInRect(point))
		{
			SetCursor(m_hCurWait);

			// 僽儔僂僓婲摦
			ShellExecute(m_hWnd, "open", "http://www.psytec.co.jp/", NULL, "", SW_SHOW);

			// 杮僟僀傾儘僌偑塀偝傟傞応崌傪峫椂偟僥僉僗僩傪嵞昤夋
			m_bPointOnUrl = FALSE;
			GetDlgItem(IDC_STATICURL)->InvalidateRect(NULL);

			SetCursor(m_hCurArrow);
		}

		m_bBtnDownUrl = FALSE;
	}
	else if (m_bBtnDownMailTo)
	{
		// 儅僂僗嵗昗埵抲僠僃僢僋
		ClientToScreen(&point);

		CRect rectMailTo;
		GetDlgItem(IDC_STATICMAILTO)->GetWindowRect(rectMailTo);

		if (rectMailTo.PtInRect(point))
		{
			SetCursor(m_hCurWait);

			// 儊乕儔婲摦
			ShellExecute(m_hWnd, "open", "mailto:info@psytec.co.jp", NULL, "", SW_SHOW);

			// 杮僟僀傾儘僌偑塀偝傟傞応崌傪峫椂偟僥僉僗僩傪嵞昤夋
			m_bPointOnMailTo = FALSE;
			GetDlgItem(IDC_STATICMAILTO)->InvalidateRect(NULL);

			SetCursor(m_hCurArrow);
		}

		m_bBtnDownMailTo = FALSE;
	}

	CDialog::OnLButtonUp(nFlags, point);
}
