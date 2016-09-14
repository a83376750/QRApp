#pragma once
class QR_Timer
{
public:
	QR_Timer();
	~QR_Timer();

private:
	time_t start_time;
	time_t pause_time;

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
	void Clear();

	inline time_t getStartTime() { return start_time; }

	void show();
};

