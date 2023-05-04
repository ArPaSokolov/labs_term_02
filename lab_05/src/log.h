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
		ERROR,
		END
	};
private:

	static std::ofstream m_out;
	static Level m_logLevel;
	static bool flag[4];

public:
	
	static void SetLogPath(const std::string& path)
	{
		m_out.open(path, std::ios::app);
	}

	static void SetLogLevel(Level logLevel)
	{
		m_logLevel = logLevel;
	}

	static void LevelFlag() {
		std::cout << "DEBUG, RELEASE, INFO, ERROR: ";
		for (int i = 0; i < 4; i++) {
			std::cin >> flag[i];
		}
	}

	static void AutoLog(int logLevel, const std::string& msg) {
		if (Log::flag[logLevel] == true) {
			Log::SetLogLevel(static_cast<Log::Level>(logLevel));
			if (m_logLevel == Level::INFO) {
				time_t t = time(nullptr);
				tm ptm = *localtime(&t);
				std::cerr << "\x1b[32m" << "[INFO][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
				m_out << "{I}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
			}
		}
		if (flag[logLevel] == true) {
			Log::SetLogLevel(static_cast<Log::Level>(logLevel));
			if (m_logLevel == Level::DEBUG) {
				time_t t = time(nullptr);
				tm ptm = *localtime(&t);
				std::cerr << "\x1b[38;5;244m" << "[DEBUG][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
				m_out << "{D}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
			}
		}
		if (flag[logLevel] == true) {
			Log::SetLogLevel(static_cast<Log::Level>(logLevel));
			if (m_logLevel == Level::RELEASE) {
				time_t t = time(nullptr);
				tm ptm = *localtime(&t);
				std::cerr << "\x1b[38;5;244m" << "[RELEASE][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
				m_out << "{R}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
			}
		}
	}

	static void AutoLog(int logLevel, const std::string& msg, const std::string& enmbr) {
		if (flag[logLevel] == true) {
			Log::SetLogLevel(static_cast<Log::Level>(logLevel));
			if (m_logLevel == Level::ERROR) {
				time_t t = time(nullptr);
				tm ptm = *localtime(&t);
				std::cerr << "\x1b[31m" << "[ERROR#" << enmbr << "][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
				m_out << "[[ERROR#" << enmbr << "][" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
			}
		}
	}

	static void End(int logLevel, const std::string& msg)
	{
		Log::SetLogLevel(static_cast<Log::Level>(logLevel));
		if (m_logLevel == Level::END) {
			time_t t = time(nullptr);
			tm ptm = *localtime(&t);
			std::cerr << "\x1b[38;5;244m" << "[END][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
			m_out << "{0}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
		}
	}
};