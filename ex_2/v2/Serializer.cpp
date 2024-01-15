#include<iostream>
#include<fstream>
#include<vector>

#include"Serializer.h"

using namespace std;

void Serializer::serialize(vector<Person>& people, const char* filename){
    // 根据文件名以二进制模式创建文件用以存放对象信息
    ofstream ofs(filename, ios::binary);
    // 从vector<Person>中遍历对象并依次存入文件
    for(Person& p: people){
        p.Serialize(ofs);
    }ofs.close();
}

void Serializer::deserialize(vector<Person>& people, const char* filename){
    // 根据文件名以二进制模式打开文件
    ifstream ifs(filename, ios::binary);
    // 依次读取对象信息
    Person p;
    while(p.Deserialize(ifs)){
        people.push_back(p);
    }
    ifs.close();
}
