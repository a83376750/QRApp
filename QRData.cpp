#include "stdafx.h"
#include "QRData.h"
#include "Communication.h"
#include "MainFrm.h"
#include "AppFunction.h"
#include "QR_Timer.h"

void ThreadRead(void *data)
{
	ComConnect *com = new ComConnect();
	if (!com->Open())
	{
		return;
	}
	QRWeixin *qr = new QRWeixin();
	int len = com->Read(qr, sizeof(QRWeixin));
	com->Close();

	if (!len)
	{
		AfxMessageBox("读取串口失败");
		return;
	}

	unsigned char *pQRCode = qr->aucQR;
	for (len = 0; len < sizeof(qr->aucQR); ++len)
	{
		if (pQRCode[len] == ' ')
			break;
	}
	CString QRCode;
	QRCode.Append((char*)pQRCode, len);

	CMainFrame *ma = ((CMainFrame*)(AfxGetApp()->m_pMainWnd));
	ma->ShowQR((char*)QRCode.GetString());
	delete qr;
}

bool QRData::QR_NET_HandShake()
{
	QR_Pc2Mid_NET_HandShake p2mHandShake;
	p2mHandShake.ucStartFlag = 0x02;
	p2mHandShake.ucEndFlag = 0x03;
	p2mHandShake.ucTranType = '6';
	p2mHandShake.ucTimeout = 0x05;
	memset(p2mHandShake.aucPayType, 0x20, sizeof(p2mHandShake.aucPayType));
	memset(p2mHandShake.aucAmount, 0x20, sizeof(p2mHandShake.aucAmount));
	memset(p2mHandShake.aucPassword, 0x20, sizeof(p2mHandShake.aucPassword));
	memset(p2mHandShake.aucOriginalOrderNo, 0x20, sizeof(p2mHandShake.aucOriginalOrderNo));
	memset(p2mHandShake.aucTraceNo, 0x20, sizeof(p2mHandShake.aucTraceNo));
	memset(p2mHandShake.aucQRCode, 0x20, sizeof(p2mHandShake.aucQRCode));
	int len = bcd_ToUInt((unsigned char*)&p2mHandShake);

	DectoBCD(len, p2mHandShake.aucDataLength, 2);

	p2mHandShake.ucAscCheck = LRCBuffer(&p2mHandShake);

	CString ss;
	ss.Append((char*)&p2mHandShake, sizeof(p2mHandShake));
	CByteArray ary;
	ary.SetSize(sizeof(p2mHandShake));
	unsigned char *pHandShake = (unsigned char*)&p2mHandShake;
	for (int i = 0; i < sizeof(p2mHandShake); ++i)
	{
		ary[i] = pHandShake[i];
	}
	//Str2Hex(ss, ary);

	ComConnect *com = new ComConnect();
	if (!com->Open())
	{
		com->Close();
		return false;
	}
	for (int i = 0; i < ary.GetSize(); ++i)
	{
		com->Write(&ary[i], 1);
	}

	QR_Mid2Pc_NET_HandShake m2pHandShake;
	len = com->Read(&m2pHandShake, sizeof(m2pHandShake));
	if (!len)
	{
		AfxMessageBox("握手,读取串口失败");
		com->Close();
		return false;
	}

	if (m2pHandShake.ucStartFlag != 0x02)
	{
		AfxMessageBox("包有误");
		com->Close();
		return false;
	}

	AfxMessageBox("握手,交易结果:成功");
	com->Close();
	return true;
}

bool QRData::QR_NET_SignIn()
{
	QR_Pc2Mid_NET_SignIn p2mSignIn;
	p2mSignIn.ucStartFlag = 0x02;
	p2mSignIn.ucEndFlag = 0x03;
	p2mSignIn.ucTranType = '6';
	p2mSignIn.ucTimeout = 0x05;
	memset(p2mSignIn.aucPayType, 0x20, sizeof(p2mSignIn.aucPayType));
	memset(p2mSignIn.aucAmount, 0x20, sizeof(p2mSignIn.aucAmount));
	memset(p2mSignIn.aucPassword, 0x20, sizeof(p2mSignIn.aucPassword));
	memset(p2mSignIn.aucOriginalOrderNo, 0x20, sizeof(p2mSignIn.aucOriginalOrderNo));
	memset(p2mSignIn.aucOriginalTraceNo, 0x20, sizeof(p2mSignIn.aucOriginalTraceNo));
	memset(p2mSignIn.aucQRCode, 0x20, sizeof(p2mSignIn.aucQRCode));
	int len = bcd_ToUInt((unsigned char*)&p2mSignIn);
	DectoBCD(len, p2mSignIn.aucDataLength, 2);
	p2mSignIn.ucAscCheck = LRCBuffer(&p2mSignIn);

	ComConnect *com = new ComConnect();
	if (!com->Open())
	{
		com->Close();
		return false;
	}

	unsigned char *pSignIn = (unsigned char*)&p2mSignIn;
	for (int i = 0; i < sizeof(pSignIn); ++i)
	{
		com->Write(&pSignIn[i], 1);
	}

	QR_Mid2Pc_NET_SignIn m2pSignIn;
	len = com->Read(&m2pSignIn, sizeof(QR_Mid2Pc_NET_SignIn));
	if (!len)
	{
		AfxMessageBox("交易 - 读取串口失败");
		com->Close();
		return false;
	}
	AfxMessageBox((char*)m2pSignIn.aucTranResult);
	return true;
}

bool QRData::QR_PAY_HandShake()
{
	QR_Pc2Mid_PAY_HandShake p2mHandShake;
	p2mHandShake.ucStartFlag = 0x02;
	p2mHandShake.ucEndFlag = 0x03;
	p2mHandShake.ucTranType = '6';
	p2mHandShake.ucTimeout = 0x05;
	memset(p2mHandShake.aucPayType, 0x20, sizeof(p2mHandShake.aucPayType));
	memset(p2mHandShake.aucAmount, 0x20, sizeof(p2mHandShake.aucAmount));
	memset(p2mHandShake.aucPassword, 0x20, sizeof(p2mHandShake.aucPassword));
	memset(p2mHandShake.aucOriginalOrderNo, 0x20, sizeof(p2mHandShake.aucOriginalOrderNo));
	memset(p2mHandShake.aucOriginalTraceNo, 0x20, sizeof(p2mHandShake.aucOriginalTraceNo));
	memset(p2mHandShake.aucQRCode, 0x20, sizeof(p2mHandShake.aucQRCode));
	int len = bcd_ToUInt((unsigned char*)&p2mHandShake);
	DectoBCD(len, p2mHandShake.aucDataLength, 2);
	p2mHandShake.ucAscCheck = LRCBuffer(&p2mHandShake);

	CString ss;
	ss.Append((char*)&p2mHandShake, sizeof(p2mHandShake));
	CByteArray ary;
	ary.SetSize(sizeof(p2mHandShake));
	unsigned char *pHandShake = (unsigned char*)&p2mHandShake;
	for (int i = 0; i < sizeof(p2mHandShake); ++i)
	{
		ary[i] = pHandShake[i];
	}
	//Str2Hex(ss, ary);

	ComConnect *com = new ComConnect();
	if (!com->Open())
	{
		com->Close();
		return false;
	}
	for (int i = 0; i < ary.GetSize(); ++i)
	{
		com->Write(&ary[i], 1);
	}

	QR_Mid2Pc_PAY_HandShake m2pHandShake;
	len = com->Read(&m2pHandShake, sizeof(m2pHandShake));
	if (!len)
	{
		AfxMessageBox("握手,读取串口失败");
		com->Close();
		return false;
	}
	
	if (m2pHandShake.ucStartFlag != 0x02)
	{
		AfxMessageBox("包有误");
		com->Close();
		return false;
	}

	AfxMessageBox("握手,交易结果:成功");
	com->Close();
	return true;
}

bool QRData::QR_PAY_TransAsk()
{
	QR_Timer ti;
	ti.Start();
	QR_Pc2Mid_PAY_TransAsk p2mTransAsk;
	p2mTransAsk.ucStartFlag = 0x02;
	p2mTransAsk.ucEndFlag = 0x03;
	p2mTransAsk.ucTranType = '0';
	p2mTransAsk.ucTimeout = 0xB4;
	memset(p2mTransAsk.aucPassword, 0x20, sizeof(p2mTransAsk.aucPassword));
	p2mTransAsk.aucPayType[0] = 'G';
	p2mTransAsk.aucPayType[1] = '2';
	memcpy(p2mTransAsk.aucAmount, "000000000001", sizeof(p2mTransAsk.aucAmount));
	memset(p2mTransAsk.aucPassword, 0x02, sizeof(p2mTransAsk.aucPassword));
	memset(p2mTransAsk.aucOriginalOrderNo, 0x20, sizeof(p2mTransAsk.aucOriginalOrderNo));
	memset(p2mTransAsk.aucOriginalTraceNo, 0x20, sizeof(p2mTransAsk.aucOriginalTraceNo));
	memset(p2mTransAsk.aucQRCode, 0x20, sizeof(p2mTransAsk.aucQRCode));

	int len = bcd_ToUInt((unsigned char*)&p2mTransAsk);
	DectoBCD(len, p2mTransAsk.aucDataLength, 2);

	p2mTransAsk.ucAscCheck = LRCBuffer(&p2mTransAsk);

	ComConnect *com = new ComConnect();
	if (!com->Open())
	{
		com->Close();
		return false;
	}

	unsigned char *pTransAsk = (unsigned char*)&p2mTransAsk;
	for (int i = 0; i < sizeof(p2mTransAsk); ++i)
	{
		com->Write(&pTransAsk[i], 1);
	}

	QR_Mid2Pc_PAY_QRCodeDisplay m2pQRCodeDisplay;
	len = com->Read(&m2pQRCodeDisplay, sizeof(QR_Mid2Pc_PAY_QRCodeDisplay));
	if (!len)
	{
		AfxMessageBox("交易 - 读取串口失败");
		com->Close();
		return false;
	}
	
	unsigned char *pQRCode = m2pQRCodeDisplay.aucQRCode;
	for (len = 0; len < sizeof(m2pQRCodeDisplay.aucQRCode); ++len)
	{
		if (pQRCode[len] == ' ')
			break;
	}

	CString QRCode;
	CMainFrame *ma = ((CMainFrame*)(AfxGetApp()->m_pMainWnd));
	QRCode.Append((char*)pQRCode, len);
	ma->ShowQR((char*)QRCode.GetString());

	ti.Stop();
	AfxMessageBox("正在刷新二维码");
	ti.show();

	com->SetReadTimeout(m2pQRCodeDisplay.ucTimeout);

	QR_Mid2Pc_PAY_TransResult m2p_TransResult;
	ti.Clear();
	ti.Start();
	len = com->Read(&m2p_TransResult, sizeof(m2p_TransResult));
	if (!len)
	{
		AfxMessageBox("读取交易结果失败");
		com->Close();
		return false;
	}
	ti.Stop();
	AfxMessageBox((char*)m2p_TransResult.aucTranResult);
	ti.show();
	com->Close();
	return true;
}

void QRData::QR_PAY_DisPlay(void *buffer, int len)
{
	//unsigned char c_send[] = "02024630B44732303030303030303030313530202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202003B2";
	//unsigned char c_send[512] = "020246353C202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202077656978696E3A2F2F77787061792F62697A70617975726C3F70723D5061366276326D2020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020200326";
	CString ss;
	ss.Append((char*)buffer, len);
	CByteArray ary;
	Str2Hex(ss, ary);

	ComConnect *com = new ComConnect();
	if (!com->Open())
	{
		com->Close();
		return;
	}
	for (int i = 0; i < ary.GetSize(); ++i)
	{
		com->Write(&ary[i], 1);
	}
	com->Close();

	void(*fun)(void*);
	fun = ThreadRead;
	_beginthread(fun, 0, NULL);
}

void QRData::QRTEXT()
{
	unsigned char c_send[] = "02024630B44732303030303030303030313530202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202020202003B2";
	CString ss;
	ss.Append((char*)c_send, strlen((char*)c_send));
	CByteArray ary;
	Str2Hex(ss, ary);
	BYTE *bt = ary.GetData();
	qrText qt;
	memcpy(&qt, (void*)bt, ary.GetSize());

	ComConnect *com = new ComConnect();
	if (!com->Open())
	{
		com->Close();
		return;
	}

	unsigned char *ps = (unsigned char*)&qt;
	for (int i = 0; i < ary.GetSize(); ++i)
	{
		com->Write(&ps[i], 1);
	}
	com->Close();

	ThreadRead(NULL);
}