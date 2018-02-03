#include "ArgumentOutOfRangeException.h"

using namespace DynabyteSoftware;
using namespace std;

static constexpr const char* const EXCEPTION_NAME = "ArgumentOutOfRangeException";

ArgumentOutOfRangeException::ArgumentOutOfRangeException(const string& functionName, const string& sourceFilename,
                                                         unsigned int sourceLineNumber, const string& paramName,
                                                         const string& message)
                           : //exception((message + " (" + paramName + ")").c_str()),
                             Exception(EXCEPTION_NAME, functionName, sourceFilename, sourceLineNumber, message + " (" + paramName + ")")//,
                             //out_of_range(getMessage())
{

}