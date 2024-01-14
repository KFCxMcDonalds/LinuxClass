#pragma once // 防止重复引用

#include<netinet/in.h>

// client接口
class IClient
{
    public:
        virtual ~IClient(); // 析构函数，一般用来close socket
        virtual void Connect(const char* serverIp, int serverPort); // 抽象函数
        virtual void Start() = 0; // 纯虚函数
    protected:
        int clientSocket;
        sockaddr_in serverAddress;
};

