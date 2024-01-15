#pragma once // 防止重复引用

#include<string>

#include"Serializable.h"

using namespace std;

//类2:Book类
//对象属性：book_name, price 
class Book: public Serializable
{
    public:
        Book(); // 默认构造函数
        Book(string n, float p); // 构造函数，构造对象数据
        void Serialize(ofstream& ofs) const; // 序列化函数
        void Deserialize(ifstream& ifs); // 反序列化函数
        int getType() const; // 获取对象的类别
        void output() const; // 输出对象的属性
    private:
        string book_name;
        float price;
};
