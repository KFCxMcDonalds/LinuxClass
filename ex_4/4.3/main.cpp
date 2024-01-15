#include <iostream>
#include <dlfcn.h>
#include <dirent.h>
#include <vector>
#include <string>

#include "PluginInterface.h"

PluginInterface* loadPluginByID(int pluginID);

int main(int argc, char* argv[]){
    // main help
    if(argc == 2 && std::string(argv[1]) == "help"){
        // 如果输入./main help
        std::cout << "Usage: ./main FuncID\n";
        std::cout << "Available FuncIDs:\n";
        //遍历plugins，输出可用的FuncID
        for(int i = 1; i <= 2; ++i){
            PluginInterface* plugin = loadPluginByID(i);
            if(plugin != nullptr){
                plugin -> Help();
                delete plugin; // 只用来输出帮助信息，所以使用结束后删除
            }
        }
        // 完成输出help帮助信息，退出程序
        return 0;
    }
    else if (argc != 2){
        // 没有指定插件ID
        std::cerr << "Usage: ./main FuncID\n";
        return -1;
    }

    // ./main ID
    int pluginID = std::stoi(argv[1]); // 获取命令行输入的ID
    // 加载插件byID
    PluginInterface* plugin = loadPluginByID(pluginID);
    if(plugin != nullptr){
        plugin -> printMessage();
        delete plugin;
    }else{
        std::cerr << "Invalid FuncID\n";
        return -1;
    }

    return 0;
}

PluginInterface* loadPluginByID(int pluginID){
    // 插件的.so名称用pluginID来命名，方便调用
    std::string pluginPath =  "./Plugin" + std::to_string(pluginID) + ".so";

    void* pluginHandle = dlopen(pluginPath.c_str(), RTLD_LAZY);
    if(pluginHandle != nullptr){
        typedef PluginInterface* (*CreatePlugin)();
        CreatePlugin createPlugin = reinterpret_cast<CreatePlugin>(dlsym(pluginHandle, "createPlugin"));
        if(createPlugin != nullptr){
            PluginInterface* plugin = createPlugin();
            return plugin;
        }
    }
    return nullptr; // 打开失败
}
