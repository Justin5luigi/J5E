#include "logger.hpp"
#include <iostream>
#include <fstream>

//Logger::Logger(const char* logPath) 
//{
    //logFile.open(logPath);
//}

std::ofstream Logger::logFile;

void Logger::SetLogPath(const char* path)
{
    logFile.open(path);
}

void Logger::Log(int type, std::string msg)
{
    switch (type)
    {
        case LOG_INFO:
            std::cout << "INFO | " << msg << std::endl;
            logFile << "INFO | " << msg << std::endl;
            break;

        case LOG_DEBUG:
            std::cout << "DEBUG | " << msg << std::endl;
            logFile << "DEBUG | " << msg << std::endl;
            break;

        case LOG_ERROR:
            std::cout << "ERROR | " << msg << std::endl;
            logFile << "ERROR | " << msg << std::endl;

        default:
            break;

        
    }
}

void Logger::Close()
{
    logFile.close();
}

