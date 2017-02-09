#pragma once

#include <functional>

/*
	TimerManager��Tickerʵ����ʱ�Ӷ�ʱ���ܣ�����һ��ʱ��󴥷��ص�����callback��ref ��https://www.zhihu.com/question/19801131��
	ʵ�ֺ������ӳٵ��ã������������ģ��Ϊ������ϵͳ���Ǿ�����ʹ�õĹ���
*/

/*
	���TimerManager��Ticker��ʵ�֣�
		1.���TimerManager��delay���ܣ��������Ҫ����������
		2.���Ticker��ʵ��
*/


/*
	ticker��ÿ��һ��ʱ�����һ�λص�����
*/
class Ticker {
public:
	Ticker(std::function<void(void)> func);						//��ĳ���ص���������Ticker
	void setCallback(std::function<void(void)> func);		//���ûص�����
	void start(time_t milisecond);										//����ticker
};


class TimerManager {
public:
	//�ӳ�milisecond����֮�����func����
	static void delay(std::function<void(void)> func, time_t milisecond);			//ͨ��lambda���ʽʵ�ָ��ӵĻص�����
};

