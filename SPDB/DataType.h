#pragma once

#include "Mess.h"
#include <vector>


/*
    为了保证数据库操作的一致性，通过继承DBData类封装基本数据结构，实现基本数据类型的表示和转化
*/


class DBData {
public:
    //Data Type
    enum DBDataType { DB_INTEGER, DB_DOUBLE, DB_CHAR, DB_DATETIME, DB_BOOL /*, DB_DECIMAL*/ };

    //从Bytes类创建DBData类型变量
    static DBData* createFromBytes(Bytes, DBDataType);
    static std::vector<DBData*> createFromBytesList(std::vector<Bytes>&, DBDataType);

public:
    //Constructor
    DBData(Bytes) {};
    //destructor
    virtual ~DBData(){}

    //将DBData转化成Bytes
    virtual Bytes toBytes()=0;
    virtual DBDataType getType()=0;
};



/*************************************************************************/
/*
    完成下面数据库数据类型的实现：
        1.实现父类的虚函数
        2.添加转换成C++基本类型int、string等类型的函数getValue()（日期可以自己实现一个DateTime类，也可以用Unix时间戳）
        3.添加其他需要的变量和函数
*/


/*
    考虑到实现复杂度的问题，暂时只实现定长的数据类型
*/


//整型
class DBInteger : public DBData {

};


//浮点型
class DBDouble : public DBData {

};


//定长字符串
class DBChar : public DBData {

};


//日期类型 yyyy-mm-dd hh:MM:ss
class DBDateTime : public DBData {

};

class DBBool : public DBData {

};


/*********OPTIONAL*******/

//高精度浮点型
class DBDecimal : public DBData {

};
