#include<iostream>
#include<fstream>
#include<vector>

#include"Person.h"
#include"Book.h"
#include"Serializer.h"
#include"MyStruct.h"

using namespace std;


int main()
{
    // 创建对象组成的结构体向量
    // 两个类分别创建两个对象
    Person p1("liwenwu", 23), p2("jiangbei", 33);
    Book b1("C++", 43.5), b2("Python", 23.9);
    // 加入结构体向量
    vector<ObjWithType> objWithTypes = {
        ObjWithType(0, p1),
        ObjWithType(1, b1), 
        ObjWithType(0, p2),
        ObjWithType(1, b2)
    };
    
    const char* filename = "info";

    // 序列化到文件
    Serializer::serialize(objWithTypes, filename);

    // 接收文件信息创建对象
    vector<ObjWithType> loaded_objWithTypes;
    // 反序列化
    Serializer::deserialize(loaded_objWithTypes, filename);
    // 输出反序列化结果
    for(ObjWithType& obj: loaded_objWithTypes){
        obj.output();
    }
    return 0;
}
