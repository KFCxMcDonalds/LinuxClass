#include<cstdlib>
#include<cstring>
#include<iostream>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

class Server
{
    public:
        Server(const char* ip, int port, int backlog); // 绑定server到本机指定端口
        ~Server(); // 析构函数
        void start(); // 开启server服务
    private:
        int serverSocket; // 存储server的socket信息
        int clientSocket; // 存储当前连接的client的socket信息
        sockaddr_in serverAddress; // 存储server的地址信息
        sockaddr_in clientAddress; // 存储当前连接的client的地址信息
};

Server::Server(const char* ip, int port, int backlog){
    // 构造方法创建套接字: 默认使用IPv4+stream+TCP
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

    // 监听连接请求并输出错误信息
    if(listen(serverSocket, backlog) == -1){ // 最大连接量5
        std::cout << "Error listening for connection:" << strerror(errno) << std::endl;
        close(serverSocket);
        exit(EXIT_FAILURE); // 发生错误退出程序
    }else{
        std::cout << "Server listening on port 8000..." << std::endl;
    }
}

Server::~Server(){
    close(serverSocket);
}

void Server::start(){
    // server将一直开启，监听请求
    while(true){
        // 接收连接请求
        // 创建clientAddr来存储用户地址信息
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
            exit(EXIT_FAILURE); // 发生错误退出程序
        }
        close(clientSocket);
    }
}

int main()
{
    Server server("0.0.0.0", 8000, 5);
    server.start();

    return 0;
}
