#include <iostream>
#include "PluginInterface.h"

class ChinaPlugin: public PluginInterface
{
    public:
        void printMessage(){
            std::cout << "Hello, china!" << std::endl;
        }

        void Help(){
            std::cout << "Plugin ID: 2\nPrints 'Hello, china!'\n";
        }

        int GetID(){
            return 2;
        }
};

// 导出插件
extern "C" PluginInterface* createPlugin(){
    // 返回一个PluginInterface指针类型，即返回插件的实例
    return new ChinaPlugin;
}

