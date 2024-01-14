#include<unistd.h>
#include<cstdlib>
#include<iostream>
#include<arpa/inet.h>
#include<cstring>

#include"IClient.h"

IClient::~IClient(){
    close(clientSocket);
}

void IClient::Connect(const char* serverIp, int serverPort){
    // 创建套接字: IPv4+stream+TCP
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    // 错误信息输出
    if(clientSocket == -1){
        std::cout << "Error creating socket:" << strerror(errno) << std::endl;
        exit(EXIT_FAILURE); // 发生错误退出程序
    }

    // 请求服务器建立连接
    serverAddress.sin_family = AF_INET; // IPv4
    serverAddress.sin_addr.s_addr = inet_addr(serverIp); // 本地服务器
    serverAddress.sin_port = htons(serverPort); // 端口
    // 错误输出
    if(connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(sockaddr_in)) == -1){
        std::cout << "Error connecting server " << inet_ntoa(serverAddress.sin_addr) << ": " << ntohs(serverAddress.sin_port) << std::endl;
        close(clientSocket);
        exit(EXIT_FAILURE); // 发生错误退出程序
    }else{
        std::cout << "Connected to server " << inet_ntoa(serverAddress.sin_addr) << ": " << ntohs(serverAddress.sin_port) << std::endl;
    }

}

