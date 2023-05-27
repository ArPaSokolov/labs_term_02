#include <iostream> 
#include "log.h"
#include <sqlite3/sqlite3.h>
#include <stdio.h>

using namespace std;


static int callback(void* data, int argc, char** argv, char** azColName) {
	int i;

	fprintf(stderr, "%s: ", (const char*)data,"\n");

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	return 0;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");

	Log::SetLogPath("../log.txt"); // указываем путь до файла с логами

	Log::LevelFlag(); // метод для установки "галочек"
	Log::AutoLog(0, "Program is running");
	Log::AutoLog(1, "Program is running");

	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	string sql;
	const char* data = "Callback function called";

	/* Open database */
	rc = sqlite3_open("test.db", &db);

	if (rc) {
		Log::AutoLog(Log::ERROR, "Can't open database: ", sqlite3_errmsg(db));
		return(0);
	}
	else {
		Log::AutoLog(Log::INFO, "Opened database successfully");
	}

	/* Create SQL statement */
	sql = "SELECT * from TEST";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);

	if (rc != SQLITE_OK) {
		Log::AutoLog(Log::ERROR, "SQL error: ", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		Log::AutoLog(Log::INFO, "Callback function called successfully");
	}
	sqlite3_close(db);
	
	
	
	
	

	/*
	Log::AutoLog(Log::INFO, "Hello World");

	Log::AutoLog(Log::ERROR, "Invalid data type", "001");*/

	Log::End(4, "Program finished successfully");
	return 0;
}