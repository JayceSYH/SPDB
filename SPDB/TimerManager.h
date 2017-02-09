#pragma once

#include <functional>

/*
	TimerManager、Ticker实现了时钟定时功能，能在一定时间后触发回调函数callback（ref ：https://www.zhihu.com/question/19801131）
	实现函数的延迟调用，在以任务队列模型为基础的系统中是经常会使用的工具
*/

/*
	完成TimerManager和Ticker的实现：
		1.完成TimerManager的delay功能，并添加需要的其他功能
		2.完成Ticker的实现
*/


/*
	ticker会每个一定时间调用一次回调函数
*/
class Ticker {
public:
	Ticker(std::function<void(void)> func);						//以某个回调函数创建Ticker
	void setCallback(std::function<void(void)> func);		//设置回调函数
	void start(time_t milisecond);										//启动ticker
};


class TimerManager {
public:
	//延迟milisecond毫秒之后调用func函数
	static void delay(std::function<void(void)> func, time_t milisecond);			//通过lambda表达式实现复杂的回调函数
};

