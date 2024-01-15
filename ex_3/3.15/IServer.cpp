#include<unistd.h>
#include<cstdlib>
#include<iostream>
#include<arpa/inet.h>
#include<cstring>

#include"IServer.h"

IServer::~IServer(){
    close(serverSocket);
}

void IServer::Bind(const char* ip, int port){
    // 接口函数中的Bind默认是IPv4+stream+TCP，在派生类中可以重载该函数为不同配置
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // 错误信息输出
    if(serverSocket == -1){
        std::cout << "Error creating socket:" << strerror(errno) << std::endl;
        exit(EXIT_FAILURE); // 发生错误退出程序
    }

    // 绑定服务器的IP+port到serverSocket
    // 先定义sockaddr_in*
    serverAddress.sin_family = AF_INET; // IPv4
    serverAddress.sin_addr.s_addr= inet_addr(ip); // 本地
    serverAddress.sin_port = htons(port); // 绑定到8000端口
    // 绑定serverSocket & 错误信息输出
    if(bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(sockaddr_in)) == -1){
        std::cout << "Error binding socket." << strerror(errno) << std::endl;
        close(serverSocket);
        exit(EXIT_FAILURE); // 发生错误退出程序
    }
}

void IServer::Listen(int backlog){
    // 监听连接请求并输出错误信息
    if(listen(serverSocket, backlog) == -1){
        std::cout << "Error listening for connection:" << strerror(errno) << std::endl;
        close(serverSocket);
        exit(EXIT_FAILURE); // 发生错误退出程序
    }else{
        std::cout << "Server listening on port 8000..." << std::endl;
    }
}
