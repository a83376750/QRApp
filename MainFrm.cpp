// MainFrm.cpp : CMainFrame ��Ĳ�������
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#include "stdafx.h"
#include "QR_Image.h"

#include "MainFrm.h"
#include "QR_Encode.h"
#include "ImageView.h"
#include "RightView.h"
#include "BottomView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CX_SPLITTER	7
#define CY_SPLITTER	7
#define CX_MARGIN	2
#define CY_MARGIN	2

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_GETMINMAXINFO()
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_KANA,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame ��Ĺ��캯������������

CMainFrame::CMainFrame()
{
	m_bInitSplit = FALSE;

	m_bDataEncoded = FALSE;
	m_pSymbleDC = NULL;

	m_strSavePath.Empty();
}

CMainFrame::~CMainFrame()
{
	if (m_pSymbleDC != NULL)
	{
		m_pSymbleDC->SelectObject(m_pOldBitmap);

		delete m_pSymbleBitmap;
		delete m_pSymbleDC;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame::OnCreate

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (! m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		! m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	if (! m_wndStatusBar.Create(this) ||
		! m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}

	//״̬��ָʾ����ȷ��ʾ ��������Ŀ��ȸ���
	m_wndStatusBar.SetPaneInfo(0, 0, SBPS_NOBORDERS | SBPS_STRETCH, 0);

	// ��ʾ��С�ĳߴ�
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	rcWindow.BottomRight() = rcWindow.TopLeft();
	MoveWindow(rcWindow);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame ������

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame ��Ϣ��������

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CMainFrame ���b�Z�[�W �n���h��

/////////////////////////////////////////////////////////////////////////////
// CMainFrame::OnSetFocus

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	SetActiveView((CView*)(m_wndSplitter1.GetPane(1, 0)));
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame::OnCmdMsg

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame::OnCreateClient

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// �ָ�ڵ�����
//  +----------+----------+
//  |          |          |
//  | ��ʾ���� | ���ô��� |
//  |          |          |
//  +----------+----------+
//  |     �������봰��    |
//  +---------------------+
	m_wndSplitter1.CreateStatic(this, 2, 1);
	m_wndSplitter1.CreateView(1, 0, RUNTIME_CLASS(CBottomView), CSize(0, 0), pContext);

	m_wndSplitter2.CreateStatic(&m_wndSplitter1, 1, 2);
	m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CImageView), CSize(0, 0), pContext);
	m_wndSplitter2.CreateView(0, 1, RUNTIME_CLASS(CRightView), CSize(0, 0), pContext);

	m_pwndBottomView = ((CBottomView*)m_wndSplitter1.GetPane(1, 0));
	m_pwndRightView  = ((CRightView*)m_wndSplitter2.GetPane(0, 1));

		// ��ȡָ���ĳߴ�
	m_sizeBottomView = ((CFormView*)m_wndSplitter1.GetPane(1, 0))->GetTotalSize();
	m_sizeRightView  = ((CFormView*)m_wndSplitter2.GetPane(0, 1))->GetTotalSize();

	CRect rcClient;
	GetClientRect(rcClient);

	m_wndSplitter1.SetRowInfo(0, (rcClient.Height() - (CY_SPLITTER + CY_MARGIN * 2)) - m_sizeBottomView.cy, 0);
	m_wndSplitter2.SetColumnInfo(0, (rcClient.Width() - (CX_SPLITTER + CX_MARGIN * 2)) - m_sizeRightView.cx, 0);

	m_bInitSplit = TRUE;

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame::RecalcLayout

void CMainFrame::RecalcLayout(BOOL bNotify) 
{
	if (m_bInitSplit)
	{
		CRect rcClient;
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, &rcClient);

		int cy0, cy1, cyMin;

		m_wndSplitter1.GetRowInfo(0, cy0, cyMin);
		m_wndSplitter1.GetRowInfo(1, cy1, cyMin);

		if (cy0 >= 0 && cy1 >= 0)
		{
			if ((cy1 > m_sizeBottomView.cy) && (rcClient.Height() < cy0 + cy1 + (CY_SPLITTER + CY_MARGIN * 2)))
			{
				cy1 = max(m_sizeBottomView.cy, (rcClient.Height() - (CY_SPLITTER + CY_MARGIN * 2)) - cy0);
			}

			cy0 = (rcClient.Height() - (CY_SPLITTER + CY_MARGIN * 2)) - cy1;

			m_wndSplitter1.SetRowInfo(0, cy0, 0);
			m_wndSplitter1.RecalcLayout();
		}

		int cx0, cx1, cxMin;

		m_wndSplitter2.GetColumnInfo(0, cx0, cxMin);
		m_wndSplitter2.GetColumnInfo(1, cx1, cxMin);

		if (cx0 >= 0 && cx1 >= 0)
		{
			if ((cx1 > m_sizeRightView.cx) && (rcClient.Width() < cx0 + cx1 + (CX_SPLITTER + CX_MARGIN * 2)))
			{
				cx1 = max(m_sizeRightView.cx, (rcClient.Width() - (CX_SPLITTER + CX_MARGIN * 2)) - cx0);
			}

			cx0 = (rcClient.Width() - (CX_SPLITTER + CX_MARGIN * 2)) - cx1;

			m_wndSplitter2.SetColumnInfo(0, cx0, 0);
			m_wndSplitter2.RecalcLayout();
		}
	}

	CFrameWnd::RecalcLayout(bNotify);
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame::OnGetMinMaxInfo

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	static BOOL bRestore = FALSE; // ����С���ָ�ʱ������
	if (IsWindow(m_wndSplitter1.m_hWnd) && ! bRestore)
	{
		CRect rcWindow;
		GetWindowRect(&rcWindow);

		CRect rcClient;
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, &rcClient);

		lpMMI->ptMinTrackSize.y = m_sizeRightView.cy + m_sizeBottomView.cy + CX_SPLITTER + CX_MARGIN * 2 + (rcWindow.Height() - rcClient.Height());
		lpMMI->ptMinTrackSize.x = m_sizeBottomView.cx + CY_MARGIN * 2 + (rcWindow.Width() - rcClient.Width());
	}

	bRestore = IsIconic();//�ж��Ƿ���С��

	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}


/////////////////////////////////////////////////////////////////////////////
// �˵���ĸ���(����&����Ϊ)

void CMainFrame::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bDataEncoded);
}

void CMainFrame::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bDataEncoded);
}


/////////////////////////////////////////////////////////////////////////////
// �˵����ִ��(����&����Ϊ)

void CMainFrame::OnFileSave() 
{
	m_strSavePath.IsEmpty() ? SaveAsImage() : SaveImage();
}

void CMainFrame::OnFileSaveAs() 
{
	SaveAsImage();
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame::ShowImage
// �� ;������QR��ͼ��
// �� ע��ʵ�ʻ滭����CImageView::OnDraw��

void CMainFrame::ShowImage()
{
	int nLevel = m_pwndRightView->m_comboLevel.GetCurSel();
	int nVersion = m_pwndRightView->m_comboVersion.GetCurSel();
	BOOL bAutoExtent = (m_pwndRightView->m_checkAutoExtent.GetCheck() != 0);
	int nMaskingNo = m_pwndRightView->m_comboMaskingNo.GetCurSel() - 1;

	CString strEncodeData;
	m_pwndBottomView->m_editSoureData.GetWindowText(strEncodeData);

	int i, j;

	CQR_Encode* pQR_Encode = new CQR_Encode;

	m_bDataEncoded = pQR_Encode->EncodeData(nLevel, nVersion, bAutoExtent, nMaskingNo, strEncodeData);

	if (m_bDataEncoded)
	{
		if (m_pSymbleDC != NULL)
		{
			m_pSymbleDC->SelectObject(m_pOldBitmap);

			delete m_pSymbleBitmap;
			delete m_pSymbleDC;
		}

		m_nSymbleSize = pQR_Encode->m_nSymbleSize + (QR_MARGIN * 2);

		m_pSymbleBitmap = new CBitmap;
		m_pSymbleBitmap->CreateBitmap(m_nSymbleSize, m_nSymbleSize, 1, 1, NULL);

		m_pSymbleDC = new CDC;
		m_pSymbleDC->CreateCompatibleDC(NULL);

		m_pOldBitmap = m_pSymbleDC->SelectObject(m_pSymbleBitmap);

		// ��������
		m_pSymbleDC->PatBlt(0, 0, m_nSymbleSize, m_nSymbleSize, WHITENESS);

		
		// ������
		for (i = 0; i < pQR_Encode->m_nSymbleSize; ++i)
		{
			for (j = 0; j < pQR_Encode->m_nSymbleSize; ++j)
			{
				if (pQR_Encode->m_byModuleData[i][j])
				{
					m_pSymbleDC->SetPixel(i + QR_MARGIN, j + QR_MARGIN, RGB(0, 0, 0));
				}
			}
		}

		// ��ʾ�汾��(�ͺ�)
		CString strWork;

		if (nVersion != pQR_Encode->m_nVersion)
			strWork.Format("(%d)", pQR_Encode->m_nVersion);
		else
			strWork.Empty();

		m_pwndRightView->m_staticVersion.SetWindowText(strWork);

		// ѡ���Զ���ģ�ĺ�����ʾ(��8����ģ)
		if (nMaskingNo == -1)
			strWork.Format("(%d)", pQR_Encode->m_nMaskingNo);
		else
			strWork.Empty();

		m_pwndRightView->m_staticMaskingNo.SetWindowText(strWork);

		// ���ð�ť
		m_pwndRightView->m_buttonCopy.EnableWindow();
		m_pwndRightView->m_buttonSave.EnableWindow();
	}
	else
	{
		// �����ʾ
		m_pwndRightView->m_staticVersion.SetWindowText("");
		m_pwndRightView->m_staticMaskingNo.SetWindowText("");

		// ���ð�ť
		m_pwndRightView->m_buttonCopy.EnableWindow(FALSE);
		m_pwndRightView->m_buttonSave.EnableWindow(FALSE);
	}

	delete pQR_Encode;

	// ����(����)ͼ��ʱ��ʾ�ߴ�
	ShowBitmapSize();

	// ���û�ͼ����
	m_wndSplitter1.GetPane(0, 0)->InvalidateRect(NULL, FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame::ShowBitmapSize
// �� ;��������(����)ͼ��ʱ��ʾ�ߴ�

void CMainFrame::ShowBitmapSize()
{
	CString strWork;
	strWork.Empty();

	if (m_bDataEncoded)
	{
		int nModuleSize = m_pwndRightView->GetDlgItemInt(IDC_EDITMODULESIZE);

		if (nModuleSize >= 1 && nModuleSize <= 20) 
		{
			int nSize = m_nSymbleSize * nModuleSize;
			strWork.Format("%d X %d", nSize, nSize);
		}
	}

	m_pwndRightView->m_staticBmpSize.SetWindowText(strWork);
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame::CopyImage
// ��  ;��QR��ͼ���Ƶ�������
// ��  ����COleDataSource ��ַ��Ĭ��= NULL��
// ��  ע��COleDataSource ���δָ��OLE�Ϸţ�Ĭ��ʹ��DIB��ʽ���Ƶ�������

void CMainFrame::CopyImage(COleDataSource* pOleDataSource)
{
	int nPixelSize = m_nSymbleSize * m_pwndRightView->GetDlgItemInt(IDC_EDITMODULESIZE);

	// ��ȡλͼ�ߴ�
	int nBmpSize = ((nPixelSize + 31) / 32) * 32 / 8;
	nBmpSize *= nPixelSize;

	// ��ȡȫ���ڴ��
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2 + nBmpSize);

	if (hGlobal == NULL)
	{
		MessageBox("û���㹻���ڴ�ռ�", NULL, MB_ICONEXCLAMATION);
		return;
	}

	LPBYTE lpbyBits = (LPBYTE)GlobalLock(hGlobal);

	// �ṹ���ַ����
	LPBITMAPINFO pbmi = (LPBITMAPINFO)lpbyBits;
	LPVOID       pbdt = lpbyBits + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2;

	// LPBITMAPINFO->BITMAPINFOHEADER
	pbmi->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth			= nPixelSize;
	pbmi->bmiHeader.biHeight		= nPixelSize;
	pbmi->bmiHeader.biPlanes		= 1;
	pbmi->bmiHeader.biBitCount		= 1;
	pbmi->bmiHeader.biCompression	= BI_RGB;
	pbmi->bmiHeader.biSizeImage		= nBmpSize;
	pbmi->bmiHeader.biXPelsPerMeter = 3780;
	pbmi->bmiHeader.biYPelsPerMeter = 3780;
	pbmi->bmiHeader.biClrUsed		= 0;
	pbmi->bmiHeader.biClrImportant	= 0;

	CDC* pWorkDC = new CDC;
	pWorkDC->CreateCompatibleDC(NULL);

	CBitmap* pWorkBitmap = new CBitmap;
	pWorkBitmap->CreateBitmap(nPixelSize, nPixelSize, 1, 1, NULL);

	CBitmap* pOldBitmap = pWorkDC->SelectObject(pWorkBitmap);
	pWorkDC->StretchBlt(0, 0, nPixelSize, nPixelSize, m_pSymbleDC, 0, 0, m_nSymbleSize, m_nSymbleSize, SRCCOPY);

	GetDIBits(pWorkDC->m_hDC, (HBITMAP)*pWorkBitmap, 0, nPixelSize, pbdt, pbmi, DIB_RGB_COLORS);

	GlobalUnlock(hGlobal);

	pWorkDC->SelectObject(pOldBitmap);
	delete pWorkBitmap;
	delete pWorkDC;

	if (pOleDataSource == NULL)
	{
		// ���Ƶ�������
		OpenClipboard();
		EmptyClipboard();
		SetClipboardData(CF_DIB, hGlobal);
		CloseClipboard();
	}
	else
	{
		// OLE�Ϸŵ����ݴ���
		pOleDataSource->CacheGlobalData(CF_DIB, hGlobal);
		pOleDataSource->DoDragDrop(DROPEFFECT_COPY);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame::SaveAsImage
// �� ;��QR��ͼ�񱣴�Ϊλͼ�ļ�(����Ϊ)

void CMainFrame::SaveAsImage()
{
	// CFileDialog ��Ĺ���
	CFileDialog* pFileDialog = new CFileDialog(FALSE, "bmp", m_strSavePath, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST,
											   "λͼ�ļ� (*.bmp)|*.bmp|�����ļ�(*.*)|*.*||", this);

	pFileDialog->m_ofn.lpstrTitle = "QR Code ͼ�񱣴�?";

	CString strFileName;

	//��ʵ�������ļ����Ի���
	if (pFileDialog->DoModal() == IDOK)
		strFileName = pFileDialog->GetPathName();

	delete 	pFileDialog;

	if (strFileName.IsEmpty())
		return;

	m_strSavePath = strFileName;

	SaveImage();
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame::SaveImage
// QR��ͼ�񱣴�Ϊλͼ�ļ�(����)

void CMainFrame::SaveImage()
{
	int nPixelSize = m_nSymbleSize * m_pwndRightView->GetDlgItemInt(IDC_EDITMODULESIZE);

	// ��ȡλͼ�ߴ�
	int nBmpSize = ((nPixelSize + 31) / 32) * 32 / 8;
	nBmpSize *= nPixelSize;

	// ����һ���ڴ�ӳ���ļ�
	HANDLE hFile = CreateFile(m_strSavePath, GENERIC_READ | GENERIC_WRITE, 0, NULL,
							  CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		m_strSavePath.Empty();
		MessageBox("�ļ��򿪴���", "QR Code ���񱣴�?", MB_ICONSTOP);
		return;
	}

	HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE | SEC_COMMIT, 0, 
						  sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2 + nBmpSize, NULL);
	LPBYTE lpbyMapView = (LPBYTE)MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, 0);

	ZeroMemory(lpbyMapView, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2 + nBmpSize);

	// �ṹ���ַ����
	LPBITMAPFILEHEADER pbfh = (LPBITMAPFILEHEADER)lpbyMapView;
	LPBITMAPINFO       pbmi = (LPBITMAPINFO)(lpbyMapView + sizeof(BITMAPFILEHEADER));
	LPVOID             pbdt = lpbyMapView + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2;

	// BITMAPFILEHEADER
	pbfh->bfType      = (WORD) (('M' << 8) | 'B'); // "BM"
	pbfh->bfSize      = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2 + nBmpSize;
	pbfh->bfReserved1 = 0;
	pbfh->bfReserved2 = 0;
	pbfh->bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2;

	// LPBITMAPINFO->BITMAPINFOHEADER
	pbmi->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth			= nPixelSize;
	pbmi->bmiHeader.biHeight		= nPixelSize;
	pbmi->bmiHeader.biPlanes		= 1;
	pbmi->bmiHeader.biBitCount		= 1;
	pbmi->bmiHeader.biCompression	= BI_RGB;
	pbmi->bmiHeader.biSizeImage		= nBmpSize;
	pbmi->bmiHeader.biXPelsPerMeter = 3780;
	pbmi->bmiHeader.biYPelsPerMeter = 3780;
	pbmi->bmiHeader.biClrUsed		= 0;
	pbmi->bmiHeader.biClrImportant	= 0;

	CDC* pWorkDC = new CDC;
	pWorkDC->CreateCompatibleDC(NULL);

	CBitmap* pWorkBitmap = new CBitmap;
	pWorkBitmap->CreateBitmap(nPixelSize, nPixelSize, 1, 1, NULL);

	CBitmap* pOldBitmap = pWorkDC->SelectObject(pWorkBitmap);
	pWorkDC->StretchBlt(0, 0, nPixelSize, nPixelSize, m_pSymbleDC, 0, 0, m_nSymbleSize, m_nSymbleSize, SRCCOPY);

	GetDIBits(pWorkDC->m_hDC, (HBITMAP)*pWorkBitmap, 0, nPixelSize, pbdt, pbmi, DIB_RGB_COLORS);

	pWorkDC->SelectObject(pOldBitmap);
	delete pWorkBitmap;
	delete pWorkDC;

	UnmapViewOfFile(lpbyMapView);
	CloseHandle(hFileMapping);
	CloseHandle(hFile);
}

void CMainFrame::ShowQR(char *str)
{
	if (strlen(str) == 0)
		return;
	m_pwndBottomView->m_editSoureData.SetWindowTextA(str);
	ShowImage();
}