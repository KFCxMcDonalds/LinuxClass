#include <iostream>
#include <dlfcn.h>
#include <vector>
#include <string>

#include "FileStatPluginInterface.h"

FileStatPluginInterface* loadPluginByID(int pluginID); // 通过ID加载插件

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./main PluginID filename\n";
        return 1;
    }

    int pluginID = std::stoi(argv[1]);
    std::string filename = argv[2];

    // 根据ID加载插件.so
    FileStatPluginInterface* plugin = loadPluginByID(pluginID);

    if (plugin != nullptr) {
        // 使用插件
        plugin->performStat(filename);

        delete plugin;
    } else {
        std::cerr << "Invalid PluginID\n";
        return 1;
    }

    return 0;
}

FileStatPluginInterface* loadPluginByID(int pluginID){
    std::string pluginPath = "./Plugin" + std::to_string(pluginID) + ".so";

    void* pluginHandle = dlopen(pluginPath.c_str(), RTLD_LAZY);
    if (pluginHandle != nullptr) {
        typedef FileStatPluginInterface* (*CreatePlugin)();
        CreatePlugin createPlugin = reinterpret_cast<CreatePlugin>(dlsym(pluginHandle, "createPlugin"));
        if (createPlugin != nullptr) {
            FileStatPluginInterface* plugin = createPlugin();
            return plugin;
        }
    }

    return nullptr;
}
