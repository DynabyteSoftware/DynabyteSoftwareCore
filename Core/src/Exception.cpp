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

Exception::Exception(const string& sFunctionName, const string& sSourceFilename, unsigned int unSourceLineNumber,
										 const string& sMessage)
{
	m_sMessage = sMessage;
	m_sFunctionName = sFunctionName;
	m_sSourceFilename = sSourceFilename;
	m_unSourceLineNumber = unSourceLineNumber;

	createStringValue();
	clog << Log::Error << what() << endl;
}

Exception::~Exception()
{
}

const string& Exception::getMessage() const
{
	return m_sMessage;
}

const string& Exception::getFunctionName() const
{
	return m_sFunctionName;
}

const string& Exception::getSourceFilename() const
{
	return m_sSourceFilename;
}

const string& Exception::toString() const
{
	return m_sStringValue;
}

void Exception::createStringValue()
{
	stringstream ssException;
	ssException << "Exception:  " << m_sMessage << " (" << m_sFunctionName << "(), " << m_sSourceFilename
		    << ", Line " << m_unSourceLineNumber << ")";

	m_sStringValue = ssException.str();
}

const char* Exception::what() const noexcept
{
	return m_sStringValue.c_str();
}

unsigned int Exception::getSourceLineNumber() const
{
	return m_unSourceLineNumber;
}
