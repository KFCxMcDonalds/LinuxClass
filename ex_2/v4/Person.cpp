#include<iostream>
#include<fstream>
#include<string>

#include"Person.h"

using namespace std;

Person::Person(){}
Person::Person(string n, int a): name(n), age(a){}

void Person::Serialize(ofstream& ofs) const { // 该函数不会改变对象的属性，所以是const
    // 将指示类别的type写入文件
    int type = this->getType();
    ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));
    // 将age变量的地址转换为char*类型指针，以便write将二进制数据写入文件
    ofs.write(reinterpret_cast<const char*>(&age), sizeof(age));  
    // 将name字符串的长度信息写入文件
    size_t nameLength = name.size(); // size_t存储字符串长度变量
    ofs.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    // 获取name字符串的指针，并存入文件
    ofs.write(name.c_str(), nameLength);
}

void Person::Deserialize(ifstream& ifs){
    // 读取age内容，从一个指针读取，长度为age类型的长度，即int(4 Bytes)
    ifs.read(reinterpret_cast<char*>(&age), sizeof(age));
    // 读取nameLength
    size_t nameLength;
    ifs.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    // 读取name
    char* buffer = new char[nameLength + 1]; // string类型，以'\0'结尾，所以是长度+1
    ifs.read(buffer, nameLength);  // 读取到buffer
    buffer[nameLength] = '\0'; // 加入字符串结尾
                               
    name = buffer;
    delete [] buffer;
}

int Person::getType() const{
    return 0;
}

void Person::output() const{
    cout << "type: Person" << endl;
    cout << "Name:" << name << "\n" << "age:" << age << endl;
}
