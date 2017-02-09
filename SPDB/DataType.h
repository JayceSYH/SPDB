#pragma once

#include "Mess.h"
#include<vector>


/*
	Ϊ�˱�֤���ݿ������һ���ԣ�ͨ���̳�DBData���װ�������ݽṹ��ʵ�ֻ����������͵ı�ʾ��ת��
*/


class DBData {
public:
	//Data Type
	enum DBDataType { DB_INTEGER, DB_DOUBLE, DB_CHAR, DB_DATETIME /*, DB_DECIMAL*/ };

	//��Bytes�ഴ��DBData���ͱ���
	static DBData* createFromBytes(Bytes, DBDataType);
	static std::vector<DBData*> createFromBytesList(std::vector<Bytes>&, DBDataType);
	
public:
	//Constructor
	DBData(Bytes) {};
	//destructor
	virtual ~DBData(){}

	//��DBDataת����Bytes
	virtual Bytes toBytes()=0;
	virtual DBDataType getType()=0;
};



/*************************************************************************/
/*
	����������ݿ��������͵�ʵ�֣�
		1.ʵ�ָ�����麯��
		2.���ת����C++��������int��string�����͵ĺ���getValue()�����ڿ����Լ�ʵ��һ��DateTime�࣬Ҳ������Unixʱ�����
		3.���������Ҫ�ı����ͺ���
*/


/*
	���ǵ�ʵ�ָ��Ӷȵ����⣬��ʱֻʵ�ֶ�������������
*/


//����
class DBInteger : public DBData {

};


//������
class DBDouble : public DBData {

};


//�����ַ���
class DBChar : public DBData {

};


//�������� yyyy-mm-dd hh:MM:ss
class DBDateTime : public DBData {

};


/*********OPTIONAL*******/

//�߾��ȸ�����
class DBDecimal : public DBData {

};