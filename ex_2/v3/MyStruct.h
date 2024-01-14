#pragma once

#include<iostream>

#include"Person.h"
#include"Book.h"

struct ObjWithType{
    int type; // 0:Person 1:Book
    void* pObj; // 指向对象的指针

    // 结构体的构造函数
    ObjWithType(int t, Person& p): type(t), pObj(&p) {}
    ObjWithType(int t, Book& b): type(t), pObj(&b) {}
    // 输出函数
    void output(){
        // string type_name;
        if(type == 0){
            cout << "type:" << "Person" << endl;
            Person* pp = static_cast<Person*>(pObj);
            pp->output();
        }else{
            cout << "type:" << "Book" << endl;
            Book* pb = static_cast<Book*>(pObj);
            pb->output();
        }
    }
};
