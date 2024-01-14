#include<iostream>
#include<fstream>
#include<vector>

#include"Serializer.h"
#include "MyStruct.h"

using namespace std;
void Serializer::serialize(vector<ObjWithType>& objWithTypes, const char* filename){
    // 根据文件名以二进制模式创建文件用以存放对象信息
    ofstream ofs(filename, ios::binary);
    // 遍历vector<ObjWithType>中的结构体并依次存入文件
    for(ObjWithType& obj: objWithTypes){
        // 把结构体中指示类别的int type写入文件
        ofs.write(reinterpret_cast<const char*>(&obj.type), sizeof(obj.type));
        if(obj.type == 0){
            // Person
            Person* pp = static_cast<Person*>(obj.pObj);
            pp->Serialize(ofs);
        }else{
            // Book
            Book* pb = static_cast<Book*>(obj.pObj);
            pb->Serialize(ofs);
        }

    }ofs.close();
}

void Serializer::deserialize(vector<ObjWithType>& objWithTypes, const char* filename){
    // 根据文件名以二进制模式打开文件
    ifstream ifs(filename, ios::binary);
    // 依次读取结构体信息并根据type类型载入对象数据
    while(true){
        int type;
        ifs.read(reinterpret_cast<char*>(&type), sizeof(type));
        if(!ifs.good() || ifs.eof() ){
            break;
        }if(type == 0){
            // Person
            Person* p; // 指针，在if代码块之后释放，但是它指向的空间依然存在
            p = new Person(); // 初始化指针
            p->Deserialize(ifs);
            struct ObjWithType obj(type, *p);
            objWithTypes.push_back(obj);
        }else{
            // Book
            Book* b;
            b = new Book();
            b->Deserialize(ifs);
            struct ObjWithType obj(type, *b);
            objWithTypes.push_back(obj);
        }
    }ifs.close();
}
