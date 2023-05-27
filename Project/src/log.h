#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <ios>
#include <sqlite3/sqlite3.h>

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
	static bool flag[4]; // поле для хранения "галочек"

public:
	
	static void SetLogPath(const std::string& path) // установливаем путь до файла с логами
	{
		m_out.open(path, std::ios::app);
	}

	static void SetLogLevel(Level logLevel) // установщик уровня доступа
	{
		m_logLevel = logLevel;
	}

	static void LevelFlag() { // метод для установки "галочек"
		std::cout << "DEBUG, RELEASE, INFO, ERROR: ";
		for (int i = 0; i < 4; i++) {
			std::cin >> flag[i]; // "1" - галочка стоити, "0" - не стоит
		}
	}

	static void AutoLog(int logLevel, const std::string& msg) { // автологгер
		if (Log::flag[INFO] == true) { // галочка на INFO стоит
			Log::SetLogLevel(static_cast<Log::Level>(logLevel)); // открываем уровень
			if (m_logLevel == Level::INFO) {  
				time_t t = time(nullptr); // время
				tm ptm = *localtime(&t); // время
				std::cerr << "\x1b[32m" << "[INFO][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
				m_out << "{I}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
			}
		}
		if (flag[DEBUG] == true) { // галочка на DEBUG стоит
			Log::SetLogLevel(static_cast<Log::Level>(logLevel)); // открываем уровень
			if (m_logLevel == Level::DEBUG) {
				time_t t = time(nullptr); // время
				tm ptm = *localtime(&t); // время
				std::cerr << "\x1b[38;5;244m" << "[DEBUG][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
				m_out << "{D}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
			}
		}
		if (flag[RELEASE] == true) { // галочка на RELEASE стоит
			Log::SetLogLevel(static_cast<Log::Level>(logLevel)); // открываем уровень
			if (m_logLevel == Level::RELEASE) {
				time_t t = time(nullptr); // время
				tm ptm = *localtime(&t); // время
				std::cerr << "\x1b[38;5;244m" << "[RELEASE][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
				m_out << "{R}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl;
			}
		}
	}

	static void AutoLog(int logLevel, const char *_Format, const char *err) { // ERROR
		if (flag[ERROR] == true) { // галочка на ERROR стоит
			Log::SetLogLevel(static_cast<Log::Level>(logLevel)); // открываем уровень
			if (m_logLevel == Level::ERROR) {
				time_t t = time(nullptr); // время
				tm ptm = *localtime(&t); // время
				std::cerr << "\x1b[31m" << "[ERROR#" << _Format << "][" << std::put_time(&ptm, "%T") << "]" << err << "\x1b[0m" << std::endl;
				m_out << "[[ERROR#" << _Format << "][" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << err << std::endl;
			}
		}
	}

	static void End(int logLevel, const std::string& msg) // программа завершилась успешно
	{
		if (flag[RELEASE] == true || flag[DEBUG] == true) {
			Log::SetLogLevel(static_cast<Log::Level>(logLevel)); // открываем уровень
			if (m_logLevel == Level::END) {
				time_t t = time(nullptr); // время
				tm ptm = *localtime(&t); // время
				std::cerr << "\x1b[38;5;244m" << "[END][" << std::put_time(&ptm, "%T") << "]" << msg << "\x1b[0m" << std::endl;
				m_out << "{0}[" << std::put_time(&ptm, "%d:%m:%Y %H:%M:%S") << "]" << msg << std::endl << std::endl << std::endl;
			}
		}
	}
};