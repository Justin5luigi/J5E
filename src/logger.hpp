#pragma once

#include <fstream>
#include <string>
//#include <bitset>

#define LOG_INFO 1
#define LOG_DEBUG 2
#define LOG_ERROR 3

//#define LOG_CONSOLE_ONLY 1
//#define LOG_FILE_ONLY 2
//#define LOG_BOTH 3


class Logger 
{
    public:
        //Logger(const char* logPath);
        //~Logger();
        static void SetLogPath(const char* path);
        static void Close();
        static void Log(int type, std::string msg);
        static std::ofstream logFile;
        //static void SetLoggingType(int type);

    private:
        //static const std::string levels[3]; 
        //static std::bitset<2> logTypeMask;
};
