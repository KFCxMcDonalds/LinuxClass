#include<fstream>
#include<iostream>
#include<string>

#include"City.h"

using namespace std;

City::City(){}
City::City(string n, float p): city_name(n), distance(p){}

void City::Serialize(ofstream& ofs) const { // 该函数不会改变对象的属性，所以是const
    // 将指示类别的type写入文件
    int type = this->getType();
    ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));
    // 将distance变量的地址转换为char*类型指针，以便write将二进制数据写入文件
    ofs.write(reinterpret_cast<const char*>(&distance), sizeof(distance));  
    // 将city_name字符串的长度信息写入文件
    size_t city_nameLength = city_name.size(); // size_t存储字符串长度变量
    ofs.write(reinterpret_cast<const char*>(&city_nameLength), sizeof(city_nameLength));
    // 获取city_name字符串的指针，并存入文件
    ofs.write(city_name.c_str(), city_nameLength);
}

void City::Deserialize(ifstream& ifs){
    // 读取distance内容，从一个指针读取，长度为distance类型的长度，即int(4 Bytes)
    ifs.read(reinterpret_cast<char*>(&distance), sizeof(distance));
    // 读取city_nameLength
    size_t city_nameLength;
    ifs.read(reinterpret_cast<char*>(&city_nameLength), sizeof(city_nameLength));
    // 读取city_name
    char* buffer = new char[city_nameLength + 1]; // string类型，以'\0'结尾，所以是长度+1
    ifs.read(buffer, city_nameLength);  // 读取到buffer
    buffer[city_nameLength] = '\0'; // 加入字符串结尾
                               
    city_name = buffer;
    delete [] buffer;
}

int City::getType() const{
    return 2;
}

void City::output() const{
    cout << "type: City" << endl;
    cout << "city_name:" << city_name << "\n" << "distance:" << distance << endl;
}
