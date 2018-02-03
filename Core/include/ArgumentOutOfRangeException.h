#pragma once
#include "Exception.h"

namespace DynabyteSoftware
{
  class ArgumentOutOfRangeException : public virtual Exception//, public virtual std::out_of_range
  {
  public:
    /**
    * Constructor for an ArgumentOutOfRangeException object
    * 
    * @param functionName[in] The function name where the exception was thrown
    * @param sourceFilename[in] The filename where the exception was thrown
    * @param sourceLineNumber[in] The line number where the exception was thrown
    * @param paramName[in] The name of the parameter whose value was out of range
    * @param message[in] The message associated with this exception
    **/
    CORE_EXPORT
    ArgumentOutOfRangeException(const std::string& functionName, const std::string& sourceFilename,
                                unsigned int sourceLineNumber, const std::string& paramName = "",
                                const std::string& message = "argument was out of range");
  };
}