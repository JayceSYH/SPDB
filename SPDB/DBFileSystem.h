#pragma once
#include "DataFrame.h"
#include "FileStructs.h"
#include "DBModel.h"


/********数据库文件格式*************
名称                                      大小

------------------------------------------------------------------------------|
Schema                                 1024Byte                               |
------------------------------------------------------------------------------|
数据库表描述符表              MAX_TD_NUM * sizeof(TableDescriptor)            |
                             默认表数量最大值(MAX_TD_NUM)为1024               |
------------------------------------------------------------------------------|
PAGE1                                 PAGE_SIZE(4kb)                          |
------------------------------------------------------------------------------|
PAGE2                                   PAGE_SIZE                             |
------------------------------------------------------------------------------|
PAGE2                                   PAGE_SIZE                             |
------------------------------------------------------------------------------|
......                                                                        |
------------------------------------------------------------------------------|

*/



/*
    完成下面数据库文件系统的实现：
        1.构造函数、析构函数的实现，writeBaseInfo函数的实现
        2.物理操作的实现，并基于Cache实现对页的缓存
        3.基于物理操作的表级操作的实现
        4.基于表级操作和页级操作实现Entry级物理操作

        Note:数据库的操作的都是并发的，本实验中DBFileSystem采用锁页的形
        式实现并发控制，即对一页进行操作时会对页加上读锁或者写锁
        （ref：http://blog.csdn.net/feixiaoxing/article/details/7024677）
*/


/****************数据库文件系统，负责对数据库文件进行操作**********/
class FileSystem {
private:
    Schema schema;
    TableDescriptor td[MAX_TD_NUM];

    //TODO:添加成员变量
public:
    /*
        关联数据库文件,若不存在则创建一个新文件
        负责加载数据库的基本信息（schema、TD）
    */
    FileSystem(std::string filename) /*throw (MyException)*/;
    ~FileSystem();


    /*
         写回Schema、数据库表描述符表
    */
    void writeBaseInfo();


    /*
         页级操作：
            注意在本实验中为简化过程和保证效率，DBFileSystem类持有了所有已经加载并且未被取消缓存的页的指针，
            这样在需要重复读写一个页面重复申请加载某个页的时候，就只是返回已经缓存的页，如果确定不再需要访问该页，
            使用decachePage取消页的缓存来释放内存空间，注意不能手动free掉Page，这样可能会造成重复删除的错误
    */
    //获取一个空页，若文件系统里没有空闲页，则增加文件长度以获取新页
    Page* getNewPage();

    //将一个页写入文件
    void writePage(Page&);
    //将所有页写回文件
    void writeAllPage();

    //加载一个页，并加入缓存
    Page* loadPage(std::uint32_t offset);

    //取消FileSystem对页的缓存，注意该操作后不能再使用该页，因为FileSystem随时可能回收该页的内存资源
    void decachePage(Page&);


    /*
        表级操作
    */
    std::vector<Table*> loadTables();
    //在数据库文件中创建该表
    void createTable(Table&);
    //在数据库文件中删除该表
    void deleteTable(Table&);
    //为了简单起见，alertTable只实现列的增、删操作，按照index的内容修改Table
    void alterTable(Table& origin, DBIndex& index);


    /*
        Entry（记录）级操作
    */
    void insertEntry(Table&, Entry&);
    void deleteEntry(Table&, Entry&);
    void updateEntry(Table&, Entry&);
    void insertOrUpdateEntry(Table&, Entry&);

    //TODO：添加成员函数
};
