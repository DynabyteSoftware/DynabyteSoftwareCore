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

static constexpr const char* const EXCEPTION_NAME = "Exception";
static constexpr const char* const TIME_OPEN_BRACKET = "[";
static constexpr const char* const TIME_CLOSE_BRACKET = "]";
static constexpr const char* const EXCEPTION_TYPE_DELIMITER = ": ";
static constexpr const char* const DETAIL_OPEN_BRACKET = "(";
static constexpr const char* const DETAIL_CLOSE_BRACKET = ")";
static constexpr const char* const FUNCTION_DECORATION = "()";
static constexpr const char* const DETAIL_DELIMITER = ", ";
static constexpr const char* const LINE_LABEL = "Line ";

Exception::Exception(const string& functionName, const string& sourceFilename, unsigned int sourceLineNumber,
										 const string& message)
         : Exception(EXCEPTION_NAME, functionName, sourceFilename, sourceLineNumber, message)
{
}

Exception::Exception(const string& exceptionName, const string& functionName, const string& sourceFilename,
                     unsigned int sourceLineNumber, const string& message)
         : _exceptionName(exceptionName), _message(message), _functionName(functionName),
           _sourceFilename(sourceFilename), _sourceLineNumber(sourceLineNumber)
{
  createStringValue();
  clog << endl;
  clog << Log::Error << TIME_OPEN_BRACKET << DateTime::now(DateTimeKind::UTC) << TIME_CLOSE_BRACKET << " " << what()
       << endl;
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
	exceptionString << _exceptionName << EXCEPTION_TYPE_DELIMITER
                  << _message << " " << DETAIL_OPEN_BRACKET
                  << _functionName << FUNCTION_DECORATION << DETAIL_DELIMITER
                  << _sourceFilename << DETAIL_DELIMITER
	          	    << LINE_LABEL << _sourceLineNumber << DETAIL_CLOSE_BRACKET;

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