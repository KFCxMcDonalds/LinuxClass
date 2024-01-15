#pragma once // 防止重复引用

#include<iostream>
#include<vector>

#include"Person.h"
#include"Book.h"
#include"MyStruct.h"

using namespace std;

class Serializer{
    public:
        static void serialize(vector<ObjWithType>& objWithTypes, const char* filename);
        static void deserialize(vector<ObjWithType>& objWithTypes, const char* filename);
};
