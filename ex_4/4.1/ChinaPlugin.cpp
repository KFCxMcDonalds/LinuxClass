#include <iostream>
#include "PluginInterface.h"

class ChinaPlugin: public PluginInterface
{
    public:
        void printMessage(){
            std::cout << "Hello, china!" << std::endl;
        }
};

// 导出插件
extern "C" PluginInterface* createPlugin(){
    // 返回一个PluginInterface指针类型，即返回插件的实例
    return new ChinaPlugin;
}

extern "C" void destroyPlugin(PluginInterface* plugin){
    // 删除一个插件
    delete plugin;
}

