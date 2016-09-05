#pragma once

#pragma pack(1)
//ͨ������
struct QR_Pc2Mid_NET_HandShake
{
	unsigned char	ucStartFlag;				/*��ʼ��־*/
	unsigned char	aucDataLength[2];			/*���ݳ���*/
	unsigned char	ucTranType;					/*��������*/
	unsigned char	ucTimeout;					/*��ʱʱ��*/
	unsigned char	aucPayType[2];				/*֧����ʽ*/
	unsigned char	aucAmount[12];				/*֧�����*/
	unsigned char	aucPassword[32];			/*����*/
	unsigned char	aucTraceNo[6];				/*ԭ������ˮ*/
	unsigned char	aucOriginalOrderNo[64];		/*ԭ���׶�����*/
	unsigned char	aucQRCode[128];				/*��ά�� ΢�Ż�֧����*/
	unsigned char	ucEndFlag;					/*������־*/
	unsigned char	ucAscCheck;					/*��У*/
};

//ͨ�����ַ���
struct QR_Mid2Pc_NET_HandShake
{
	unsigned char	ucStartFlag;				/*��ʼ��־*/
	unsigned char	aucDataLength[2];			/*���ݳ���*/
	unsigned char	ucTranType;					/*��������*/
	unsigned char	aucTranResult[2];			/*���׽��*/
	unsigned char	aucInfo[40];				/*��Ϣ����*/
	unsigned char	aucMerchantID[15];			/*�̻���,ASCII��*/
	unsigned char	aucTerminalID[8];			/*�ն˺�,ASCII��*/
	unsigned char	aucTransAmount[23];			/*���׽��*/
	unsigned char	aucCardNo[19];				/*���׿���*/
	unsigned char	aucTraceNo[6];				/*��ˮ��*/
	unsigned char	aucBatchNum[6];				/*���κ�*/
	unsigned char	aucReferenceNum[12];		/*�ο���*/
	unsigned char	aucAuthCode[6];				/*��Ȩ��*/
	unsigned char	aucTransTime[22];			/*����ʱ��*/
	unsigned char	aucChannel[32];				/*����*/
	unsigned char	aucAccount[64];				/*�˺�*/
	unsigned char	aucOrderInfo[64];			/*������Ϣ*/
	unsigned char	aucPaidAmount[12];			/*ʵ�����*/
	unsigned char	aucNoDiscountAmount[12];	/*���ɴ��۽��*/
	unsigned char	ucEndFlag;					/*������־*/
	unsigned char	ucAscCheck;					/*��У*/
};

//����,ǩ��
struct QR_Pc2Mid_NET_SignIn
{
	unsigned char	ucStartFlag;				/*��ʼ��־*/
	unsigned char	aucDataLength[2];			/*���ݳ���*/
	unsigned char	ucTranType;					/*��������*/
	unsigned char	ucTimeout;					/*��ʱʱ��*/
	unsigned char	aucPayType[2];				/*֧����ʽ*/
	unsigned char	aucAmount[12];				/*֧�����*/
	unsigned char	aucPassword[32];			/*����*/
	unsigned char	aucOriginalTraceNo[6];		/*ԭ������ˮ*/
	unsigned char	aucOriginalOrderNo[64];		/*ԭ���׶�����*/
	unsigned char	aucQRCode[128];				/*��ά�� ΢�Ż�֧����*/
	unsigned char	ucEndFlag;					/*������־*/
	unsigned char	ucAscCheck;					/*��У*/

};

//ǩ������
struct QR_Mid2Pc_NET_SignIn
{
	unsigned char	ucStartFlag;				/*��ʼ��־*/
	unsigned char	aucDataLength[2];			/*���ݳ���*/
	unsigned char	ucTranType;					/*��������*/
	unsigned char	aucTranResult[2];			/*���׽��*/
	unsigned char	aucInfo[40];				/*��Ϣ����*/
	unsigned char	aucPayType[2];				/*֧����ʽ*/
	unsigned char	aucMerchantID[15];			/*�̻���,ASCII��*/
	unsigned char	aucTerminalID[8];			/*�ն˺�,ASCII��*/
	unsigned char	aucTransAmount[23];			/*���׽��*/
	unsigned char	aucCardNo[19];				/*���׿���*/
	unsigned char	aucTraceNo[6];				/*��ˮ��*/
	unsigned char	aucBatchNum[6];				/*���κ�*/
	unsigned char	aucReferenceNum[12];		/*�ο���*/
	unsigned char	aucAuthCode[6];				/*��Ȩ��*/
	unsigned char	aucTransTime[22];			/*����ʱ��*/
	unsigned char	aucChannel[32];				/*����*/
	unsigned char	aucAccount[64];				/*�˺�*/
	unsigned char	aucOrderInfo[64];			/*������Ϣ*/
	unsigned char	aucPaidAmount[12];			/*ʵ�����*/
	unsigned char	aucNoDiscountAmount[12];	/*���ɴ��۽��*/
	unsigned char	aucDiscountAmount[12];		/*�ɴ��۽��*/
	unsigned char	ucEndFlag;					/*������־*/
	unsigned char	ucAscCheck;					/*��У*/

};


//֧������
//����
struct QR_Pc2Mid_PAY_HandShake
{
	unsigned char	ucStartFlag;				/*��ʼ��־*/
	unsigned char	aucDataLength[2];			/*���ݳ���*/
	unsigned char	ucTranType;					/*��������*/
	unsigned char	ucTimeout;					/*��ʱʱ��*/
	unsigned char	aucPayType[2];				/*֧����ʽ*/
	unsigned char	aucAmount[12];				/*֧�����*/
	unsigned char	aucPassword[32];			/*����*/
	unsigned char	aucOriginalTraceNo[6];		/*ԭ������ˮ*/
	unsigned char	aucOriginalOrderNo[64];		/*ԭ���׶�����*/
	unsigned char	aucQRCode[128];				/*��ά�� ΢�Ż�֧����*/
	unsigned char	ucEndFlag;					/*������־*/
	unsigned char	ucAscCheck;					/*��У*/
};

struct QR_Mid2Pc_PAY_HandShake
{
	unsigned char	ucStartFlag;				/*��ʼ��־*/
	unsigned char	aucDataLength[2];			/*���ݳ���*/
	unsigned char	ucTranType;					/*��������*/
	unsigned char	aucTranResult[2];			/*���׽��*/
	unsigned char	aucInfo[40];				/*��Ϣ����*/
	unsigned char	aucPayType[2];				/*֧����ʽ*/
	unsigned char	aucMerchantID[15];			/*�̻���,ASCII��*/
	unsigned char	aucTerminalID[8];			/*�ն˺�,ASCII��*/
	unsigned char	aucTransAmount[23];			/*���׽��*/
	unsigned char	aucCardNo[19];				/*���׿���*/
	unsigned char	aucTraceNo[6];				/*��ˮ��*/
	unsigned char	aucBatchNum[6];				/*���κ�*/
	unsigned char	aucReferenceNum[12];		/*�ο���*/
	unsigned char	aucAuthCode[6];				/*��Ȩ��*/
	unsigned char	aucTransTime[22];			/*����ʱ��*/
	unsigned char	aucChannel[32];				/*����*/
	unsigned char	aucAccount[64];				/*�˺�*/
	unsigned char	aucOrderInfo[64];			/*������Ϣ*/
	unsigned char	aucPaidAmount[12];			/*ʵ�����*/
	unsigned char	aucNoDiscountAmount[12];	/*���ɴ��۽��*/
	unsigned char	aucDiscountAmount[12];		/*�ɴ��۽��*/
	unsigned char	ucEndFlag;					/*������־*/
	unsigned char	ucAscCheck;					/*��У*/
};

struct QR_Pc2Mid_PAY_TransAsk
{
	unsigned char	ucStartFlag;				/*��ʼ��־*/
	unsigned char	aucDataLength[2];			/*���ݳ���*/
	unsigned char	ucTranType;					/*��������*/
	unsigned char	ucTimeout;					/*��ʱʱ��*/
	unsigned char	aucPayType[2];				/*֧����ʽ*/
	unsigned char	aucAmount[12];				/*֧�����*/
	unsigned char	aucPassword[32];			/*����*/
	unsigned char	aucOriginalTraceNo[6];		/*ԭ������ˮ*/
	unsigned char	aucOriginalOrderNo[64];		/*ԭ���׶�����*/
	unsigned char	aucQRCode[128];				/*��ά�� ΢�Ż�֧����*/
	unsigned char	ucEndFlag;					/*������־*/
	unsigned char	ucAscCheck;					/*��У*/
};

struct QR_Mid2Pc_PAY_QRCodeDisplay
{
	unsigned char	ucStartFlag;				/*��ʼ��־*/
	unsigned char	aucDataLength[2];			/*���ݳ���*/
	unsigned char	ucTranType;					/*��������*/
	unsigned char	ucTimeout;					/*��ʱʱ��*/
	unsigned char	aucPayType[2];				/*֧����ʽ*/
	unsigned char	aucAmount[12];				/*֧�����*/
	unsigned char	aucPassword[32];			/*����*/
	unsigned char	aucOriginalTraceNo[6];		/*ԭ������ˮ*/
	unsigned char	aucOriginalOrderNo[64];		/*ԭ���׶�����*/
	unsigned char	aucQRCode[128];				/*��ά�� ΢�Ż�֧����*/
	unsigned char	ucEndFlag;					/*������־*/
	unsigned char	ucAscCheck;					/*��У*/
};

struct QR_Mid2Pc_PAY_TransResult
{
	unsigned char	ucStartFlag;				/*��ʼ��־*/
	unsigned char	aucDataLength[2];			/*���ݳ���*/
	unsigned char	ucTranType;					/*��������*/
	unsigned char	aucTranResult[2];			/*���׽��*/
	unsigned char	aucInfo[40];				/*��Ϣ����*/
	unsigned char	aucPayType[2];				/*֧����ʽ*/
	unsigned char	aucMerchantID[15];			/*�̻���,ASCII��*/
	unsigned char	aucTerminalID[8];			/*�ն˺�,ASCII��*/
	unsigned char	aucTransAmount[23];			/*���׽��*/
	unsigned char	aucCardNo[19];				/*���׿���*/
	unsigned char	aucTraceNo[6];				/*��ˮ��*/
	unsigned char	aucBatchNum[6];				/*���κ�*/
	unsigned char	aucReferenceNum[12];		/*�ο���*/
	unsigned char	aucAuthCode[6];				/*��Ȩ��*/
	unsigned char	aucTransTime[22];			/*����ʱ��*/
	unsigned char	aucChannel[32];				/*����*/
	unsigned char	aucAccount[64];				/*�˺�*/
	unsigned char	aucOrderInfo[64];			/*������Ϣ*/
	unsigned char	aucPaidAmount[12];			/*ʵ�����*/
	unsigned char	aucNoDiscountAmount[12];	/*���ɴ��۽��*/
	unsigned char	aucDiscountAmount[12];		/*�ɴ��۽��*/
	unsigned char	ucEndFlag;					/*������־*/
	unsigned char	ucAscCheck;					/*��У*/
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