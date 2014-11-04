#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <string>

namespace mugg {
    namespace core {
        enum LogLevel {
            Info,
            Warning,
            Error
        };

        static std::string Path = "log.txt";
        //Minimum level to print and write to disk
        static LogLevel MinLvl = LogLevel::Info;

        static void Log(LogLevel lvl, const std::string& msg) {
            if(lvl < MinLvl) {
                std::cout << "bajs\n";
                return;
            }
            
            std::string lvlString;

            switch(lvl) {
                case LogLevel::Info:
                    lvlString = "[Info]";
                    break;
                case LogLevel::Warning:
                    lvlString = "[Warning]";
                    break;
                case LogLevel::Error:
                    lvlString = "[Error]";
                    break;
                default:
                    lvlString = "[Unknown]";
                    break;
            }

            std::string finalString = lvlString;
            finalString += ": ";
            finalString += msg;
            finalString += "\n";
    
            std::cerr << finalString;
        }
    }
}

#endif
