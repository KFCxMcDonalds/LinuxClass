#pragma once // 防止重复引用头文件

#include<fstream>

using namespace std;

// 待序列化对象的抽象类
class Serializable
{
    public:
        Serializable(){} // default constructor
        // 以下是纯虚函数，需要派生类实现
        virtual void Serialize(ofstream& ofs) const = 0; // 序列化函数
        virtual void Deserialize(ifstream& ifs) = 0; // 反序列化函数
        virtual int getType() const = 0; // 获取对象的类别
        virtual void output() const = 0; // 输出对象的属性

        virtual ~Serializable(){} // 析构函数，保证对象正确销毁
};
