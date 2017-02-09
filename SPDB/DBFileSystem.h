#pragma once
#include "DataFrame.h"
#include "FileStructs.h"
#include "DBModel.h"


/********���ݿ��ļ���ʽ*************
����										��С

------------------------------------------------------------------------------|
Schema									1024Byte														  |
------------------------------------------------------------------------------|
���ݿ����������			MAX_TD_NUM * sizeof(TableDescriptor)	  |
										  Ĭ�ϱ��������ֵ(MAX_TD_NUM)Ϊ1024  |
------------------------------------------------------------------------------|
PAGE1									PAGE_SIZE(4kb)										  |
------------------------------------------------------------------------------|
PAGE2									PAGE_SIZE												  |
------------------------------------------------------------------------------|
PAGE2									PAGE_SIZE												  |
------------------------------------------------------------------------------|
......																												  |
------------------------------------------------------------------------------|

*/


/*
	����������ݿ��ļ�ϵͳ��ʵ�֣�
		1.���캯��������������ʵ�֣�writeBaseInfo������ʵ��
		2.���������ʵ�֣�������Cacheʵ�ֶ�ҳ�Ļ���
		3.������������ı�������ʵ��
		4.���ڱ�������ҳ������ʵ��Entry���������

		Note:���ݿ�Ĳ����Ķ��ǲ����ģ���ʵ����DBFileSystem������ҳ����
		ʽʵ�ֲ������ƣ�����һҳ���в���ʱ���ҳ���϶�������д��
		��ref��http://blog.csdn.net/feixiaoxing/article/details/7024677��
*/


/****************���ݿ��ļ�ϵͳ����������ݿ��ļ����в���**********/
class FileSystem {
private:
	Schema schema;
	TableDescriptor td[MAX_TD_NUM];

	//TODO:��ӳ�Ա����
public:
	/*
		�������ݿ��ļ�,���������򴴽�һ�����ļ�
		����������ݿ�Ļ�����Ϣ��schema��TD��
	*/
	FileSystem(std::string filename) /*throw (MyException)*/;
	~FileSystem();


	/*
		д��Schema�����ݿ����������
	*/
	void writeBaseInfo();


	/*
		ҳ��������
			ע���ڱ�ʵ����Ϊ�򻯹��̺ͱ�֤Ч�ʣ�DBFileSystem������������Ѿ����ز���δ��ȡ�������ҳ��ָ�룬
			��������Ҫ�ظ���дһ��ҳ���ظ��������ĳ��ҳ��ʱ�򣬾�ֻ�Ƿ����Ѿ������ҳ�����ȷ��������Ҫ���ʸ�ҳ��
			ʹ��decachePageȡ��ҳ�Ļ������ͷ��ڴ�ռ䣬ע�ⲻ���ֶ�free��Page���������ܻ�����ظ�ɾ���Ĵ���
	*/
	//��ȡһ����ҳ�����ļ�ϵͳ��û�п���ҳ���������ļ������Ի�ȡ��ҳ
	Page* getNewPage();
	
	//��һ��ҳд���ļ�
	void writePage(Page&);
	//������ҳд���ļ�
	void writeAllPage();

	//����һ��ҳ�������뻺��
	Page* loadPage(uint32_t offset);

	//ȡ��FileSystem��ҳ�Ļ��棬ע��ò���������ʹ�ø�ҳ����ΪFileSystem��ʱ���ܻ��ո�ҳ���ڴ���Դ
	void decachePage(Page&);


	/*
		������
	*/
	std::vector<Table*> loadTables();
	//�����ݿ��ļ��д����ñ�
	void createTable(Table&);
	//�����ݿ��ļ���ɾ���ñ�
	void deleteTable(Table&);
	//Ϊ�˼������alertTableֻʵ���е�����ɾ����������index�������޸�Table
	void alterTable(Table& origin, Index& index);


	/*
		Entry����¼��������
	*/
	void insertEntry(Table&, Entry&);
	void deleteEntry(Table&, Entry&);
	void updateEntry(Table&, Entry&);
	void insertOrUpdateEntry(Table&, Entry&);

	//TODO����ӳ�Ա����
};
