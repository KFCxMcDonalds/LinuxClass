#include <iostream>
#include "PluginInterface.h"

class OtherPlugin: public PluginInterface
{
    public:
        void printMessage(){
            std::cout << "Some other message from the OtherPlugin." << std::endl;
        }
};

// 导出插件
extern "C" PluginInterface* createPlugin(){
    // 返回一个PluginInterface指针类型，即返回插件的实例
    return new OtherPlugin;
}
