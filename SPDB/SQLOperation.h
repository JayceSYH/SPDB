#pragma once

#include "DataFrame.h"
#include "DBModel.h"
#include <functional>
#include <string>
#include <vector>

/*
    实现下面的各种SQL Operation
*/


/*
    SQLOperation实现了Select、Insert、Delete这些Entry级的操作
    以及Create、Drop、Alert、Join这些表级的操作
*/
enum JoinMode { LeftJoin, RightJoin, InnerJoin, OutterJoin };

class SQLOperation {
public:
    //Entry 级操作
    //选出筛选函数选中的行并组成一个新的DataFrame,默认筛选所有列（列名列表为空）
    DataFrame* Select(DataFrame&, std::function<bool(DataRow&)>, std::vector<std::string> cols = std::vector<std::string>());
    //插入newData到origin中组成一个新的DataFrame
    DataFrame& Insert(DataFrame& origin, DataFrame& newData);
    DataFrame& Insert(DataFrame&, DataRow&);
    //从DataFrame中去除被筛选函数选中的行组成一个新的DataFrame
    DataFrame& Delete(DataFrame&, std::function<bool(DataRow&)>);

    //Table 级操作
    //从一个DataFrame创建一个新表
    Table* Create(DataFrame&);
    //从一个DBIndex创建一个新的空表
    Table* Create(DBIndex&);
    //丢弃目标表,返回值为是否成功
    bool Drop(Table&);
    //以DBIndex的信息为准对Table进行修改
    Table& Alert(Table&, DBIndex&);
    //以onCondition为关键字对两个表进行join操作，默认为innerjoin
    DataFrame* Join(Table&, Table&, std::vector<std::string> onCondition, JoinMode mode=InnerJoin);
};
