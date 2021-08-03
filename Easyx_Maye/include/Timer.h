#pragma once
#include<ctime>
class Timer
{
public:
	Timer(clock_t ms = 0);
	void startTimer();
	bool timeOut();
	void setTime(clock_t ms);
	void killTimer();
public:
	//��̬��ʱ��
	static bool startTimer(clock_t ms, int id);
	//��ʱ�������ID
	inline static size_t maxTimerID() { return 20; };
private:
	clock_t m_ms;	//�ӳٺ�����
	clock_t m_startime;
	clock_t m_endtime;

	bool m_threadIsRun;	//�����߳�����
};

