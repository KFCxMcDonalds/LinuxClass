#include<fstream>
#include<iostream>
#include<string>

#include"Book.h"

using namespace std;

Book::Book(){}
Book::Book(string n, float p): book_name(n), price(p){}

void Book::Serialize(ofstream& ofs) const { // 该函数不会改变对象的属性，所以是const
    // 将指示类别的type写入文件
    int type = this->getType();
    ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));
    // 将price变量的地址转换为char*类型指针，以便write将二进制数据写入文件
    ofs.write(reinterpret_cast<const char*>(&price), sizeof(price));  
    // 将book_name字符串的长度信息写入文件
    size_t book_nameLength = book_name.size(); // size_t存储字符串长度变量
    ofs.write(reinterpret_cast<const char*>(&book_nameLength), sizeof(book_nameLength));
    // 获取book_name字符串的指针，并存入文件
    ofs.write(book_name.c_str(), book_nameLength);
}

void Book::Deserialize(ifstream& ifs){
    // 读取price内容，从一个指针读取，长度为price类型的长度，即int(4 Bytes)
    ifs.read(reinterpret_cast<char*>(&price), sizeof(price));
    // 读取book_nameLength
    size_t book_nameLength;
    ifs.read(reinterpret_cast<char*>(&book_nameLength), sizeof(book_nameLength));
    // 读取book_name
    char* buffer = new char[book_nameLength + 1]; // string类型，以'\0'结尾，所以是长度+1
    ifs.read(buffer, book_nameLength);  // 读取到buffer
    buffer[book_nameLength] = '\0'; // 加入字符串结尾
                               
    book_name = buffer;
    delete [] buffer;
}

int Book::getType() const{
    return 1;
}

void Book::output() const{
    cout << "type: Book" << endl;
    cout << "book_name:" << book_name << "\n" << "price:" << price << endl;
}
