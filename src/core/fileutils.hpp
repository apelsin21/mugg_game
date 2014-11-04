#ifndef FILEUTILS_HPP
#define FILEUTILS_HPP

#include <string>
#include <fstream>
#include <iostream>

namespace mugg {
    namespace io {
        bool LoadTextFromFile(const std::string&, std::string&);
        bool LoadTextFromFile(const char*, const char*&);
    }
}

#endif
