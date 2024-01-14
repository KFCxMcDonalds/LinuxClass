#pragma once

#include <map>
#include <string>
#include <fstream>

class TestStatus {
public:
    void updatePluginStatus(const std::string& pluginName, const std::string& status);
    void printPluginTable(const char* clientIP, int clientPort) const;
    void serialize(const std::string& filename) const;
    void deserialize(const std::string& filename);

private:
    std::map<std::string, std::string> pluginTable;  // 插件状态，键为客户端信息和插件名的组合，值为执行状态
};
