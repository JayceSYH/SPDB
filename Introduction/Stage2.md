## SPDB Stage2: Implement the middle layer

### Abstract
>  In stage 1, you've completed the database filesystem. This time, we are gonna do something about database operation. (See [SQL](https://en.wikipedia.org/wiki/SQL))
>  You will complete the following files in this stage:  
>
>  MiddleLayer----|--SQLOperation　　　　　---The implementation of SQL Operation  
>　　　　　　　|  
>　　　　　　　|--TableManager　　　　　---The implementation of a set of methods managing the table  
>　　　　　　　|  
>　　　　　　　|--TimerManager　　　　　---The implementation of a set of methods about time 

---

In this stage, you will use you implementation in stage 1. So, be sure that you have a good understanding of what you have done in stage 1. 
Maybe you should review your code first before starting this stage. After preparation, let's begin our journey to the middle layer!

### TimerManager
TimerManager implements a set of methods used to delay function call or call function periodically. In stage 2, we need to implement 'delay' function used to delay function call and 'Ticker' class used to call function periodically. If you need other functions about time, just extend this class.

#### How to implement it?
How to delay a function call? Implementing it with a new thread and sleep function seems to be an intuitive way. But what if you have a thousand such delay calls? It will be a bad way to use a thousand threads as creating a new thread costs much.

How about using just one thread to do this? Just imagine that you have a list of delayed things to do(delayed functions) and you can have a rest (sleep) before the time of dealing with the most recent job coming. But just when you are ready to sleep, you get a new message saying that you will have to deal with a new task(new delayed function call). You have no choice but to rearrange you time sheet, compare the time of the new task with the former most recent task's. Knowing how long can you spend on you rest(reset sleep time), finally you can have a good rest!

That seems to be a good workflow. But think about this condition: you have 1000 works and the gap between works are exactly 1ms. If you choose to sleep every time you finish a task, you may have to switch between threads for 2000 times to finish this job. That costs much! How could you deal with such problem?
#### Optional
  - Now that we can decide when to call our functions, threr are more things we can do now. We can extend cache class to periodically clean up unused memory. But you should consider that how can you design this class to satisfy different clean-up demands.  
  - There are still some problems in this design. Image that you have a task whick costs long time to complete and many tasks only need little time to complete. But you don't know which one cost more and put all of them into task queue and run them in the same thread. It's obviously inefficient to run those tasks in the same thread, we need more thread to do this! Now it's time to use **thread pool** to improve our TaskQueue!

### TableManager
TableManager manages all the tables in this program. Whether you are creating a table or deleting a table, you should notify your table manager first(Imageine you are doing your jobs and you should notify your team manager if you need some authorities) or just let your table manager to deal with such matters.

### SQL
In this project, we only implement some frequently-used sql function.
##### Functions to implement
###### Table
- Create　　　　--Create a new table
- Alert　　　　　--Change table structure
- Drop　　　　　--Delete table

###### Entry
- Insert　　　　--Insert one or more rows to a table
- Select　　　　--Select one or more rows from a table
- Update　　　　--Update one or more rows of date
- Delete　　　　--Delete one or more rows