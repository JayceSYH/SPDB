#pragma once

#include <vector>
#include "DataType.h"
#include <string>
#include<vector>
#include<unordered_map>

/*
	DataFrameʵ���˶Դ��������ľ���Ļ�����������DBTable�ľ��󲿷ֹ��ܵĳ���
	DataRow���Ƕ�DBEntry��Series���ܳ���
	DataColumn��DataFrame�Ļ�����ɵ�λ���洢��������һ������

	����в����׵ĵط�������pandas������ô����
	Note:
		���鲻Ҫ������������ɾ��Data������ÿ�������µ�DataFrame��Ҫ���¸�������
		��Data��ͨ����Դͷ��ͳһ����Data�����ɺ�ɾ���������ڱ�ʵ���п���������Table��
		���ڴ���ɾ��ʱɾ��Data������С���ƵĿ�����ʵ�ֺܶ࿽�����캯�����ƶ���ֵ������
		�ĳɱ�
*/

/***********DataFrame����********/
//���������������������͵���Ϣ
class Index {
private:
	std::vector<std::string> indices;
	//TODO����ӳ�Ա
public:
	//TODO:��ӳ�Ա
};


/**********������*************/
class DataRow {
private:
	Index index;
	//TODO:��ӳ�Ա����
public:
	DBData& operator[](std::string col);
	//TODO:��ӳ�Ա����
};


/*********������************/
class DataColumn {
private:
	std::string name;
	std::vector<DBData*> data;

public:
	DataColumn(std::string name, std::vector<DBData> data);
	std::string getName();
	std::vector<DBData*>& getData();
	DBData& operator[](int);
	//TODO:��ӳ�Ա����
};


/***************���ݾ���*************/
class DataFrame {
private:
	//����
	Index index;

	//������
	std::unordered_map<std::string, DataColumn> columns;

	//TODO:��ӳ�Ա����
public:
	//������Ӧ�õ�ÿһ�в�������ֵ
	void apply(void func(DataRow));

	//������Ӧ�õ�ÿһ�в�����һ�������У�ÿ�е�ֵΪ���������ķ���ֵ
	template<typename T>
	DataColumn applyWithRet(T func(DataRow));
	//TODO:��ӳ�Ա����

	//��������
	void setIndex(Index& index);
	Index& getIndex();

	//��ȡ��(�������������)
	DataColumn& operator[](std::string name);

	//��ȡ��
	DataRow operator[](int rownum);

	//��ȡ������֡
	DataFrame operator[](std::string names[]);
	DataFrame operator[](int rows[]);
	DataFrame operator[](std::pair<int, int> slice_range);

	//ɾ����
	DataFrame drop(std::string[]);

	/**************OPTIONAL***********/
	/*
		ʵ�ֶ�key�ĵ��� 
		eg ��ÿ�е�һ��ֵ��һ��
			for (auto key : df)
				df[key][0]++;

		ref��http://blog.csdn.net/is2120/article/details/30238945
	*/


	//TODO:��ӳ�Ա����
};

