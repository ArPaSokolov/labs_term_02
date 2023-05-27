#include <iostream> 
#include "log.h"
#include <sqlite3/sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class SQLite
{
private:
	string dbname;
	/*string tablename;*/
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

    void Open()
    {
        try
        {
            int rc = sqlite3_open(dbname.c_str(), &db);
			Log::AutoLog(Log::INFO, "Opened database successfully");
        }
        catch (...)
        {
			Log::AutoLog(Log::ERROR, "SQL", sqlite3_errmsg(db));
        }
    }
	
	string Insert() {
		try
		{
			Log::AutoLog(Log::INFO, "Inserting data");
			string somedata;
			cout << "Введите somedata: ";
			cin >> somedata;
			string insert = "INSERT INTO TEST (somedata) "  \
				"VALUES ( ('" + somedata + "') ); ";
			Log::AutoLog(Log::INFO, "Insert data finished");
			return insert;
		}
		catch (...) {
			Log::AutoLog(Log::ERROR, "SQL", sqlite3_errmsg(db));
		}
	}

    void Exec(const string& sql)
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

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");

	Log::SetLogPath("../log.txt"); // указываем путь до файла с логами

	Log::LevelFlag(); // метод для установки "галочек"
	Log::AutoLog(Log::DEBUG, "Program is running");
	Log::AutoLog(Log::RELEASE, "Program is running");

	
    SQLite s("test.db");

    s.Open();
    s.Exec("SELECT * from TEST");
	s.Exec(s.Insert()); 
	s.Exec("SELECT * from TEST");


	Log::End(Log::END, "Program finished successfully");
	return 0;
}