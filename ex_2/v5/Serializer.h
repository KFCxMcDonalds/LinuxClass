#pragma once // 防止重复引用

#include<vector>

#include"Serializable.h"

using namespace std;

class Serializer{
    public:
        static void serialize(vector<Serializable*>& pObjs, string filename);
        static void deserialize(vector<Serializable*>& pObjs, string filename);
};
