#pragma once

#pragma pack(1)
//通信握手
struct QR_Pc2Mid_NET_HandShake
{
	unsigned char	ucStartFlag;				/*开始标志*/
	unsigned char	aucDataLength[2];			/*数据长度*/
	unsigned char	ucTranType;					/*交易类型*/
	unsigned char	ucTimeout;					/*超时时间*/
	unsigned char	aucPayType[2];				/*支付方式*/
	unsigned char	aucAmount[12];				/*支付金额*/
	unsigned char	aucPassword[32];			/*密码*/
	unsigned char	aucTraceNo[6];				/*原交易流水*/
	unsigned char	aucOriginalOrderNo[64];		/*原交易订单号*/
	unsigned char	aucQRCode[128];				/*二维码 微信或支付宝*/
	unsigned char	ucEndFlag;					/*结束标志*/
	unsigned char	ucAscCheck;					/*检校*/
};

//通信握手返回
struct QR_Mid2Pc_NET_HandShake
{
	unsigned char	ucStartFlag;				/*开始标志*/
	unsigned char	aucDataLength[2];			/*数据长度*/
	unsigned char	ucTranType;					/*交易类型*/
	unsigned char	aucTranResult[2];			/*交易结果*/
	unsigned char	aucInfo[40];				/*信息描述*/
	unsigned char	aucMerchantID[15];			/*商户号,ASCII码*/
	unsigned char	aucTerminalID[8];			/*终端号,ASCII码*/
	unsigned char	aucTransAmount[23];			/*交易金额*/
	unsigned char	aucCardNo[19];				/*交易卡号*/
	unsigned char	aucTraceNo[6];				/*流水号*/
	unsigned char	aucBatchNum[6];				/*批次号*/
	unsigned char	aucReferenceNum[12];		/*参考号*/
	unsigned char	aucAuthCode[6];				/*授权号*/
	unsigned char	aucTransTime[22];			/*交易时间*/
	unsigned char	aucChannel[32];				/*渠道*/
	unsigned char	aucAccount[64];				/*账号*/
	unsigned char	aucOrderInfo[64];			/*订单信息*/
	unsigned char	aucPaidAmount[12];			/*实付金额*/
	unsigned char	aucNoDiscountAmount[12];	/*不可打折金额*/
	unsigned char	ucEndFlag;					/*结束标志*/
	unsigned char	ucAscCheck;					/*检校*/
};

//管理,签到
struct QR_Pc2Mid_NET_SignIn
{
	unsigned char	ucStartFlag;				/*开始标志*/
	unsigned char	aucDataLength[2];			/*数据长度*/
	unsigned char	ucTranType;					/*交易类型*/
	unsigned char	ucTimeout;					/*超时时间*/
	unsigned char	aucPayType[2];				/*支付方式*/
	unsigned char	aucAmount[12];				/*支付金额*/
	unsigned char	aucPassword[32];			/*密码*/
	unsigned char	aucOriginalTraceNo[6];		/*原交易流水*/
	unsigned char	aucOriginalOrderNo[64];		/*原交易订单号*/
	unsigned char	aucQRCode[128];				/*二维码 微信或支付宝*/
	unsigned char	ucEndFlag;					/*结束标志*/
	unsigned char	ucAscCheck;					/*检校*/

};

//签到返回
struct QR_Mid2Pc_NET_SignIn
{
	unsigned char	ucStartFlag;				/*开始标志*/
	unsigned char	aucDataLength[2];			/*数据长度*/
	unsigned char	ucTranType;					/*交易类型*/
	unsigned char	aucTranResult[2];			/*交易结果*/
	unsigned char	aucInfo[40];				/*信息描述*/
	unsigned char	aucPayType[2];				/*支付方式*/
	unsigned char	aucMerchantID[15];			/*商户号,ASCII码*/
	unsigned char	aucTerminalID[8];			/*终端号,ASCII码*/
	unsigned char	aucTransAmount[23];			/*交易金额*/
	unsigned char	aucCardNo[19];				/*交易卡号*/
	unsigned char	aucTraceNo[6];				/*流水号*/
	unsigned char	aucBatchNum[6];				/*批次号*/
	unsigned char	aucReferenceNum[12];		/*参考号*/
	unsigned char	aucAuthCode[6];				/*授权号*/
	unsigned char	aucTransTime[22];			/*交易时间*/
	unsigned char	aucChannel[32];				/*渠道*/
	unsigned char	aucAccount[64];				/*账号*/
	unsigned char	aucOrderInfo[64];			/*订单信息*/
	unsigned char	aucPaidAmount[12];			/*实付金额*/
	unsigned char	aucNoDiscountAmount[12];	/*不可打折金额*/
	unsigned char	aucDiscountAmount[12];		/*可打折金额*/
	unsigned char	ucEndFlag;					/*结束标志*/
	unsigned char	ucAscCheck;					/*检校*/

};


//支付环节
//握手
struct QR_Pc2Mid_PAY_HandShake
{
	unsigned char	ucStartFlag;				/*开始标志*/
	unsigned char	aucDataLength[2];			/*数据长度*/
	unsigned char	ucTranType;					/*交易类型*/
	unsigned char	ucTimeout;					/*超时时间*/
	unsigned char	aucPayType[2];				/*支付方式*/
	unsigned char	aucAmount[12];				/*支付金额*/
	unsigned char	aucPassword[32];			/*密码*/
	unsigned char	aucOriginalTraceNo[6];		/*原交易流水*/
	unsigned char	aucOriginalOrderNo[64];		/*原交易订单号*/
	unsigned char	aucQRCode[128];				/*二维码 微信或支付宝*/
	unsigned char	ucEndFlag;					/*结束标志*/
	unsigned char	ucAscCheck;					/*检校*/
};

struct QR_Mid2Pc_PAY_HandShake
{
	unsigned char	ucStartFlag;				/*开始标志*/
	unsigned char	aucDataLength[2];			/*数据长度*/
	unsigned char	ucTranType;					/*交易类型*/
	unsigned char	aucTranResult[2];			/*交易结果*/
	unsigned char	aucInfo[40];				/*信息描述*/
	unsigned char	aucPayType[2];				/*支付方式*/
	unsigned char	aucMerchantID[15];			/*商户号,ASCII码*/
	unsigned char	aucTerminalID[8];			/*终端号,ASCII码*/
	unsigned char	aucTransAmount[23];			/*交易金额*/
	unsigned char	aucCardNo[19];				/*交易卡号*/
	unsigned char	aucTraceNo[6];				/*流水号*/
	unsigned char	aucBatchNum[6];				/*批次号*/
	unsigned char	aucReferenceNum[12];		/*参考号*/
	unsigned char	aucAuthCode[6];				/*授权号*/
	unsigned char	aucTransTime[22];			/*交易时间*/
	unsigned char	aucChannel[32];				/*渠道*/
	unsigned char	aucAccount[64];				/*账号*/
	unsigned char	aucOrderInfo[64];			/*订单信息*/
	unsigned char	aucPaidAmount[12];			/*实付金额*/
	unsigned char	aucNoDiscountAmount[12];	/*不可打折金额*/
	unsigned char	aucDiscountAmount[12];		/*可打折金额*/
	unsigned char	ucEndFlag;					/*结束标志*/
	unsigned char	ucAscCheck;					/*检校*/
};

struct QR_Pc2Mid_PAY_TransAsk
{
	unsigned char	ucStartFlag;				/*开始标志*/
	unsigned char	aucDataLength[2];			/*数据长度*/
	unsigned char	ucTranType;					/*交易类型*/
	unsigned char	ucTimeout;					/*超时时间*/
	unsigned char	aucPayType[2];				/*支付方式*/
	unsigned char	aucAmount[12];				/*支付金额*/
	unsigned char	aucPassword[32];			/*密码*/
	unsigned char	aucOriginalTraceNo[6];		/*原交易流水*/
	unsigned char	aucOriginalOrderNo[64];		/*原交易订单号*/
	unsigned char	aucQRCode[128];				/*二维码 微信或支付宝*/
	unsigned char	ucEndFlag;					/*结束标志*/
	unsigned char	ucAscCheck;					/*检校*/
};

struct QR_Mid2Pc_PAY_QRCodeDisplay
{
	unsigned char	ucStartFlag;				/*开始标志*/
	unsigned char	aucDataLength[2];			/*数据长度*/
	unsigned char	ucTranType;					/*交易类型*/
	unsigned char	ucTimeout;					/*超时时间*/
	unsigned char	aucPayType[2];				/*支付方式*/
	unsigned char	aucAmount[12];				/*支付金额*/
	unsigned char	aucPassword[32];			/*密码*/
	unsigned char	aucOriginalTraceNo[6];		/*原交易流水*/
	unsigned char	aucOriginalOrderNo[64];		/*原交易订单号*/
	unsigned char	aucQRCode[128];				/*二维码 微信或支付宝*/
	unsigned char	ucEndFlag;					/*结束标志*/
	unsigned char	ucAscCheck;					/*检校*/
};

struct QR_Mid2Pc_PAY_TransResult
{
	unsigned char	ucStartFlag;				/*开始标志*/
	unsigned char	aucDataLength[2];			/*数据长度*/
	unsigned char	ucTranType;					/*交易类型*/
	unsigned char	aucTranResult[2];			/*交易结果*/
	unsigned char	aucInfo[40];				/*信息描述*/
	unsigned char	aucPayType[2];				/*支付方式*/
	unsigned char	aucMerchantID[15];			/*商户号,ASCII码*/
	unsigned char	aucTerminalID[8];			/*终端号,ASCII码*/
	unsigned char	aucTransAmount[23];			/*交易金额*/
	unsigned char	aucCardNo[19];				/*交易卡号*/
	unsigned char	aucTraceNo[6];				/*流水号*/
	unsigned char	aucBatchNum[6];				/*批次号*/
	unsigned char	aucReferenceNum[12];		/*参考号*/
	unsigned char	aucAuthCode[6];				/*授权号*/
	unsigned char	aucTransTime[22];			/*交易时间*/
	unsigned char	aucChannel[32];				/*渠道*/
	unsigned char	aucAccount[64];				/*账号*/
	unsigned char	aucOrderInfo[64];			/*订单信息*/
	unsigned char	aucPaidAmount[12];			/*实付金额*/
	unsigned char	aucNoDiscountAmount[12];	/*不可打折金额*/
	unsigned char	aucDiscountAmount[12];		/*可打折金额*/
	unsigned char	ucEndFlag;					/*结束标志*/
	unsigned char	ucAscCheck;					/*检校*/
};

struct QRWeixin
{
	unsigned char ucStart;
	unsigned char aucDataLen[2];
	unsigned char ucTranType;
	unsigned char ucTimeout;
	unsigned char aucPayType[2];
	unsigned char aucAmount[12];
	unsigned char aucPassword[32];
	unsigned char aucCurTrace[6];
	unsigned char aucOrder[64];
	unsigned char aucQR[128];
	unsigned char ucEnd;
	unsigned char ucAuc;
};//251
#pragma pack()