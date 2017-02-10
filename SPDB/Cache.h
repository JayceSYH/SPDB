#pragma once

#include<unordered_map>
#include<string>


/*
    TODO：
        1.实现CacheProperty，完成锁的相关实现
        2.完成CacheContent的实现，实现对缓存内容的操作
        3.完成对Cache的实现，实现对缓存内容的存取、删改
        4.设置Cache的锁的模式
*/


/*
    CacheProperty持有了每个cachecontent的锁，并实现锁相关的方法保证Cache读写的线程安全性
*/
class CacheProperty {
    //TODO：添加读写锁以及读写锁相关操作，注意要统一悲观锁和乐观锁（即加了一种锁之后，解锁前不能加另一种锁）

public:

    /***********悲观锁***********/
    /*（ref：mutex，http://www.cnblogs.com/haippy/p/3237213.html ）*/
    //读锁加锁
    void rlock();
    //读锁解锁
    void runlock();

    //写锁加锁
    void wlock();
    //写锁解锁
    void wunlock();


    /***************乐观锁****************/
    /*（ref：CAS操作、http://blog.csdn.net/syzcch/article/details/8075830 ）*/
    ////读锁加锁
    void atomic_rlock();
    //读锁解锁
    void atomic_runlock();

    //写锁加锁
    void atomic_wlock();
    //写锁解锁
    void atomic_wunlock();
};


/*
    CacheContent是Cache的内容，封装了内容变量T和相关的锁来保证多线程访问的安全
    Note：
        1.可以通过添加构造函数、添加setMode函数设置锁的类型（悲观锁、乐观锁、不加锁），使用默认参数可以简化函数调用
*/
template<typename T>
class CacheContent {
private:
    CacheProperty cproperty;
    T* content;
public:
    //直接将指针作为content
    CacheContent(T*);
    //复制内容作为content
    CacheContent(T&&);

    //获取内容
    T& getContent();
    //修改内容
    void setContent(T*);
    void setContent(T&&);

    //TODO:添加其他成员
};


/*
    Cache实现了像map一样对Cache内容进行操作，并对cache内容进行
    存取、删改。通过在构造函数中添加参数或者添加set函数可以修改
    Cache Mode（悲观锁、乐观锁、不加锁等）
*/
template<typename K, typename T>
class Cache {
private:
    std::unordered_map<K, CacheContent<T>> content;

public:
    //使用[]操作符访问content
    T& operator[](K& key);
    //以指针内容作为content
    void put(K&, T*);
    //删除内容
    void remove(K&);

    //TODO:添加其他成员
};



/********************OPTIONAL*********************/
//Mode的设计

/*
    mode一般可以用两种方式定义：
        1.枚举类型
            enum Mode { Mode1, Mode2, ....... }
            enum Mode { Mode1 = xxx, Mode2 = xxx, .......}
        2.宏定义
            #define Mode1 xxx
            #define Mode2 xxx

    多维度模式的定义技巧：
        假定我们要设计一个窗体的模式，须在三个维度上定义--形状、颜色、边框样式不同的模式：
            #define 三角形 0x1
            #define 正方形 0x2
            #define 菱形 0x3

            #define 红色 0x4
            #define 绿色 0x8
            #define 黄色 0xc

            #define 细边 0x10
            #define 粗边 0x20

            那么一个正方形红色粗边的窗体模式就是：(正方形 | 红色 | 粗边) 
            显然，其实利用了不同维度使用不同位置的bit来表示多维度的模式
            形状使用了前2位，颜色使用了3~4位，边框使用了5~6位，这样使用模式
            既直观又简单。相应的，在判断一个窗体是否是红色时可以使用以下方法：
                        （mode & 红色 == 红色）
*/