#include<iostream>
#include<fstream>
#include<vector>

#include"Serializable.h"
#include"Person.h"
#include"Book.h"
#include"City.h"
#include"Serializer.h"

using namespace std;

int main()
{
    // 创建对象组成的Serializable向量
    // 多个类分别创建两个对象
    Person p1("liwenwu", 23), p2("jiangbei", 33);
    Book b1("C++", 43.5), b2("Python", 23.9);
    City c1("Deyang", 833578.2834), c2("Beijing", 18608934.7693);
    // 加入结构体向量
    vector<Serializable*> pObjs = {
        &p1,
        &p2,
        &b1,
        &b2,
        &c1,
        &c2
    };

    const char* filename = "info";

    // 序列化到文件
    Serializer::serialize(pObjs, filename);

    // 接收文件信息创建对象
    vector<Serializable*> loaded_pObjs;
    // 反序列化
    Serializer::deserialize(loaded_pObjs, filename);
    // 输出反序列化结果
    for(Serializable*& pObj: loaded_pObjs){
        pObj->output();
    }
    return 0;
}



