#include <iostream>
#include "PluginInterface.h"

class WorldPlugin: public PluginInterface
{
    public:
        void printMessage(){
            std::cout << "Hello, world!" << std::endl;
        }
        
        void Help(){
            std::cout << "Plugin ID: 1\nPrints 'Hello, world!'\n";
        }

        int GetID(){
            return 1;
        }
};

// 导出插件
extern "C" PluginInterface* createPlugin(){
    // 返回一个PluginInterface指针类型，即返回插件的实例
    return new WorldPlugin;
}
