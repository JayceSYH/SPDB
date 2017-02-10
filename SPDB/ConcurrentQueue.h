#pragma once

/*
    实现下面的线程安全队列
*/

/*
    ConcurrentQueue实现了线程安全的队列，通过使用mutex
    或者CAS来实现（推荐CAS）
*/
template<typename T>
class ConcurrentQueue {

};