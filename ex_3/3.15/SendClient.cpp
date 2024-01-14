#include<iostream>
#include<cstring>
#include<arpa/inet.h>
#include<unistd.h>

#include"SendClient.h"

SendClient::SendClient(){}

void SendClient::Start(){
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
    SendClient sendClient;
    sendClient.Connect("127.0.0.1", 8000);
    sendClient.Start();
}
