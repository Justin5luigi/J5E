#pragma once

#include <fstream>
#include <string>

#define LOG_INFO 1
#define LOG_DEBUG 2
#define LOG_ERROR 3


class Logger 
{
    public:
        //Logger(const char* logPath);
        //~Logger();
        static void SetLogPath(const char* path);
        static void Close();
        static void Log(int type, std::string msg);
        static std::ofstream logFile;

    private:
};
