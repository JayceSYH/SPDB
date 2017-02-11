#pragma once
#include "DataFrame.h"
#include "Mess.h"

/*
    完成下面数据模型的实现：
        1.数据库表的实现
        2.数据条目的实现
*/

/*****************数据库表************/
/*
    为了数据库文件的实现方便，需要添加一个隐藏列_ROW_STATE_TAG_来表示某行是否被删除
*/
class Table : public DataFrame {
    Table();            //所有表都默认有一个_ROW_STATE_TAG_列来标记某行是否被删除

    Bytes toBytes();
};


/***************数据条目（记录）**************/
class Entry : public DataRow {
    Bytes toBytes();
};