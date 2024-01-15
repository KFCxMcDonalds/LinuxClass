#include <iostream>
#include <fstream>
#include <sstream>
#include "testPluginInterface.h"

class FileStatTestPlugin : public TestPluginInterface {
public:
    void executePlugin() override {
        std::string fileName;
        std::cout << "Enter the file name: ";
        std::cin >> fileName;

        std::ifstream file(fileName);
        if (file.is_open()) {
            int lineCount = 0;
            std::string line;
            while (getline(file, line)) {
                ++lineCount;
            }

            std::cout << "File " << fileName << " has " << lineCount << " lines." << std::endl;
        } else {
            std::cout << "Failed to open file: " << fileName << std::endl;
        }
    }
};

extern "C" TestPluginInterface* createPlugin() {
    return new FileStatTestPlugin();
}
