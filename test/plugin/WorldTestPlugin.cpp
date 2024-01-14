#include <iostream>
#include "testPluginInterface.h"

class WorldTestPlugin : public TestPluginInterface {
public:
    void executePlugin() override {
        std::cout << "Hello, world!" << std::endl;
    }
};

extern "C" TestPluginInterface* createPlugin() {
    return new WorldTestPlugin();
}
