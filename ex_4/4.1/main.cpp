#include <iostream>
#include <dlfcn.h>

#include "PluginInterface.h"

typedef PluginInterface* (*CreatePlugin)(); // CreatePluign，创建插件对象的函数指针类型
typedef void (*DestroyPlugin)(PluginInterface*); // DestroyPluign，删除插件的函数指针类型                                            

int main(){
    // 加载动态链接库
    void* pluginHandle = dlopen("./Plugin.so", RTLD_LAZY);
    if(pluginHandle == nullptr){
        // 打开ddl失败返回错误信息
        std::cerr << "Failed to load plugin: " << dlerror() << std::endl;
        return -1;
    }

    // 获取插件接口
    // 1. 创建插件对象函数
    CreatePlugin createPlugin = reinterpret_cast<CreatePlugin>(dlsym(pluginHandle, "createPlugin"));
    if(createPlugin == nullptr){
        // 返回插件函数地址失败打印错误信息
        std::cerr << "Failed to get createPlugin function: " << dlerror() << std::endl;
        dlclose(pluginHandle);
        return -1;
    }
    // 2. 删除插件函数
    DestroyPlugin destroyPlugin = reinterpret_cast<DestroyPlugin>(dlsym(pluginHandle, "destroyPlugin"));
    if(destroyPlugin == nullptr){
        // 返回插件函数地址失败打印错误信息
        std::cerr << "Failed to get destroyPlugin function: " << dlerror() << std::endl;
        dlclose(pluginHandle);
        return -1;
    }

    // 使用插件
    PluginInterface* plugin = createPlugin(); // plugin是需要调用的插件，是一个接口指针
    plugin->printMessage();

    // 卸载插件
    destroyPlugin(plugin);
    dlclose(pluginHandle);

    return 0;
}
