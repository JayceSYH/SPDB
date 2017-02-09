#pragma once

#include<stdint.h>

#define LEVEL1_INDEX_NUM 10			//多级索引中的一级索引数量
#define PAGE_SIZE (4 * 1024)					//页大小
#define MAX_TD_NUM 1024					//表描述符最大数量
#define SCHEMA_SIZE 1024					//Schema字节数
#define FIRST_PAGE_OFFSET   (SCHEMA_SIZE + MAX_TD_NUM * sizeof(TableDescriptor))	//第一个页的起始地址

/*
为了简单起见，简化版的数据库文件内容分为几个部分：
1.schema：数据库基本信息
2.表描述符：存储了表的基本信息以及表内字段的描述符起始地址（在文件内的offset），
		在本实验中为表描述符分配了固定大小的空间（1024个表描述符大小），并且位置固定在schema之后
3.字段描述符：存储了字段的基本信息以及字段内容的起始地址，字段描述符位置不固定，由表描述符中的索引决定
4.通过使用分页的方法保证数据库内容的灵活性、可扩展性
*/

/*
一些基本概念的介绍：
	1.多级索引：一级索引直接指向目标起始地址，二级索引指向一个索引页，页中每4个字节都是一级索引，三级索引同理（具体百度）
	2.表、条目（记录）和字段：表和字段好说，记录就是表的一行
	3.页：逻辑上将内存、硬盘资源分成多个部分（页），以解决空间碎片化等问题
*/


/********数据库文件格式*************
名称										大小

------------------------------------------------------------------------------|
Schema									1024Byte														  |
------------------------------------------------------------------------------|
数据库表描述符表			MAX_TD_NUM * sizeof(TableDescriptor)	  |
										  默认表数量最大值(MAX_TD_NUM)为1024  |
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


/************索引结构****************

						     ____  TableDescriptor					   _______  FieldDescriptor			 _______ FieldContent
						   /														 /													   /
	Schema____/______ TableDescriptor   _______/_________ FieldDescriptor____/_____ FieldContent
						 \														   \													 \
						   \ ......													 \ ......											   \ ......
*/


//数据库头
struct Schema
{
	uint32_t magic;								//魔数
	uint32_t table_num;						//表数目
	uint32_t fep_offset;						//first empty page 第一个未分配页
	uint32_t tdt_offset;						//table descriptor table 表描述符表起始地址偏移
	uint32_t fdt_offset;						//field descriptor table 字段描述符表起始地址偏移
};
/*
Note:
	1.魔数是很多特定类型文件都有的4字节identifier，用来判断是否是某种类型的文件
	2.未分配页偏移（fep）在没有未分配页时为0，有未分配页时指向第一个未分配页，每个未分配页的前4个字节为下一个为分配页的起始地址，若没有下一页则为0
	3.表描述符表、字段描述符表里放的分别是表描述符和字段描述符
*/


//页结构
struct Page
{
	uint32_t offset;		//页起始地址
	union {
		uint8_t _8[PAGE_SIZE];
		uint16_t _16[PAGE_SIZE / 2];
		uint32_t _32[PAGE_SIZE / 4];
	} content;				//页内容
};
/*
Note:
	1.PAGE_SIZE默认为4kb
	2.使用union定义页内容是为了能以三种不同的方式读取数据（单字节、双字节、四字节）
*/
  

//多级索引
struct MultilevelIndex
{
	uint32_t level1[LEVEL1_INDEX_NUM];			//一级索引
	uint32_t level2;														//二级索引
	uint32_t level3;														//三级索引
};
/*
Note:
	一级索引直接指向目标起始地址，二级索引指向一个索引页，页中每4个字节都是一级索引，三级索引同理
*/

//表描述符
struct TableDescriptor
{
	char table_name[64];							//表名
	uint32_t field_num;							//字段数
	MultilevelIndex mli;							//字段描述符多级索引
};

//字段描述符
struct FieldDescriptor
{
	char field_name[64];							//字段名
	uint16_t width;									//字段宽度
	uint16_t type;										//字段类型
	uint32_t row_num;							//字段行数
	MultilevelIndex mli;							//字段内容多级索引
};

