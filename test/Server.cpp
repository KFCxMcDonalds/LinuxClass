#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <map>

#include "TestStatus.h"

class Server {
public:
    Server(int port) : port(port) {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1) {
            perror("Error creating socket");
            exit(EXIT_FAILURE);
        }

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
            perror("Error binding to port");
            exit(EXIT_FAILURE);
        }

        if (listen(serverSocket, 10) == -1) {
            perror("Error listening for connections");
            exit(EXIT_FAILURE);
        }
    }

    void startListening() {
        std::cout << "Server listening on port " << port << std::endl;

        while (true) {
            int clientSocket = accept(serverSocket, nullptr, nullptr);
            if (clientSocket == -1) {
                perror("Error accepting connection");
                continue;
            }

            pthread_t thread;
            int* pClientSocket = new int(clientSocket);

            if (pthread_create(&thread, nullptr, handleClient, pClientSocket) != 0) {
                perror("Error creating thread");
                delete pClientSocket;
                close(clientSocket);
            }
        }
    }

    static void* handleClient(void* pClientSocket) {
        int clientSocket = *((int*)pClientSocket);
        delete pClientSocket;

        // 获取客户端信息
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        getpeername(clientSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
        int clientPort = ntohs(clientAddr.sin_port);

        std::cout << "Client connected from " << clientIP << std::endl;

        // 客户端插件表格，存储插件名和状态
        TestStatus clientTestStatus;

        while (true) {
            // 等待用户输入
            std::string userInput;
            std::cout << "[" << clientIP << "] Enter 'exit', 'migrate', 'load', or plugin name: ";
            std::cin >> userInput;

            if (userInput == "exit") {
                // 用户选择退出，发送 "exit" 给客户端并退出循环
                send(clientSocket, "exit", 4, 0);
                std::cout << "[" << clientIP << "] Exiting client thread" << std::endl;
                break;
            } else if (userInput == "migrate") {
                // 用户选择迁移，继续接收文件路径并发送给客户端
                std::string filepath;
                std::cout << "[" << clientIP << "] Enter migrate file path: ";
                std::cin >> filepath;

                std::string message = "migrate " + filepath;
                send(clientSocket, message.c_str(), message.size(), 0);
            } else if (userInput == "load") {
                // 用户选择加载，继续接收文件路径并发送给客户端
                std::string filepath;
                std::cout << "[" << clientIP << "] Enter load file path: ";
                std::cin >> filepath;

                std::string message = "load " + filepath;
                send(clientSocket, message.c_str(), message.size(), 0);

                // 直接从文件路径反序列化更新客户端插件表格
                clientTestStatus.deserialize(filepath);
                std::cout << "[" << clientIP << "] Updated testStatus from client" << std::endl;
                clientTestStatus.printPluginTable(clientIP, clientPort);
            } else {
                // 用户输入插件名字，发送插件名字给客户端
                send(clientSocket, userInput.c_str(), userInput.size(), 0);

                // 更新客户插件表格并打印
                clientTestStatus.updatePluginStatus(userInput, "running");
                clientTestStatus.printPluginTable(clientIP, clientPort);

                // 等待用户返回的 status
                char receivedStatus[256];
                ssize_t bytesRead = recv(clientSocket, receivedStatus, sizeof(receivedStatus), 0);
                if (bytesRead == -1) {
                    perror("Error receiving status");
                    break;
                } else if (bytesRead == 0) {
                    // 客户端关闭连接，退出循环
                    std::cout << "[" << clientIP << "] Client disconnected" << std::endl;
                    break;
                } else {
                    receivedStatus[bytesRead] = '\0';

                    // 更新客户插件表格的 status 并打印
                    clientTestStatus.updatePluginStatus(userInput, receivedStatus);
                    clientTestStatus.printPluginTable(clientIP, clientPort);
                }
            }
        }

        close(clientSocket);
        pthread_exit(nullptr);
    }

private:
    int serverSocket;
    int port;
    struct sockaddr_in serverAddr;
};

int main() {
    Server server(8080);
    server.startListening();

    return 0;
}
