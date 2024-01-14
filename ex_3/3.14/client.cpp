#include<iostream>
#include<cstring>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

class Client
{
    public:
        Client(const char* serverIp, int serverPort); // 构造函数，默认IPv4+stream+TCP
        ~Client(); // 析构函数
        void start();
    private:
        int clientSocket;
        sockaddr_in serverAddress;
};

Client::Client(const char* serverIp, int serverPort){
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

Client::~Client(){
    close(clientSocket);
}

void Client::start(){
    // 循环，已知可以向服务其发送消息，直到输入exit
    char buf[1024];
    while(true){
        // 向服务器发送信息
        // 要发送的信息
        std::cout << "请输入要发送给服务器的消息：（输入exit退出）" << std::endl;
        std::cin.getline(buf, sizeof(buf));

        // 发送并输出错误信息
        if(write(clientSocket, &buf, sizeof(buf)) == -1){
            std::cout << "Error sending message to server " << inet_ntoa(serverAddress.sin_addr) << ": " << ntohs(serverAddress.sin_port) << std::endl;
            close(clientSocket);
            exit(EXIT_FAILURE); // 发生错误退出程序
        }

        // 检查是否退出
        if(strcmp(buf, "exit") == 0) break;

        // 接收服务器发送的消息并显示
        memset(&buf, 0, sizeof(buf));
        int sizeRead;
        if((sizeRead = read(clientSocket, &buf, sizeof(buf))) == -1){
            std::cout << "Error recieving messages from server " << inet_ntoa(serverAddress.sin_addr) << ": " << ntohs(serverAddress.sin_port) << std::endl;
            close(clientSocket);
            exit(EXIT_FAILURE); // 发生错误退出程序
        }else if(sizeRead > 0) {
            std::cout << "Recieved message:" << std::endl << buf << std::endl;
        }
    }
}

int main()
{
    Client client("127.0.0.1", 8000);
    client.start();
}
