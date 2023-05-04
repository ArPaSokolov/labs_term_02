#include <iostream> 
#include "log.h"
#include <vector>

using namespace std;

int main()
{
	Log::SetLogPath("../log.txt"); // указываем путь до файла с логами

	Log::LevelFlag(); // метод для установки "галочек"

	Log::AutoLog(0, "Program is running");

	Log::AutoLog(1, "Program is running");

	Log::AutoLog(2, "Hello World");
	Log::AutoLog(2, "Booyakasha");

	Log::AutoLog(3, "Invalid data type", "001");
	Log::AutoLog(3, "Out of range", "002");
	Log::AutoLog(3, "Slishkom mnogo bukav", "001");

	Log::End(4, "Program finished successfully");
	return 0;
}