#pragma once

#include "ConcurrentQueue.h"
#include <string>

/*
	实现数据库的连接，并对数据库连接进行管理
*/

/*
	数据库连接
*/
class Connection {
public:
	void sendSQL(std::string sql);

	//TODO:添加其他成员
};


/*
	数据库连接管理器，管理到数据库的连接
*/
class ConnectionManager {
	//线程安全队列，用来存储已建立的连接
	ConcurrentQueue<Connection> ccq;
public:
	//创建一个数据库连接，可以添加参数来控制数据库连接的属性
	static Connection createConnection(/*Meta*/);

	//TODO：添加成员函数对Connnection进行管理
};