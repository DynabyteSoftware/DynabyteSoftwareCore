#include <iostream>
#include <sstream>
#include "Exception.h"
#include "Log.h"

using namespace DynabyteSoftware;
using std::clog;
using std::endl;
using std::string;
using std::stringstream;

Exception::Exception(string const sFunctionName, string const sSourceFilename, unsigned int unSourceLineNumber,
										 string const sMessage, Exception* const pInnerException)
{
	m_sMessage = sMessage;
	m_sFunctionName = sFunctionName;
	m_sSourceFilename = sSourceFilename;
	m_unSourceLineNumber = unSourceLineNumber;
	m_pInnerException = pInnerException;

	createStringValue();
	clog << Log::Error << what() << endl;
}

Exception::~Exception()
{
  /*
	if(m_pInnerException)
 	{
 		delete m_pInnerException;
	}
	*/
}

string const& Exception::getMessage() const
{
	return m_sMessage;
}

string const& Exception::getFunctionName() const
{
	return m_sFunctionName;
}

string const& Exception::getSourceFilename() const
{
	return m_sSourceFilename;
}

string const Exception::toString() const
{
	return m_sStringValue;
}

void Exception::createStringValue()
{
	stringstream ssException;
	ssException << "Exception:  " << m_sMessage << " (" << m_sFunctionName << "(), " << m_sSourceFilename
		    << ", Line " << m_unSourceLineNumber << ")";

	if(m_pInnerException)
	{
 		ssException << endl << '\t' << m_pInnerException->toString();
	}

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

Exception* const Exception::getInnerException() const
{
	return m_pInnerException;
}
