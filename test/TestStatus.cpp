#include "TestStatus.h"
#include <iostream>

void TestStatus::updatePluginStatus(const std::string& pluginName, const std::string& status) {
    // 直接插入或更新
    pluginTable[pluginName] = status;
}

void TestStatus::printPluginTable(const char* clientIP, int clientPort) const {
    // 打印客户信息
    std::cout << "Client Info: " << clientIP << std::endl;

    // 打印客户插件表格头部
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "| Plugin Name | Status |" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    // 打印客户插件表格内容
    for (const auto& entry : pluginTable) {
        std::cout << "| " << entry.first << " | " << entry.second << " |" << std::endl;
    }

    // 打印客户插件表格底部
    std::cout << "--------------------------------------" << std::endl;
}

void TestStatus::serialize(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    // 写入插件表格的大小
    size_t tableSize = pluginTable.size();
    file.write(reinterpret_cast<const char*>(&tableSize), sizeof(size_t));

    // 依次写入插件名和状态
    for (const auto& entry : pluginTable) {
        size_t nameSize = entry.first.size();
        size_t statusSize = entry.second.size();

        // 写入插件名的大小和内容
        file.write(reinterpret_cast<const char*>(&nameSize), sizeof(size_t));
        file.write(entry.first.c_str(), nameSize);

        // 写入插件状态的大小和内容
        file.write(reinterpret_cast<const char*>(&statusSize), sizeof(size_t));
        file.write(entry.second.c_str(), statusSize);
    }

    file.close();
}

void TestStatus::deserialize(const std::string& filename) {
    // 清空当前的插件表格
    pluginTable.clear();

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    // 读取插件表格的大小
    size_t tableSize;
    file.read(reinterpret_cast<char*>(&tableSize), sizeof(size_t));

    // 依次读取插件名和状态
    for (size_t i = 0; i < tableSize; ++i) {
        size_t nameSize;
        size_t statusSize;

        // 读取插件名的大小和内容
        file.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
        std::string pluginName(nameSize, '\0');
        file.read(&pluginName[0], nameSize);

        // 读取插件状态的大小和内容
        file.read(reinterpret_cast<char*>(&statusSize), sizeof(size_t));
        std::string status(statusSize, '\0');
        file.read(&status[0], statusSize);

        // 更新插件表格
        pluginTable[pluginName] = status;
    }

    file.close();
}
