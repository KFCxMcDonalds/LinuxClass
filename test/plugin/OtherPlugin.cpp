#include <iostream>
#include "testPluginInterface.h"

class OtherPlugin: public TestPluginInterface
{
    public:
        void executePlugin(){
            std::cout << "Some other message from the OtherPlugin." << std::endl;
        }
};

// 导出插件
extern "C" TestPluginInterface* createPlugin() {
    return new OtherPlugin();
}
