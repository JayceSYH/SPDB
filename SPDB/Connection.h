#pragma once

#include "ConcurrentQueue.h"
#include <string>

/*
	ʵ�����ݿ�����ӣ��������ݿ����ӽ��й���
*/

/*
	���ݿ�����
*/
class Connection {
public:
	void sendSQL(std::string sql);

	//TODO:���������Ա
};


/*
	���ݿ����ӹ��������������ݿ������
*/
class ConnectionManager {
	//�̰߳�ȫ���У������洢�ѽ���������
	ConcurrentQueue<Connection> ccq;
public:
	//����һ�����ݿ����ӣ�������Ӳ������������ݿ����ӵ�����
	static Connection createConnection(/*Meta*/);

	//TODO����ӳ�Ա������Connnection���й���
};