#pragma once

#include "DataFrame.h"
#include <string>

/*
	实现下面的SQLParser：
		Tips：
			1.使用正则表达式将字符串处理成一组tokens
			2.检查语法是否正确
			3.（可选）将中缀表达式转化成后缀表达式
			4.得到最终的结果
*/

enum TokenType { TK_KEYWORD /*Add token types here*/};

class Token {
private:
	std::string content;
	TokenType type;
public:
	//判断参数是什么类型的token，并初始化成员变量
	Token(std::string&);

	//TODO：添加成员函数
};

//SQL 语句解析器,实现将SQL语句转化为相应的操作
class SQLParser {
public:
	//执行查询操作（select）
	DataFrame* excuteQuery(std::string sql);
	//执行表条目的更新操作，返回值为受影响的条目数
	int excuteUpdate(std::string sql);
	//执行表结构操作
	void excute(std::string sql);
};
