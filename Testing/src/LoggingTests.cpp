#include <iostream>
#include "LoggingTests.h"
#include "Log.h"

using namespace DynabyteSoftware::Testing;
using std::clog;
using std::endl;

void LoggingTests::logStuff()
{
	clog << Log::Information << "This is test for information" << endl;
	clog << Log::Warning << "This is a test for a warning" << endl;
	clog << Log::Error << "This is a test for an error" << endl;
}

void LoggingTests::testWithCommonLogFile()
{
	Log::getLogger().assignLogFile("CommonLogTest.txt");
	logStuff();
	Log::endLogger();
}

void LoggingTests::testWithNoLogFiles()
{
	Log::getLogger();
	logStuff();
	Log::endLogger();
}

void LoggingTests::testWithSeparateLogFiles()
{
	Log& oLogger = Log::getLogger();
	oLogger.assignLogFile(Log::Information, "InformationLog.txt");
	oLogger.assignLogFile(Log::Warning, "WarningLog.txt");
	oLogger.assignLogFile(Log::Error, "ErrorLog.txt");
	logStuff();
	Log::endLogger();
}

void LoggingTests::allTests()
{
	testWithNoLogFiles();
	testWithSeparateLogFiles();
	testWithCommonLogFile();
}