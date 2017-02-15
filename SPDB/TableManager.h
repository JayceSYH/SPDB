#pragma once

#include "Cache.h"
#include "DBModel.h"
#include <string>

/*
    TableManager是数据库表管理类，任何对表结构或表项的操作都需要通过该类
    反映到物理层面（通过在“合适的时机”合理调用BaseLayer中实现的接口实现）
*/


/*
    实现TableManager：
        1.实现对表的管理
        2.通过BaseLayer的接口实现将Table写到数据库的接口
*/


#define TIME_SEP_IN_SECOND 10

class TableManager {
private:
    static Cache<std::string, Table> tables;

    //TODO:添加成员
public:

    //添加表
    static Table* createTable(std::string& name);

    //删除表
    static void deleteTable(std::string& name);
    static void deleteTable(Table& table);
    
    /*条目级操作*/
    //插入条目
    static void insertEntry(Table&, Entry&);
    static void insertEntry(std::string&, Entry&);

    //删除条目
    static void deleteEntry(Table&, Entry&);
    static void deleteEntry(std::string&, Entry&);

    //更新条目
    static void updateEntry(Table&, Entry&);
    static void updateEntry(std::string&, Entry&);

    //插入或更新条目
    static void insertOrUpdateEntry(Table&, Entry&);
    static void insertOrUpdateEntry(std::string&, Entry&);
};