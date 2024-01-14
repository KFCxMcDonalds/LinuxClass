#pragma once // 防止重复引用

#include<netinet/in.h>
#include<unistd.h>

// Server抽象类，提取出server应该有的属性、方法
class IServer
{
    public:
        virtual ~IServer();// 析构函数，用来close socket
        virtual void Bind(const char* ip, int port); // 抽象函数
        virtual void Listen(int backlog);
        virtual void Start() = 0; // 纯虚函数 listen+accept+echo
    protected:
        int serverSocket; // 存储server的socket信息
        int clientSocket; // 存储当前连接的client的socket信息
        sockaddr_in serverAddress; // 存储server的地址信息
        sockaddr_in clientAddress; // 存储当前连接的client的地址信息
};

