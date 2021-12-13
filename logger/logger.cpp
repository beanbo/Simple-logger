#pragma once
#include "pch.h"
#include "logger.h"


Logger::Logger(std::wstring sFileName /*= ""*/) : m_sFileName(sFileName), m_sFormat("**message** %%time%% %data% *prior*")
{
}

Logger::~Logger()
{
}

void Logger::SetFileName(std::wstring sFileName)
{
	if (m_sFileName.empty())
		return;

	m_sFileName = sFileName;
}

void Logger::SetFormat(std::string sFormat)
{
	m_sFormat = sFormat;
}

void Logger::PrintError(std::string sText)
{
	Print(sText, "Error");
}

void Logger::PrintDebug(std::string sText)
{
	Print(sText, "Debug");
}

void Logger::PrintTrace(std::string sText)
{
	Print(sText, "Trace");
}

void Logger::Print(std::string sText, std::string sType)
{
	std::ofstream logFile(m_sFileName, std::ios::app);

	std::time_t seconds = std::time(nullptr);
	tm* timeinfo = new tm();
	localtime_s(timeinfo, &seconds);

	char sCurrentDate[80];
	char sCurrentTime[80];

	const char* format = "%d %B %Y";
	strftime(sCurrentDate, 80, format, timeinfo);

	format = "%I:%M:%S";
	strftime(sCurrentTime, 80, format, timeinfo);

	std::string sOutput = m_sFormat;

	static const auto regMessage = std::regex("\\*\\*message\\*\\*");
	static const auto regDate = std::regex("%data%");
	static const auto regTime = std::regex("%%time%%");
	static const auto regType = std::regex("\\*prior\\*");

	sOutput = std::regex_replace(sOutput, regMessage, sText);
	sOutput = std::regex_replace(sOutput, regDate, sCurrentDate);
	sOutput = std::regex_replace(sOutput, regTime, sCurrentTime);
	sOutput = std::regex_replace(sOutput, regType, sType);

	logFile << sOutput << std::endl;

	logFile.close();
}

Logger& GetLogger()
{
	static Logger logger;
	return logger;
}

LOGGER_API void SetLoggerFileName(const wchar_t* sFileName)
{
	GetLogger().SetFileName(sFileName);
}

LOGGER_API void SetLoggerFormat(const char* sFormat)
{
	GetLogger().SetFormat(sFormat);
}

LOGGER_API void LoggerPrintError(const char* sText)
{
	GetLogger().PrintError(sText);
}

LOGGER_API void LoggerPrintDebug(const char* sText)
{
	GetLogger().PrintDebug(sText);
}

LOGGER_API void LoggerPrintTrace(const char* sText)
{
	GetLogger().PrintTrace(sText);
}
