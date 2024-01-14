#pragma once

class PluginInterface{
    // 插件的接口，派生类重载PrintMessage来实现打印不同的消息
    public:
        virtual ~PluginInterface(){}
        virtual void printMessage() = 0; // 具体功能的纯虚函数，由派生类实现
        virtual void Help() = 0; // 插件的帮助信息
        virtual int GetID() = 0; // 获取插件的ID
};
