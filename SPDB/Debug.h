#pragma once

//在此定义你要调用的测试函数
#define _TEST_DEMO_

/*
    Debug用法：
        在包含main函数的文件中include该头文件，通过修改define不同的宏
        来在不同的测试main函数中进行切换。

        eg：
            #define _DEBUG1_

            #if defined(_DEBUG1_)
                int main() { ... }
            #elif defined(_DEBUG2_)
                int mian() { ... }
            #endif

*/