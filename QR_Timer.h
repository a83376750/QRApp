#pragma once
class QR_Timer
{
public:
	QR_Timer();
	~QR_Timer();

private:
	long start_time;
	long pause_time;

	//����boolֵ�������״̬   
	bool is_pause; //��¼��ʱ����״̬ ���Ƿ�����ͣ״̬��  
	bool is_stop;//�Ƿ���ֹͣ״̬   
public:
	bool isPause(); //���ؼ�ʱ��״̬   
	bool isStop();

	//��ʱ�������ֶ��������ܣ�   
	void Start();
	void Pause();
	void Stop();

	inline long getStartTime() { return start_time; }

	void show();
};

