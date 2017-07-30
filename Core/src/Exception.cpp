#include <iostream>
#include <sstream>
#include "Exception.h"
#include "Log.h"

using namespace DynabyteSoftware;
using std::clog;
using std::endl;
using std::string;
using std::stringstream;
using std::exception;

Exception::Exception(const string& functionName, const string& sourceFilename, unsigned int sourceLineNumber,
										 const string& message)
         : message(message), functionName(functionName), sourceFilename(sourceFilename),
           sourceLineNumber(sourceLineNumber)
{
	createStringValue();
	clog << Log::Error << what() << endl;
}

Exception::~Exception()
{
}

const string& Exception::getMessage() const
{
	return message;
}

const string& Exception::getFunctionName() const
{
	return functionName;
}

const string& Exception::getSourceFilename() const
{
	return sourceFilename;
}

const string& Exception::toString() const
{
	return stringValue;
}

void Exception::createStringValue() const
{
	stringstream exceptionString;
	exceptionString << "Exception:  " << message << " (" << functionName << "(), " << sourceFilename
	          	    << ", Line " << sourceLineNumber << ")";

	stringValue = exceptionString.str();
}

const char* Exception::what() const noexcept
{
	return stringValue.c_str();
}

unsigned int Exception::getSourceLineNumber() const
{
	return sourceLineNumber;
}
