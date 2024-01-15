#pragma once // 防止重复引用

#include<string>
#include<fstream>

using namespace std;

//类1:Person类
//对象属性：name, age
class Person
{
    public:
        Person(); // default constructor
        Person(string n, int a); // 构造函数，构造对象数据
        void Serialize(ofstream& ofs) const; // 序列化函数
        bool Deserialize(ifstream& ifs); // 反序列化函数
        void output() const; // 输出对象的属性
    private:
        string name;
        int age;
};
