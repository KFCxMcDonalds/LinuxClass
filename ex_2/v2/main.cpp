#include<iostream>
#include<fstream>
#include<vector>

#include "Person.h"
#include "Serializer.h"

using namespace std;

int main()
{
    const char* filename = "info";

    // 创建待序列化的多个对象
    vector<Person> people = {
        {"liwenwu", 23},
        {"liangyiling", 33},
        {"jiangbei", 43}
    };
    // 序列化到文件
    Serializer::serialize(people, filename);

    // 接收文件信息创建对象
    vector<Person> loaded_person;
    // 反序列化
    Serializer::deserialize(loaded_person, filename);
    // 输出反序列化结果
    for(const Person& p: loaded_person){
        p.output();
    }
    return 0;
}
