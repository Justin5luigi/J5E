#include "logger.hpp"
#include <iostream>
#include <fstream>

//Logger::Logger(const char* logPath) 
//{
    //logFile.open(logPath);
//}

std::ofstream Logger::logFile;
//std::string levels[3] = {"Info", "Debug", "ERROR"};
//std::bitset<2> logTypeMask;

void Logger::SetLogPath(const char* path)
{
    logFile.open(path);
}

void Logger::Log(int type = LOG_INFO, std::string msg = "")
{
    std::string levels[3] = {"Info", "Debug", "ERROR"};
    std::string message = levels[type - 1] + " | " + msg + "\n";
    //if ((logTypeMask & 0b01) == 0b01) { std::cout << message; }
    //if ((logTypeMask & 0b10) == 0b10) { logFile << message; }
    std::cout << message;
    logFile << message;
}

void Logger::Close()
{
    logFile.close();
}

/*
void Logger::SetLoggingType(int type) 
{
     switch(type)
     {
         case LOG_CONSOLE_ONLY:
             logTypeMask.set(0);
             logTypeMask.reset(1);
             break;

         case LOG_FILE_ONLY:
             logTypeMask.reset(0);
             logTypeMask.set(1);
             break;

         case LOG_BOTH:
             logTypeMask.set(0);
             logTypeMask.set(1);
             break;

         default:
             std::cout << "Error: Undefined logging type" << std::endl;
             logFile << "Error: Undefinded logging type" << std::endl;
     }
} 
*/
