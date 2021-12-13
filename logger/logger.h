#pragma once
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <ctime>

#define LOGGER_API __declspec(dllexport)

class Logger
{
public:
    Logger(std::wstring sFileName = L"log.txt");

    ~Logger();

    void SetFileName(std::wstring sFileName);
    void SetFormat(std::string sFormat);

    void PrintError(std::string sText);
    void PrintDebug(std::string sText);
    void PrintTrace(std::string sText);

protected:
    void Print(std::string sText, std::string sType);

protected:
    std::wstring m_sFileName;
    std::string m_sFormat;
};


Logger& GetLogger();

// https://docs.microsoft.com/en-us/windows/win32/dlls/creating-a-simple-dynamic-link-library
#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

LOGGER_API void SetLoggerFileName(const wchar_t* sFileName);
LOGGER_API void SetLoggerFormat(const char* sFormat);
LOGGER_API void LoggerPrintError(const char* sText);
LOGGER_API void LoggerPrintDebug(const char* sText);
LOGGER_API void LoggerPrintTrace(const char* sText);

#ifdef __cplusplus
}
#endif