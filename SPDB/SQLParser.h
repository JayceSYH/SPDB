#pragma once

#include "DataFrame.h"
#include <string>

/*
	ʵ�������SQLParser��
		Tips��
			1.ʹ��������ʽ���ַ��������һ��tokens
			2.����﷨�Ƿ���ȷ
			3.����ѡ������׺���ʽת���ɺ�׺���ʽ
			4.�õ����յĽ��
*/

enum TokenType { TK_KEYWORD /*Add token types here*/};

class Token {
private:
	std::string content;
	TokenType type;
public:
	//�жϲ�����ʲô���͵�token������ʼ����Ա����
	Token(std::string&);

	//TODO����ӳ�Ա����
};

//SQL ��������,ʵ�ֽ�SQL���ת��Ϊ��Ӧ�Ĳ���
class SQLParser {
public:
	//ִ�в�ѯ������select��
	DataFrame* excuteQuery(std::string sql);
	//ִ�б���Ŀ�ĸ��²���������ֵΪ��Ӱ�����Ŀ��
	int excuteUpdate(std::string sql);
	//ִ�б�ṹ����
	void excute(std::string sql);
};
