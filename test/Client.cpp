#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <dlfcn.h>
#include <map>

#include "TestStatus.h"
#include "plugin/TestPluginInterface.h"

class Client {
public:
    Client(const char* ip, int port) : ip(ip), port(port) {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == -1) {
            perror("Error creating socket");
            exit(EXIT_FAILURE);
        }

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(ip);
        serverAddr.sin_port = htons(port);
    }

    void connectToServer() {
        if (::connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
            perror("Error connecting to server");
            exit(EXIT_FAILURE);
        }
        std::cout << "Connected to server " << inet_ntoa(serverAddr.sin_addr) << ": " << ntohs(serverAddr.sin_port) << std::endl;
    }

    void receiveAndExecutePlugin() {
        while (true) {
            char buffer[256];
            ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead == -1) {
                perror("Error receiving data");
                break;
            } else if (bytesRead == 0) {
                // 服务器关闭连接，退出循环
                break;
            } else {
                buffer[bytesRead] = '\0';

                if (std::string(buffer) == "exit") {
                    std::cout << "Received exit command. Closing connection." << std::endl;
                    break;
                } else if (std::string(buffer).find("migrate ") == 0) {
                    std::string filePath(buffer + 8); // Skip "migrate "
                    std::cout << "Received migrate command. Serializing to file: " << filePath << std::endl;
                    testStatus.serialize(filePath);
                } else if (std::string(buffer).find("load ") == 0) {
                    std::string filePath(buffer + 5); // Skip "load "
                    std::cout << "Received load command. Deserializing from file: " << filePath << std::endl;
                    testStatus.deserialize(filePath);
                    testStatus.printPluginTable(ip, port);
                } else {
                    std::cout << "Received plugin name: " << buffer << std::endl;

                    // 更新插件表格并设置状态为 "running"
                    testStatus.updatePluginStatus(buffer, "running");

                    // 执行插件
                    executePlugin(buffer);

                    // 发送插件执行完成的状态给服务器
                    sendPluginStatus(buffer, "finished");

                    // 打印插件表格内容
                    testStatus.printPluginTable(ip, port);
                }
            }
        }
    }

    void executePlugin(const char* pluginName) {
        // 构造动态链接库文件路径
        std::string pluginPath = "./plugin/" + std::string(pluginName) + ".so";

        // 加载动态链接库
        void* pluginHandle = dlopen(pluginPath.c_str(), RTLD_LAZY);
        if (!pluginHandle) {
            perror(dlerror());
            return;
        }

        // 查找插件接口
        typedef TestPluginInterface* (*CreatePlugin)();
        CreatePlugin createPlugin = reinterpret_cast<CreatePlugin>(dlsym(pluginHandle, "createPlugin"));
        if (!createPlugin) {
            std::cerr << "Error loading plugin interface: " << dlerror() << std::endl;
            dlclose(pluginHandle);
            return;
        }

        // 创建插件实例
        TestPluginInterface* plugin = createPlugin();

        // 执行插件功能
        plugin->executePlugin();

        // 释放插件资源
        delete plugin;
        dlclose(pluginHandle);
    }

    void sendPluginStatus(const char* pluginName, const char* status) {
        // 发送插件执行状态给服务器
        send(clientSocket, status, strlen(status), 0);

        // 更新插件表格并设置状态为 "finished"
        testStatus.updatePluginStatus(pluginName, "finished");
    }

    void closeConnection() {
        close(clientSocket);
    }

private:
    const char* ip;
    int port;
    int clientSocket;
    struct sockaddr_in serverAddr;
    TestStatus testStatus;  
};

int main() {
    Client client("127.0.0.1", 8080);
    client.connectToServer();

    // 接收并执行插件任务
    client.receiveAndExecutePlugin();

    // 关闭连接
    client.closeConnection();

    return 0;
}
