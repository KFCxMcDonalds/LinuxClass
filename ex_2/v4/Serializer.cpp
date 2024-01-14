#include<iostream>
#include<fstream>
#include<vector>

#include"Serializer.h"
#include"Person.h"
#include"Book.h"
#include"City.h"

using namespace std;

void Serializer::serialize(vector<Serializable*>& pObjs, const char* filename){
    // 根据文件名以二进制模式创建文件用以存放对象信息
    ofstream ofs(filename, ios::binary);
    // 遍历vector<Serializable*>中的对象并依次调用Serialize方法存入文件
    for(Serializable*& pObj: pObjs){
        pObj->Serialize(ofs);
    }ofs.close();
}

void Serializer::deserialize(vector<Serializable*>& pObjs, const char* filename){
    // 根据文件名以二进制模式打开文件
    ifstream ifs(filename, ios::binary);
    // 依次读取结构体信息并根据type类型载入对象数据
    while(true){
        int type;
        ifs.read(reinterpret_cast<char*>(&type), sizeof(type));
        if(!ifs.good() || ifs.eof() ){
            break; // 如果读取失败或者文件到尾，退出循环
        }
        Serializable* pObj;
        switch(type){
            case 0:
                pObj = new Person();
                break;
            case 1:
                pObj = new Book();
                break;
            case 2:
                pObj = new City();
                break;
        }
        pObj->Deserialize(ifs);
        pObjs.push_back(pObj);
    }ifs.close();
}
