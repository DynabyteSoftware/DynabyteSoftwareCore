/*******************************************************************************************************************//**
* @file ArgumentOutOfRangeException.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/02/03
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's ArgumentOutOfRange exception
**********************************************************************************************************************/

#pragma once
#include "Exception.h"

namespace DynabyteSoftware
{
  /****************************************************************************************************************//**
  * @class ArgumentOutOfRangeException
  * @ingroup DynabyteSoftware
  * @brief Exception thrown when an argument has a value outside expected range
  * @details
  * Exception thrown when an argument has a value outisde expected range.
  ********************************************************************************************************************/
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

    /**
     * @return name of parameter whose value was out of range
     **/
    CORE_EXPORT
    const std::string& getParameterName() const;
  private:
    const std::string _paramName;
  };
}
