#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <ios>

class Log
{
public:
	enum Level
	{
		DEBUG,
		RELEASE,
		INFO,
		ERROR
	};
private:

	static std::ofstream m_out;
	static Level m_logLevel;

public:

	static void SetLogPath(const std::string& path)
	{
		m_out.open(path, std::ios::app);
	}

	static void SetLogLevel(Level logLevel)
	{
		m_logLevel = logLevel;
	}

	static void Info()
	{
		time_t t = time(nullptr);
		tm ptm = *localtime(&t);
		if (m_logLevel == Level::INFO) {
			std::cerr << "\x1b[32m" << "[INFO]["<< std::put_time(&ptm, "%T") << "]Hello World" << "\x1b[0m" << std::endl;
			m_out << "{I}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]Hello World" << std::endl;
		}
	}

	static void Debug()
	{
		time_t t = time(nullptr);
		tm ptm = *localtime(&t);
		if (m_logLevel == Level::DEBUG) {
			std::cerr << "\x1b[38;5;244m" << "[DEBUG][" << std::put_time(&ptm, "%T") << "]Program is running" << "\x1b[0m" << std::endl;
			m_out << "{D}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]Program is running" << std::endl;
		}
	}

	static void Error()
	{
		time_t t = time(nullptr);
		tm ptm = *localtime(&t);
		if (m_logLevel == Level::ERROR) {
			std::cerr << "\x1b[31m" << "[ERROR#00][" << std::put_time(&ptm, "%T") << "]Invalid data type" << "\x1b[0m" << std::endl;
			m_out << "[[ERROR#00][" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]Invalid data type" << std::endl;
		}
	}

	static void Release()
	{
		time_t t = time(nullptr);
		tm ptm = *localtime(&t);
		if (m_logLevel == Level::RELEASE) {
			std::cerr << "\x1b[38;5;244m" << "[RELEASE][" << std::put_time(&ptm, "%T") << "]Program is running" << "\x1b[0m" << std::endl;
			m_out << "{R}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]Program is running" << std::endl;
		}
	}
	static void End()
	{
		time_t t = time(nullptr);
		tm ptm = *localtime(&t);
		std::cerr << "\x1b[38;5;244m" << "[END][" << std::put_time(&ptm, "%T") << "]Program ended" << "\x1b[0m" << std::endl;
		m_out << "{0}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]Program ended" << std::endl;
	}
};