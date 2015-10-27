#include "Log.h"
#include "LoggingTests.h"
#include "ExceptionTests.h"

using namespace DynabyteSoftware::Testing;
using DynabyteSoftware::Log;

int main(int argc, char* argv[])
{
	LoggingTests::allTests();

	Log::getLogger().assignLogFile("ExceptionLogs.txt");
	ExceptionTests::allTests();
	Log::endLogger();

	return 0;
}