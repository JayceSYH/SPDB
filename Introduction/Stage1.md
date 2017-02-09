## SPDB Stage1: Implement the base layer
###  Abstract
In **stage 1**, you will implement the file structure of a database file and it's filesystem. To achieve this, you should first implement some classes to assist you to complete your **stage 1 Lab**.

You will complete the following files in this stage:  

>  Common ---|--Cache　　　　　　   ---The implementation of a simple cache  
>  　　|　　　|  
>  　　|　　　|--DataFrame　　　　　　   ---The implementation is similar to 'pandas.DataFrame' in Python  
>  　　|　　　|  
>  　　|　　　|--Bytes　　　　　　   ---The implementation of Bytes stream.  
>  　　|  
>  BaseLayer ---|--DataType　　　　   ---The implementation of Database field types  
>  　　　　　　|  
>  　　　　　　|--DBFileSystem　　   ---The implementation of DBFileSystem  
>  　　　　　　|  
>  　　　　　　|--DBModel　　　　   ---The implementation of DBModels (Table, Entry...)  

---

It's useful to have an overview of these files, and now, we are going to begin our first SPDB journey~

### DataFrame

Before dealing with those tough tasks, let's begin with some easy and interesting jobs.

#### about DataFrame

You may have heard of `DataFrame` in Python or have enjoyed using it for a long time. It's an easy-to-use and powerful tool which is used to manage a set of named data. It doesn't matter if you don't know anything about it, let's just implement it with our own code!

#### Index
You can think of an index as the title of a table's columns. What's more, it contains the type of each column and any other necessary informations needed to identify a table column. 
To *keep it simple, stupid* (See [Kiss Principle](https://en.wikipedia.org/wiki/KISS_principle) ), we just need to keep names and types of a table's columns in the Index class. If you need more property, just add it as you want.

#### DataRow
DataRow contains Index and a row of data and some functions you need to implement. But just do as *Kiss Principle* says, keep it simple utill you need more features.

#### DataColumn
After finishing 'Index' of our DataFrame, we need to think about the way we are going to store our data in DataFrame. Arrays seem to be a fast and simple way, but it can't gurantee our dataframe's flexibility and scalability. How about using 'vector' to store rows of our data? It seems to be a good idea which is flexible and scalable as well as being a good implementation for row operation. So why we choose DataColumn as our way to store our data? Because it's fast when forming a subframe with some of the origin dataframe's columns, and the most important reason is that the author's just chosen it :).

#### DataFrame
Now, it's time to implement the core class `DataFrame`. With Index and DataColumn, we can easily build a simple DataFrame. However, it's imperfect utill some amazing functions are added to this class. So, just keep on improving your DataFrame by add more useful functions!

### Cache
Cache is widely used in computer architecture design. You may know that the time of reading a byte from hard disk is much longer than reading from RAM, and the time of reading a byte from RAM is much longer than reading from ROM. But generally, 'faster' means more expensive, so we need to take good use of those scarce resource. That's why we need to use cache technique to fasten our program.  
For more about cache, see a [reference on wiki](https://en.wikipedia.org/wiki/Cache_memory).

#### CacheProperty
CacheProperty is a combination of cache unit's properties. The most important part is thread lock which gurantees that at one time, only limited numbers of threads can read or write some specific data. There are two kinds of widely used lock implementation -- *Pessimistic Lock* and *Optimistic Lock* (See:

- [Pessimistic Lock](http://en.cppreference.com/w/cpp/thread/mutex)
- [Optimistic Lock](https://en.wikipedia.org/wiki/Optimistic_concurrency_control)
- [Readers–writer lock](https://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock)

#### CacheContent
CacheContent just simply combines CacheProperty and the content of the cache unit. You need to implement relative functions to complete it.

##### Cache
Now, all of the preparation are done, let's finish the cache! If you want, you can implement a cache mode which automatically cleans up all the unused memory in cache.

________________________________
### DBFileSystem
This time, we are facing a tough task. But don't be afraid, with our above preparations we will eventually go through it. 

#### Overview
Before fighting with our enemy, we should firstly know what our enemy is.  

How can we save our data in a file? Remeber that we shoud keep our database flexible and scalable enough to add or delete data or even change the struture of our tables. Besides, efficiency is also crucial for a database as a database always contains a plenty of data. To solve this problem and make sure that this project is suitable for beginners, we degined a simple filestructure to store our data in it.(See `FileStructs.h`)  

But I don't think you want to operate the database file every time you want to insert an entry or just select some rows of a table, we need to use OOP to simplify it! So, we need to design our data model and create some easy-to-use API for such reason.(See `DBModel.h`、`DBFileSystem.h`)  

Sometimes we use integer as data value, sometimes string. How can we operate this types of data in the same way? We need a super class to unify them!  (See `DataType.h`)

#### FileStructs
| name                      | size                                 |
| :------------------------ | :----------------------------------- |
| Schema                    | 1024Byte                             |
| Database Table Descriptor | MAX_TD_NUM * sizeof(TableDescriptor) |
| PAGE1                     | PAGE_SIZE(4kb)                       |
| PAGE2                     | PAGE_SIZE                            |
| PAGE2                     | PAGE_SIZE                            |

This is the file structure of database file, the first 1024 bytes is Schema, which describes the structure of this file. The following `MAX_TD_NUM * sizeof(TableDescriptor)` bytes of space is used to store TableDescriptor which describes a table's base information. For more details, see `FileStructs.h`

####  FileSystem
If you have understood how dose the file structs work, you can start building you database filesystem with the following steps:

1. Load base info of the database file
2. Implement page operations
3. Implement Table operations
4. Implement Entry opeartions

________________________________
### TEST
Congratulations! You've just finished the database filesystem. Now, let's test the program to see if it runs correctly.

#### How to debug?
How can we debug in a simple way? You will debug many modules, but only one main function is allowed in c++. If you need to test a new module, you can convert your main to comment and create a new main function. But when you want to switch between you main functions, you need to convert the current main function to comment and use you needed main code. Inefficient and boring! To make matters worse, if you have comment in your main function, it's hard to convert the whole function to comment. So, what can we do?   

##### eg

```c++
// define _DEBUG1_

#if defined(_DEBUG1_)  
　int main() { ... }  
#elif defined(_DEBUG2_)  
　int main() { ... }  
#endif
```

Dose it remind you of something? Yes, that's macro, which is really useful in such situations. If you have some doubt about it, see Test/Debug.h for more detail
