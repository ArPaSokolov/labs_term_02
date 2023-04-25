#include <iostream>
#include "log.h"
#include <vector>

using namespace std;

int main()
{
	Log::SetLogPath("../log.txt");

	bool Dflag, Rflag, Iflag, Eflag;
	cout <<	"DEBUG, RELEASE, INFO, ERROR: ";
	cin >> Dflag;
	cin >> Rflag;
	cin >> Iflag;
	cin >> Eflag;

	if (Dflag == true) {
		Log::SetLogLevel(static_cast<Log::Level>(0));
		Log::Debug("Program is running");
	}
	if (Rflag == true) {
		Log::SetLogLevel(static_cast<Log::Level>(1));
		Log::Release("Program is running");
	}
	if (Iflag == true) {
		Log::SetLogLevel(static_cast<Log::Level>(2));
		Log::Info("Hello World");
		Log::Info("Booyakasha");
	}
	if (Eflag == true) {
		Log::SetLogLevel(static_cast<Log::Level>(3));
		Log::Error("001","Invalid data type");
		Log::Error("002","Out of range");
		Log::Error("003","Smth in the way");
	}

	Log::End("Program finished successfully");
	return 0;
}