#include<iostream>

int main()
{
    // 动态分配空间
    int* array = new int[5];

    // 违规访问指针
    array[5] = 10; // array索引最多到4

    // 没有释放分配的内存，造成内存泄漏
    // delete [] array;
    return 0;
}
