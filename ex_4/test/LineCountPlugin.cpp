#include <iostream>
#include <fstream>
#include <string>

#include "FileStatPluginInterface.h"

class LineCountPlugin: public FileStatPluginInterface
{
    public:
        void performStat(const std::string& filename){
            // 打开文件
            std::ifstream file(filename);
            if(file.is_open()){
                // 成功打开继续程序
                int lineCount = 0;
                std::string line;
                while(std::getline(file, line)){
                    // 成功读取文件的一行
                    ++lineCount;
                }
                // 输出行数
                std::cout << "Line count in file '" << filename << "': " << lineCount << std::endl;
            }else{
                // 打开文件失败，输出错误信息
                std::cerr << "Error opening file: " << filename << std::endl;
            }
        }
};

extern "C" FileStatPluginInterface* createPlugin(){
    return new LineCountPlugin;
}
