#include "stdafx.h"
#include "QR_Timer.h"
#include <iostream>
#include <iomanip>
#include <sstream>

QR_Timer::QR_Timer()
{
	is_pause = false; //��ʼ����ʱ��״̬   
	is_stop = true;
}


QR_Timer::~QR_Timer()
{
}

bool QR_Timer::isPause()
{
	if (is_pause)
		return true;
	else
		return false;
}

bool QR_Timer::isStop()
{
	if (is_stop)
		return true;
	return false;
}

void QR_Timer::Start()
{
	if (is_stop)
	{
		start_time = time(0);
		is_stop = false;
	}
	else if (is_pause)
	{
		is_pause = false;
		start_time += time(0) - pause_time; //���¿�ʼʱ�䣺�ô�ʱ��ʱ�� - ��ͣʱ���õ�ʱ�� + ��һ�ο�ʼ��ʱ�� = ��ʱ�Ŀ�ʼʱ��   
	}
}

void QR_Timer::Pause()
{
	if (is_stop || is_pause) //�������ֹͣ/��ͣ״̬,�˶��������κδ���ֱ�ӷ���   
		return;
	else    //�������Ϊ��ͣ״̬  
	{
		is_pause = true;
		pause_time = time(0); //��ȡ��ͣʱ��   
	}
}

void QR_Timer::Stop()
{
	if (is_stop) //���������ֹͣ״̬��������ͣ״̬���������κδ���   
		return;
	else if (is_pause) //�ı��ʱ��״̬   
	{
		is_pause = false;
		is_stop = true;
	}
	else if (!is_stop)
	{
		is_stop = true;
	}
}

void QR_Timer::Clear()
{
	start_time = 0;
	pause_time = 0;
}

void QR_Timer::show()
{
	time_t t = time(0) - start_time;
	std::stringstream ss;
	ss << "����ʱ��:" << std::setw(2) << std::setfill('0') << t / 60 / 60 << ":"
		<< std::setw(2) << std::setfill('0') << t / 60 << ":"
		<< std::setw(2) << std::setfill('0') << t % 60 << std::endl;
	AfxMessageBox(ss.str().c_str());
}