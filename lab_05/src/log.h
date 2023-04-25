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

	static void Info(const std::string& msg)
	{
		time_t t = time(nullptr);
		tm ptm = *localtime(&t);
		if (m_logLevel == Level::INFO) {
			std::cerr << "\x1b[32m" << "[INFO]["<< std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
			m_out << "{I}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
		}
	}

	static void Debug(const std::string& msg)
	{
		time_t t = time(nullptr);
		tm ptm = *localtime(&t);
		if (m_logLevel == Level::DEBUG) {
			std::cerr << "\x1b[38;5;244m" << "[DEBUG][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
			m_out << "{D}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
		}
	}

	static void Error(const std::string& enmbr, const std::string& msg)
	{
		time_t t = time(nullptr);
		tm ptm = *localtime(&t);
		if (m_logLevel == Level::ERROR) {
			std::cerr << "\x1b[31m" << "[ERROR#" << enmbr << "][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
			m_out << "[[ERROR#" << enmbr <<"][" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
		}
	}

	static void Release(const std::string& msg)
	{
		time_t t = time(nullptr);
		tm ptm = *localtime(&t);
		if (m_logLevel == Level::RELEASE) {
			std::cerr << "\x1b[38;5;244m" << "[RELEASE][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
			m_out << "{R}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
		}
	}
	static void End(const std::string& msg)
	{
		time_t t = time(nullptr);
		tm ptm = *localtime(&t);
		std::cerr << "\x1b[38;5;244m" << "[END][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
		m_out << "{0}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
	}
};