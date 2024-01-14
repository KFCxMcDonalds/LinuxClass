#include<iostream>
#include<fstream>
#include<string>

#include"Person.h"

using namespace std;

int main()
{
    Person person("liwenwu", 23);

    // 写入文件
    ofstream outfile;
    outfile.open("info", ios::binary); // 以二进制模式打开文件
    // serialize
    person.Serialize(outfile);
    outfile.close(); // 写入后关闭文件 

    Person loaded_person;
    // 读取文件
    ifstream infile;
    infile.open("info", ios::binary);
    // deserialize
    loaded_person.Deserialize(infile);
    infile.close();
    // 输出对象
    loaded_person.output();

    return 0;
}
