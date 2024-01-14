#include <iostream>
#include <fstream>
#include <string>

#include "FileStatPluginInterface.h"

class ByteCountPlugin: public FileStatPluginInterface
{
    public:
        void performStat(const std::string& filename){
            // 二进制模式打开文件
            std::ifstream file(filename, std::ios::binary);
            if(file.is_open()){
                // 成功打开继续程序
                // 计数文件的字节数
                file.seekg(0, std::ios::end);
                std::streampos fileSize = file.tellg();
                // 输出字节数
                std::cout << "Byte count in file '" << filename << "': " << fileSize << std::endl;
            }else{
                // 打开文件失败，输出错误信息
                std::cerr << "Error opening file: " << filename << std::endl;
            }
        }
};

extern "C" FileStatPluginInterface* createPlugin(){
    return new ByteCountPlugin;
}
