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
    Ticker(std::function<void(void)> func);                     //以某个回调函数创建Ticker
    void setCallback(std::function<void(void)> func);       //设置回调函数
    void start(time_t milisecond);                                      //启动ticker
};


class TimerManager {
private:
    static TaskQueue taskQueue;
public:
    //延迟milisecond毫秒之后调用func函数
    static void delay(std::function<void(void)> func, time_t milisecond);           //通过lambda表达式实现复杂的回调函数
};


//注意该类需持有一个线程锁来保证个线程在同时添加任务时不会出现错误
class TaskQueue {
private:
    /*
        处理所有处理时间小于等于该时刻的函数，注意每次执行完一个函数之后都
        要进行时间判断
    */
    void callFuncs();

    //TODO:添加成员
    //Tips:一个用来存储任务的容器，便于添加任务；一个线程锁用来保证线程安全
public:
    //在绝对时刻time之后调用func(想想为什么是之后)
    void newTask(std::function<void(void)> func, time_t time);

    //TODO:添加成员
};
/*
    Note:思考一下，假如有1000个任务，每个任务之间的时间间隔都很小（假设为1ms），
    如果每次执行完一个任务都要挂起等待下一次执行，那么为了执行这些人物可能会进行
    大量的线程切换，怎么设计TaskQueue才能使得这一系列的任务执行效率得到提高？
*/
