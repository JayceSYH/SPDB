#pragma once

/*
    TableManager是数据库表管理类，任何对表结构或表项的操作都需要通过该类
    反映到物理层面（通过在“合适的时机”合理调用BaseLayer中实现的接口实现）

    鉴于文件IO实践开销特别大在进行诸如Entry的插入删除的操作时TableManager
    并不会马上调用BaseLayer的接口进行文件读写，而是在一定时间后（比如每过10s）
    进行一次操作，从而保证了数据库的运行效率，本实验中以10s作为间隔进行
    文件的读写（如果是对表结构进行操作则是立即执行文件读写）

    Tips：TableManager 需采用单例模式，以vector<Table>为参数进行构造，通过使用
    线程锁保证线程安全
*/


/*
    实现TableManager：
        1.实现对表的管理
        2.通过BaseLayer的接口实现将Table写到数据库的接口
        3.实现定时调用BaseLayer的接口对数据进行写回到数据库文件
*/


#define TIME_SEP_IN_SECOND 10

class TableManager {

};