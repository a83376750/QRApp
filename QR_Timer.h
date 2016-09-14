#pragma once
class QR_Timer
{
public:
	QR_Timer();
	~QR_Timer();

private:
	time_t start_time;
	time_t pause_time;

	//两个bool值标记四种状态   
	bool is_pause; //记录计时器的状态 （是否处于暂停状态）  
	bool is_stop;//是否处于停止状态   
public:
	bool isPause(); //返回计时器状态   
	bool isStop();

	//计时器的三种动作（功能）   
	void Start();
	void Pause();
	void Stop();
	void Clear();

	inline time_t getStartTime() { return start_time; }

	void show();
};

