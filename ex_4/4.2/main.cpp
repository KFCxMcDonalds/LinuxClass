#include <iostream>
#include <dlfcn.h>
#include <dirent.h>
#include <vector>
#include <string>

#include "plugin/PluginInterface.h" 

typedef PluginInterface* (*CreatePlugin)(); // CreatePluign，创建插件对象的函数指针类型
typedef void (*DestroyPlugin)(PluginInterface*); // DestroyPluign，删除插件的函数指针类型                                            

// 函数：加载plugin/文件加下的所有插件
std::vector<PluginInterface*> loadPlugins(const std::string& directory);

int main(){
    // 加载插件
    std::vector<PluginInterface*> plugins = loadPlugins("plugin");

    // 使用插件
    for(auto plugin: plugins){
        plugin -> printMessage();
    }

    return 0;
}

std::vector<PluginInterface*> loadPlugins(const std::string& directory){
    // 创建一个vector存储导入的插件类
    std::vector<PluginInterface*> plugins;

    DIR* dir = opendir(directory.c_str()); // 打开插件文件
    if(dir){
        // 成功打开，遍历插件
        struct dirent* entry; // 遍历插件entry
        while((entry = readdir(dir)) != nullptr){
            std::string filename = entry -> d_name; // 每一个插件文件的名字
            // 判断文件的结尾是不是.so，如果是就载入
            if(filename.length() > 3 && filename.substr(filename.length() - 3) == ".so"){
                std::string pluginPath = directory + "/" + filename;
                // 开始插件载入的流程
                void* pluginHandle = dlopen(pluginPath.c_str(), RTLD_LAZY);
                if(pluginHandle != nullptr){
                    typedef PluginInterface* (*CreatePluign)();
                    CreatePlugin createPlugin = reinterpret_cast<CreatePlugin>(dlsym(pluginHandle, "createPlugin"));
                    if(createPlugin != nullptr){
                        PluginInterface* plugin = createPlugin();
                        plugins.push_back(plugin);
                    }
                }
            }
        }
        closedir(dir);
    }
    return plugins;
}
