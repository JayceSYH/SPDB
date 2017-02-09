#pragma once

#include "DataFrame.h"
#include "DBModel.h"
#include <functional>
#include <string>
#include <vector>

/*
	ʵ������ĸ���SQL Operation
*/


/*
	SQLOperationʵ����Select��Insert��Delete��ЩEntry���Ĳ���
	�Լ�Create��Drop��Alert��Join��Щ���Ĳ���
*/
enum JoinMode { LeftJoin, RightJoin, InnerJoin, OutterJoin };

class SQLOperation {
public:
	//Entry ������
	//ѡ��ɸѡ����ѡ�е��в����һ���µ�DataFrame,Ĭ��ɸѡ�����У������б�Ϊ�գ�
	DataFrame* Select(DataFrame&, std::function<bool(DataRow&)>, std::vector<std::string> cols = std::vector<std::string>());
	//����newData��origin�����һ���µ�DataFrame
	DataFrame& Insert(DataFrame& origin, DataFrame& newData);
	DataFrame& Insert(DataFrame&, DataRow&);
	//��DataFrame��ȥ����ɸѡ����ѡ�е������һ���µ�DataFrame
	DataFrame& Delete(DataFrame&, std::function<bool(DataRow&)>);

	//Table ������
	//��һ��DataFrame����һ���±�
	Table* Create(DataFrame&);
	//��һ��Index����һ���µĿձ�
	Table* Create(Index&);
	//����Ŀ���,����ֵΪ�Ƿ�ɹ�
	bool Drop(Table&);
	//��Index����ϢΪ׼��Table�����޸�
	Table& Alert(Table&, Index&);
	//��onConditionΪ�ؼ��ֶ����������join������Ĭ��Ϊinnerjoin
	DataFrame* Join(Table&, Table&, std::vector<std::string> onCondition, JoinMode mode=InnerJoin);
};