#pragma once
#include "DataFrame.h"
#include "Mess.h"

/*
	�����������ģ�͵�ʵ�֣�
		1.���ݿ���ʵ��
		2.������Ŀ��ʵ��
*/

/*****************���ݿ��************/
/*
	Ϊ�����ݿ��ļ���ʵ�ַ��㣬��Ҫ���һ��������_ROW_STATE_TAG_����ʾĳ���Ƿ�ɾ��
*/
class Table : public DataFrame {
	Table();			//���б�Ĭ����һ��_ROW_STATE_TAG_�������ĳ���Ƿ�ɾ��

	Bytes toBytes();
};


/***************������Ŀ����¼��**************/
class Entry : public DataRow {
	Bytes toBytes();
};