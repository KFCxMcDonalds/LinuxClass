#pragma once
#include <string>

class FileStatPluginInterface
{
    public:
        virtual ~FileStatPluginInterface(){}
        virtual void performStat(const std::string& filename) = 0; // 实现不同的统计功能
};
