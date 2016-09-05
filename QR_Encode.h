// QR_Encode.h : CQR_Encode�������ͽӿڶ���
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#if !defined(AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_)
#define AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// ����

// ������
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

// ����ģʽ
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3

// �汾���ͺţ�����
#define QR_VRESION_S	0 // 1 ~ 9
#define QR_VRESION_M	1 // 10 ~ 26
#define QR_VRESION_L	2 // 27 ~ 40

#define MAX_ALLCODEWORD	 3706 // �ܴ����������ֵ
#define MAX_DATACODEWORD 2956 // ���ݱ��������ֵ��40��- L�汾)
#define MAX_CODEBLOCK	  153 // �����ݱ����������ֵ��RS���������ڣ�
#define MAX_MODULESIZE	  177 // һ��ģ�������ֵ

// ����λͼ�Ŀհ�����
#define QR_MARGIN	4


/////////////////////////////////////////////////////////////////////////////
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		// RS����
	int ncAllCodeWord;	// �����������
	int ncDataCodeWord;	// ���ݱ�����������������- RS����������
} RS_BLOCKINFO, *LPRS_BLOCKINFO;


/////////////////////////////////////////////////////////////////////////////
// QR�汾���ͺţ������Ϣ

typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // �汾���ͺţ����루1��40��
	int ncAllCodeWord; // �ܴ�������

	// ���������±��Ǵ��������ʣ�0 = L��1��2 = = M QΪ��3 = H�� 
	int ncDataCodeWord[4];	// ���ݱ����������ܴ�������- RS����������

	int ncAlignPoint;	// ��׼ģʽ������
	int nAlignPoint[6];	//��׼ģʽ��������
	RS_BLOCKINFO RS_BlockInfo1[4]; // RS����Ϣ��1��
	RS_BLOCKINFO RS_BlockInfo2[4]; // RS����Ϣ��2��

} QR_VERSIONINFO, *LPQR_VERSIONINFO;


/////////////////////////////////////////////////////////////////////////////
// CQR _ Encode��

class CQR_Encode
{
// ������
public:
	CQR_Encode();
	~CQR_Encode();

public:
	int m_nLevel;		// ������
	int m_nVersion;		// �汾���ͺţ�
	BOOL m_bAutoExtent;	// �汾���ͺţ��Զ���չָ��ת�۵�
	int m_nMaskingNo;	// �ڱ�ģʽ����

public:
	int m_nSymbleSize;
	BYTE m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // [x][y]
	// bit5:����ģ�飨�ڱζ����⣩ת�۵�/ /����ģ�飨��ģ���⣩��־
	// bit4:����ģ���ͼ����/ /������ģ�¿��ͼ����
	// bit1:��������
	// bit0:��ߺ��������/ /�滭
	// 20 h���߼��͸�����ģ���ж���11 h���߼��͸���ͼ������BOOLֵ����

private:
	int m_ncDataCodeWordBit; // ���ݱ�����λ��
	BYTE m_byDataCodeWord[MAX_DATACODEWORD]; //�������ݱ�����
	int m_ncDataBlock;
	BYTE m_byBlockMode[MAX_DATACODEWORD];
	int m_nBlockLength[MAX_DATACODEWORD];

	int m_ncAllCodeWord; // �ܴ���������RS���������������ڣ�
	BYTE m_byAllCodeWord[MAX_ALLCODEWORD]; // �ܴ����ּ�������
	BYTE m_byRSWork[MAX_CODEBLOCK]; // RS����������`
//���ݱ�����غ���
public:
	BOOL EncodeData(int nLevel, int nVersion, BOOL bAutoExtent, int nMaskingNo, LPCSTR lpsSource, int ncSource = 0);

private:
	int GetEncodeVersion(int nVersion, LPCSTR lpsSource, int ncLength);
	BOOL EncodeSourceData(LPCSTR lpsSource, int ncLength, int nVerGroup);

	int GetBitLength(BYTE nMode, int ncData, int nVerGroup);

	int SetBitStream(int nIndex, WORD wData, int ncData);

	BOOL IsNumeralData(unsigned char c);
	BOOL IsAlphabetData(unsigned char c);
	BOOL IsKanjiData(unsigned char c1, unsigned char c2);

	BYTE AlphabetToBinaly(unsigned char c);
	WORD KanjiToBinaly(WORD wc);

	void GetRSCodeWord(LPBYTE lpbyRSWork, int ncDataCodeWord, int ncRSCodeWord);

// ģ�鲼����غ���
private:
	void FormatModule();

	void SetFunctionModule();
	void SetFinderPattern(int x, int y);
	void SetAlignmentPattern(int x, int y);
	void SetVersionPattern();
	void SetCodeWordPattern();
	void SetMaskingPattern(int nPatternNo);
	void SetFormatInfoPattern(int nPatternNo);
	int CountPenalty();
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_)
