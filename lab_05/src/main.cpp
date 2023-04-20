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
		Log::Debug();
	}
	if (Rflag == true) {
		Log::SetLogLevel(static_cast<Log::Level>(1));
		Log::Release();
	}
	if (Iflag == true) {
		Log::SetLogLevel(static_cast<Log::Level>(2));
		Log::Info();
	}
	if (Eflag == true) {
		Log::SetLogLevel(static_cast<Log::Level>(3));
		Log::Error();
	}

	Log::End();
	return 0;
}