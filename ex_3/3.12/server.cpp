#include<iostream>
#include<cstring>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main()
{
    // 创建套接字: IPv4+stream+TCP
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // 错误信息输出
    if(serverSocket == -1){
        std::cout << "Error creating socket:" << strerror(errno) << std::endl;
        return -1;
    }

    // 绑定服务器的IP+port到serverSocket
    // 先定义sockaddr_in*
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET; // IPv4
    serverAddress.sin_addr.s_addr= inet_addr("0.0.0.0"); // 本地
    serverAddress.sin_port = htons(8000); // 绑定到8000端口
    // 绑定serverSocket & 错误信息输出
    if(bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(sockaddr_in)) == -1){
        std::cout << "Error binding socket." << strerror(errno) << std::endl;
        close(serverSocket);
        return -1;
    }

    // 监听连接请求并输出错误信息
    if(listen(serverSocket, 5) == -1){ // 最大连接量5
        std::cout << "Error listening for connection:" << strerror(errno) << std::endl;
        close(serverSocket);
        return -1;
    }else{
        std::cout << "Server listening on port 8000..." << std::endl;
    }

    // server将一直开启，监听请求
    while(true){
        // 接收连接请求
        // 创建clientAddr来存储用户地址信息
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        // 从ESTABLISHED队列中取出一个连接
        int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
        // 输出错误信息
        if(clientSocket == -1){
            std::cout << "Error accepting connection:" << "client IP: " << inet_ntoa(clientAddress.sin_addr) << strerror(errno) << std::endl;
            close(serverSocket);
            return -1;
        }else{
            std::cout << "Connection accepted from " << inet_ntoa(clientAddress.sin_addr) << std::endl;
        }

        // 读取和回送数据
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
            return -1;
        }
        close(clientSocket);
    }
    return 0;
}





