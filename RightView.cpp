// RightView.cpp : CRightView 类的实现文件
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#include "stdafx.h"
#include "QR_Image.h"
#include "QR_Encode.h"
#include "MainFrm.h"
#include "RightView.h"

#include "Communication.h"
#include <algorithm>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CRightView

IMPLEMENT_DYNCREATE(CRightView, CFormView)

CRightView::CRightView()
	: CFormView(CRightView::IDD)
{
	//{{AFX_DATA_INIT(CRightView)
	//}}AFX_DATA_INIT

	m_bInitControl = FALSE;
}

CRightView::~CRightView()
{
}

void CRightView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRightView)
	DDX_Control(pDX, IDC_COMBOLEVEL, m_comboLevel);
	DDX_Control(pDX, IDC_COMBOVERSION, m_comboVersion);
	DDX_Control(pDX, IDC_STATICVERSION, m_staticVersion);
	DDX_Control(pDX, IDC_CHECKAUTOEXTENT, m_checkAutoExtent);
	DDX_Control(pDX, IDC_COMBOMASKINGNO, m_comboMaskingNo);
	DDX_Control(pDX, IDC_STATICMASKINGNO, m_staticMaskingNo);
	DDX_Control(pDX, IDC_EDITMODULESIZE, m_editModuleSize);
	DDX_Control(pDX, IDC_SPINMODULESIZE, m_spinModuleSize);
	DDX_Control(pDX, IDC_STATICBMPSIZE, m_staticBmpSize);
	DDX_Control(pDX, IDC_BUTTONCOPY, m_buttonCopy);
	DDX_Control(pDX, IDC_BUTTONSAVE, m_buttonSave);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRightView, CFormView)
	//{{AFX_MSG_MAP(CRightView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_CBN_SELCHANGE(IDC_COMBOLEVEL, OnSelChangeLevel)
	ON_CBN_SELCHANGE(IDC_COMBOVERSION, OnSelChangeVersion)
	ON_BN_CLICKED(IDC_CHECKAUTOEXTENT, OnAutoExtent)
	ON_CBN_SELCHANGE(IDC_COMBOMASKINGNO, OnSelChangeMaskNo)
	ON_EN_CHANGE(IDC_EDITMODULESIZE, OnChangeDrawSize)
	ON_EN_KILLFOCUS(IDC_EDITMODULESIZE, OnKillFocusDrawSize)
	ON_BN_CLICKED(IDC_BUTTONCOPY, OnCopy)
	ON_BN_CLICKED(IDC_BUTTONSAVE, OnSave)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CRightView::OnBnClickedButton1)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRightView 診断

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRightView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CRightView 消息处理程序

void CRightView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (! m_bInitControl)
	{
		m_comboLevel.SetCurSel(1);

		m_comboVersion.SetCurSel(0);
		m_staticVersion.SetWindowText("");
		m_checkAutoExtent.SetCheck(1);
		m_checkAutoExtent.EnableWindow(FALSE);

		m_comboMaskingNo.SetCurSel(0);
		m_staticMaskingNo.SetWindowText("");

		m_editModuleSize.SetWindowText("4");
		m_spinModuleSize.SetRange(1, 20);
		m_staticBmpSize.SetWindowText("");

		m_buttonCopy.EnableWindow(FALSE);
		m_buttonSave.EnableWindow(FALSE);

		m_bInitControl = TRUE;
	}
}


/////////////////////////////////////////////////////////////////////////////
// 更新菜单项

void CRightView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	BOOL bEnable = FALSE;

	if (GetFocus() != NULL && IsWindow(GetFocus()->m_hWnd) && GetFocus()->GetDlgCtrlID() == IDC_EDITMODULESIZE)
	{
		if (m_editModuleSize.CanUndo())
		{
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
}

void CRightView::OnUpdateEditCut(CCmdUI* pCmdUI)
{
	BOOL bEnable = FALSE;

	if (GetFocus() != NULL && IsWindow(GetFocus()->m_hWnd) && GetFocus()->GetDlgCtrlID() == IDC_EDITMODULESIZE)
	{
		int nStartChar, nEndChar;

		m_editModuleSize.GetSel(nStartChar, nEndChar);

		if (nStartChar != nEndChar)
		{
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
}

void CRightView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	BOOL bEnable = FALSE;

	if (GetFocus() != NULL && IsWindow(GetFocus()->m_hWnd) && GetFocus()->GetDlgCtrlID() == IDC_EDITMODULESIZE)
	{
		int nStartChar, nEndChar;

		m_editModuleSize.GetSel(nStartChar, nEndChar);

		if (nStartChar != nEndChar)
		{
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
}

void CRightView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	BOOL bEnable = FALSE;

	if (GetFocus() != NULL && IsWindow(GetFocus()->m_hWnd) && GetFocus()->GetDlgCtrlID() == IDC_EDITMODULESIZE)
	{
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}


/////////////////////////////////////////////////////////////////////////////
// 运行菜单

void CRightView::OnEditUndo() {m_editModuleSize.Undo();}
void CRightView::OnEditCut() {m_editModuleSize.Cut();}
void CRightView::OnEditCopy() {m_editModuleSize.Copy();}
void CRightView::OnEditPaste() {m_editModuleSize.Paste();}
void CRightView::OnEditSelectAll() {m_editModuleSize.SetSel(0, -1);}


/////////////////////////////////////////////////////////////////////////////
// 输入更新后处理

void CRightView::OnSelChangeLevel() 
{
	if (m_bInitControl)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowImage();
}

void CRightView::OnSelChangeVersion() 
{
	if (m_bInitControl)
	{
		m_checkAutoExtent.EnableWindow(m_comboVersion.GetCurSel() != 0 && m_comboVersion.GetCurSel() < 40);

		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowImage();
	}
}

void CRightView::OnAutoExtent() 
{
	if (m_bInitControl)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowImage();
}

void CRightView::OnSelChangeMaskNo() 
{
	if (m_bInitControl)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowImage();
}

void CRightView::OnChangeDrawSize() 
{
	if (m_bInitControl)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowBitmapSize();
}

void CRightView::OnKillFocusDrawSize()
{
	if (m_bInitControl)
	{
		int nDrawSize = GetDlgItemInt(IDC_EDITMODULESIZE);

		if (nDrawSize <= 0)
		{
			nDrawSize = 1;
		}
		else if (nDrawSize > 20)
		{
			nDrawSize = 20;
		}

		SetDlgItemInt(IDC_EDITMODULESIZE, nDrawSize);

		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowBitmapSize();
	}
}


/////////////////////////////////////////////////////////////////////////////
// 命令按钮处理

void CRightView::OnCopy() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->CopyImage();
}

void CRightView::OnSave() 
{
	if (((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_strSavePath.IsEmpty())
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->SaveAsImage(); // 用新名称保存
	else
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->SaveImage(); // 保存活动文档
}

char HexChar(char c)
{
	if ((c >= '0') && (c <= '9'))
		return c - 0x30;
	else if ((c >= 'A') && (c <= 'F'))
		return c - 'A' + 10;
	else if ((c >= 'a') && (c <= 'f'))
		return c - 'a' + 10;
	else
		return 0x10;
}

int Str2Hex(CString str, CByteArray &data)
{
	int t, t1;
	int rlen = 0, len = str.GetLength();
	data.SetSize(len / 2);
	for (int i = 0; i < len;)
	{
		char l, h = str[i];
		if (h == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		l = str[i];
		t = HexChar(h);
		t1 = HexChar(l);
		if ((t == 16) || (t1 == 16))
			break;
		else
			t = t * 16 + t1;
		i++;
		data[rlen] = (char)t;
		rlen++;
	}
	data.SetSize(rlen);
	return rlen;
}

char ConvertHexData(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;
	if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else return(-1);
}

int String2Hex(CString str, char *SendOut)
{
	int hexdata, lowhexdata;
	int hexdatalen = 0;
	int len = str.GetLength();
	//SendOut.SetSize(len/2);
	for (int i = 0; i < len;)
	{
		char lstr, hstr = str[i];
		if (hstr == ' ' || hstr == '\r' || hstr == '\n')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		lstr = str[i];
		hexdata = ConvertHexData(hstr);
		lowhexdata = ConvertHexData(lstr);
		if ((hexdata == 16) || (lowhexdata == 16))
			break;
		else
			hexdata = hexdata * 16 + lowhexdata;
		i++;
		SendOut[hexdatalen] = (char)hexdata;
		hexdatalen++;
	}
	//senddata.SetSize(hexdatalen);
	return hexdatalen;
}

int bcd_ToUInt(unsigned char *buffer)
{
	unsigned long rslt = 0;

	if (buffer[0] == 0x02)
	{
		int len = 0;
		for (unsigned int i = 3; i < 255 + 3; ++i, ++len)
		{
			if (buffer[i] == 0x03)
				return len;
		}
	}
	return -1;
}

void GetData(unsigned char *in, CString &out)
{
	int len = bcd_ToUInt(in);
	out = "";
	char *str = out.GetBuffer();
	for (int i = 0; i < len; ++i)
	{
		out.Append((CString)&in[i + 3],1);
	}
}

void ThreadRead(void *)
{
	ComConnect *com = new ComConnect();
	com->Open();
	bool isOpen = true;
	unsigned char c_read[512] = "";

	while (isOpen)
	{
		memset(c_read, 0, sizeof(c_read));
		int len = com->Read(c_read, 512);
		if (len)
		{
			isOpen = false;
		}
	}
	com->Close();
	//CString out;
	//GetData(c_read, out);
	QRWeixin *qr = new QRWeixin();
	memcpy(qr, c_read, sizeof(QRWeixin));
	

	CMainFrame *ma = ((CMainFrame*)(AfxGetApp()->m_pMainWnd));
	ma->ShowQR((char*)qr->aucQR);
	delete qr;
}


void CRightView::OnBnClickedButton1()
{
	//unsigned char c_send[] = "02024630B44732303030303030303030313530202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202003B2";
	//unsigned char c_send[512] = "020246353C202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202077656978696E3A2F2F77787061792F62697A70617975726C3F70723D5061366276326D2020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020200326";
	CString ss = "02024630B44732303030303030303030313530202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202003B2";
	CByteArray ary;
	Str2Hex(ss, ary);

	ComConnect *com = new ComConnect();
	com->Open();
	for (int i = 0; i < ary.GetSize(); ++i)
	{
		com->Write(&ary[i], 1);
	}
	com->Close();

	void(*fun)(void*);
	fun = ThreadRead;
	_beginthread(fun, 0, NULL);
// 	if (!com->Write(&ary[0], ary.GetSize()))
// 		//if (!com->Write((void*)c_send, 502))
// 	{
// 		AfxMessageBox("写入失败");
// 		com->Close();
// 		return;
// 	}

	//unsigned char c_read[512] = "";
	//if (!com->Read(c_read, 512))
	//{
	//	AfxMessageBox("读取失败");
	//	com->Close();
	//	return;
	//}
	//com->Close();

	//if (!c_read)
	//{
	//	AfxMessageBox("超时");
	//	com->Close();
	//	return;
	//}

	//CString out;
	//GetData(c_read, out);
	////if (!CheckFlag(c_read))
	////{
	////	AfxMessageBox("报文格式错误");
	////	return;
	////}


	//CMainFrame *ma = ((CMainFrame*)(AfxGetApp()->m_pMainWnd));
	//ma->ShowQR(out.GetBuffer());
}


