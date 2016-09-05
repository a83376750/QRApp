// QR_Encode.h : CQR_Encode类声明和接口定义
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#if !defined(AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_)
#define AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// 常数

// 纠错级别
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

// 数据模式
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3

// 版本（型号）集团
#define QR_VRESION_S	0 // 1 ~ 9
#define QR_VRESION_M	1 // 10 ~ 26
#define QR_VRESION_L	2 // 27 ~ 40

#define MAX_ALLCODEWORD	 3706 // 总代码字数最大值
#define MAX_DATACODEWORD 2956 // 数据编码字最大值（40）- L版本)
#define MAX_CODEBLOCK	  153 // 块数据编码字数最大值（RS代码字在内）
#define MAX_MODULESIZE	  177 // 一边模块数最大值

// 绘制位图的空白余量
#define QR_MARGIN	4


/////////////////////////////////////////////////////////////////////////////
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		// RS块数
	int ncAllCodeWord;	// 区块代码字数
	int ncDataCodeWord;	// 数据编码字数（代码字数- RS代码字数）
} RS_BLOCKINFO, *LPRS_BLOCKINFO;


/////////////////////////////////////////////////////////////////////////////
// QR版本（型号）相关信息

typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // 版本（型号）号码（1～40）
	int ncAllCodeWord; // 总代码字数

	// 以下排列下标是错误修正率（0 = L，1，2 = = M Q为期3 = H） 
	int ncDataCodeWord[4];	// 数据编码字数（总代码字数- RS代码字数）

	int ncAlignPoint;	// 对准模式坐标数
	int nAlignPoint[6];	//对准模式中心座标
	RS_BLOCKINFO RS_BlockInfo1[4]; // RS块信息（1）
	RS_BLOCKINFO RS_BlockInfo2[4]; // RS块信息（2）

} QR_VERSIONINFO, *LPQR_VERSIONINFO;


/////////////////////////////////////////////////////////////////////////////
// CQR _ Encode班

class CQR_Encode
{
// 消灭构筑
public:
	CQR_Encode();
	~CQR_Encode();

public:
	int m_nLevel;		// 纠错级别
	int m_nVersion;		// 版本（型号）
	BOOL m_bAutoExtent;	// 版本（型号）自动扩展指定转折点
	int m_nMaskingNo;	// 掩蔽模式号码

public:
	int m_nSymbleSize;
	BYTE m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // [x][y]
	// bit5:功能模块（遮蔽对象外）转折点/ /功能模块（掩模除外）标志
	// bit4:功能模块绘图数据/ /功能能模仿块绘图数据
	// bit1:编码数据
	// bit0:面具后编码数据/ /绘画
	// 20 h的逻辑和更功能模块判定，11 h的逻辑和更绘图（最终BOOL值化）

private:
	int m_ncDataCodeWordBit; // 数据编码字位长
	BYTE m_byDataCodeWord[MAX_DATACODEWORD]; //输入数据编码区
	int m_ncDataBlock;
	BYTE m_byBlockMode[MAX_DATACODEWORD];
	int m_nBlockLength[MAX_DATACODEWORD];

	int m_ncAllCodeWord; // 总代码字数（RS错误修正数据在内）
	BYTE m_byAllCodeWord[MAX_ALLCODEWORD]; // 总代码字计算区域
	BYTE m_byRSWork[MAX_CODEBLOCK]; // RS代码字算出ー
//数据编码相关函数
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

// 模块布局相关函数
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
