#include <iostream> 
#include <sqlite3/sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cstring>

#include "log.h"

using namespace std;

class SQLite
{
private:
	string dbname;
	string tablename = "traffic";
	sqlite3* db;

static int callback(void* data, int argc, char** argv, char** azColName) {

	int i;

	fprintf(stderr, (const char*)data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	return 0;
}
public:
	SQLite(const string& dbName) {
        dbname = dbName;
	}

	~SQLite()
	{
        /*независимо от того, происходит ли ошибка при открытии, ресурсы связанные 
        с соединением к базе данных должны быть освобождены, передав их
        в sqlite3_close (), когда они больше не требуется.*/
		sqlite3_close(db); 

	}

    void Open() // открываем базу
    {
        try
        {
            int rc = sqlite3_open(dbname.c_str(), &db);
			Log::AutoLog(Log::INFO, "Opened" + tablename + "successfully");
        }
        catch (...)
        {
			Log::AutoLog(Log::ERROR, "SQL", sqlite3_errmsg(db));
        }
    }
	
	string Insert() {
		try
		{
			Log::AutoLog(Log::INFO, "Inserting data...");
			string insert;
			cout << "Введите somedata: ";
			cin >> insert;
			string sql = "INSERT INTO " + dbname + " (somedata) "  \
				"VALUES ( ('" + insert + "') ); ";
			Log::AutoLog(Log::INFO, "Insert data finished");
			return sql;
		}
		catch (...) {
			Log::AutoLog(Log::ERROR, "SQL", sqlite3_errmsg(db));
		}
	}

	string AddColumn() { // добавляем колонку
		try
		{
			Log::AutoLog(Log::INFO, "Inserting data...");
			time_t now = time(nullptr);

			time_t rawtime;
			struct tm* timeinfo;
			char buffer[15];

			time(&rawtime);
			timeinfo = localtime(&rawtime);

			strftime(buffer, sizeof(buffer), "'%Y.%m.%d'", timeinfo);
			string str(buffer);

			string sql = "ALTER TABLE " + tablename + " ADD COLUMN " + str + " TEXT";

			Log::AutoLog(Log::INFO, "Insert data finished");
			return sql;
		}
		catch (...) {
			Log::AutoLog(Log::ERROR, "SQL", sqlite3_errmsg(db));
		}
	}

	string Select() {
		try
		{
			Log::AutoLog(Log::INFO, "Selecting data...");
			string select;
			cout << "Введите фильтр: ";
			cin >> select;
			string sql = "SELECT " + select + "  from " + tablename + "";
			Log::AutoLog(Log::INFO, "Selecting data finished");
			return sql;
		}
		catch (...) {
			Log::AutoLog(Log::ERROR, "SQL", sqlite3_errmsg(db));
		}
	}

	string Query() {
		try
		{
			string sql = "SELECT * FROM " + tablename + " WHERE somedata LIKE '%Browser%'"; // запрос к базе данных
			return sql;
		}
		catch (...) {
			Log::AutoLog(Log::ERROR, "SQL", sqlite3_errmsg(db));
		}
	}

    void Exec(const string& sql) // запрос = обращение к базе данных
    {
        char* zErrMsg = 0;
		Log::AutoLog(Log::INFO, "Callback function called");
        int rc = sqlite3_exec(db, sql.c_str(), callback, "", &zErrMsg);

        if (rc != SQLITE_OK) {
			Log::AutoLog(Log::ERROR, "SQL", zErrMsg);
			sqlite3_free(zErrMsg);
        }
        else {
            Log::AutoLog(Log::INFO, "Operation done successfully");
        }
    }
};

int main()
{
	setlocale(LC_ALL, "ru");

	Log::SetLogPath("../log.txt"); // указываем путь до файла с логами

	Log::LevelFlag(); // метод для установки "галочек"
	Log::AutoLog(Log::DEBUG, "Program is running");
	Log::AutoLog(Log::RELEASE, "Program is running");


    SQLite s("database.db");

    s.Open();
    s.Exec(s.Select());
	//s.Exec(s.AddColumn());
	

	Log::End(Log::END, "Program finished successfully");
	return 0;
}

