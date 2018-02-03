#include <iostream>
#include <sstream>
#include "DateTime.h"
#include "Exception.h"
#include "Log.h"

using namespace DynabyteSoftware;
using std::clog;
using std::endl;
using std::string;
using std::stringstream;
using std::exception;

static const char* const EXCEPTION_NAME = "Exception";

Exception::Exception(const string& functionName, const string& sourceFilename, unsigned int sourceLineNumber,
										 const string& message)
         : _exceptionName(EXCEPTION_NAME), _message(message), _functionName(functionName),
           _sourceFilename(sourceFilename), _sourceLineNumber(sourceLineNumber)
{
	createStringValue();
	clog << Log::Error << "[" << DateTime::now(DateTimeKind::UTC) << "] " << what() << endl;
}

Exception::~Exception()
{
}

const string& Exception::getMessage() const
{
	return _message;
}

const string& Exception::getFunctionName() const
{
	return _functionName;
}

const string& Exception::getSourceFilename() const
{
	return _sourceFilename;
}

const string& Exception::toString() const
{
	return _stringValue;
}

void Exception::createStringValue() const
{
	stringstream exceptionString;
	exceptionString << _exceptionName << ":  " << _message << " (" << _functionName << "(), " << _sourceFilename
	          	    << ", Line " << _sourceLineNumber << ")";

	_stringValue = exceptionString.str();
}

const char* Exception::what() const noexcept
{
	return _stringValue.c_str();
}

unsigned int Exception::getSourceLineNumber() const
{
	return _sourceLineNumber;
}