#include<iostream>
#include<vector>

#include"Person.h"

using namespace std;

class Serializer{
    public:
        static void serialize(vector<Person>& people, const char* filename);
        static void deserialize(vector<Person>& people, const char* filename);
};
