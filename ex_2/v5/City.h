#pragma once // 防止重复引用

#include<string>

#include"Serializable.h"

using namespace std;

//类3:City类
//对象属性：city_name, distance
class City: public Serializable
{
    public:
        City(); // 默认构造函数
        City(string n, float p); // 构造函数，构造对象数据
        void Serialize(ofstream& ofs) const; // 序列化函数
        void Deserialize(ifstream& ifs); // 反序列化函数
        int getType() const; // 获取对象的类别
        void output() const; // 输出对象的属性
    private:
        string city_name;
        double distance;
};
