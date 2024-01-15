#include<iostream>
#include<arpa/inet.h>
#include<cstring>

#include"EchoServer.h"

EchoServer::EchoServer(){}

void EchoServer::Start(){
    // server将一直开启，监听请求
    while(true){
        // 接收连接请求
        socklen_t clientAddressLength = sizeof(clientAddress);
        // 从ESTABLISHED队列中取出一个连接
        clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
        // 输出错误信息
        if(clientSocket == -1){
            std::cout << "Error accepting connection:" << "client IP: " << inet_ntoa(clientAddress.sin_addr) << strerror(errno) << std::endl;
            close(serverSocket);
            exit(EXIT_FAILURE); // 发生错误退出程序
        }else{
            std::cout << "Connection accepted from " << inet_ntoa(clientAddress.sin_addr) << std::endl;
        }

        // Echo:读取和回送数据
        char buffer[1024];
        int sizeRead;
        while((sizeRead = read(clientSocket, buffer, sizeof(buffer))) > 0){
            if(strcmp(buffer, "exit") == 0){
                std::cout << "Client " << inet_ntoa(clientAddress.sin_addr) << " exits." << std::endl;
                break;
            }
            write(clientSocket, buffer, sizeof(buffer));
            // server的输出
            std::cout << "Recieving message from " << inet_ntoa(clientAddress.sin_addr) << std::endl << buffer << std::endl;
        }if(sizeRead == -1){
            std::cout << "Error recieving message from "<< inet_ntoa(clientAddress.sin_addr) << strerror(errno) << std::endl;
            close(serverSocket);
            close(clientSocket);
            exit(EXIT_FAILURE); // 发生错误退出程序
        }
        close(clientSocket);
    }
}

int main()
{
    EchoServer echoServer;
    echoServer.Bind("0.0.0.0", 8000); // 调用的是接口中的Bind函数
    echoServer.Listen(5);
    echoServer.Start();

    return 0;
}


