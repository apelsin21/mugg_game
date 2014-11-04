#include "core/fileutils.hpp"

bool mugg::io::LoadTextFromFile(const std::string& filepath, std::string &outString) {
    std::string data;
    std::ifstream textStream(filepath, std::ios::in);

    if(textStream.is_open()) {
        std::string line;

        while(std::getline(textStream, line)) {
            data += "\n" + line;
        }

        textStream.close();
    } else {
        return false;
    }

    outString = data;

    return true;
}

bool mugg::io::LoadTextFromFile(const char* filepath, const char* &outString) {
    std::string data;
    
    if(!mugg::io::LoadTextFromFile(filepath, data)) {
        return false;
    }

    outString = data.c_str();

    return true;
}
