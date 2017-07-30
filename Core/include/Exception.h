/***********************************************************************************************************************
 * @file Exception.h
 * @author Rod Leonard
 * @version 0.0.2
 * @date 2015/10/27
 * @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
 * @brief Header file for DynabyteSoftware's Exception object
 **********************************************************************************************************************/

#pragma once

#include <string>
#include <exception>
#include "CoreExports.h"

/**
 * @def THROW(ExceptionName, ...)
 * @brief Macro intended to be used with any exceptions that inherit from DynabyteSoftware-derived exceptions
 * @see DynabyteSoftware::Exception
 * @details
 * This macro throws a DynabyteSoftware exception while automatically populating information about the location the
 * exception is being thrown.
 * @code{.cpp}
 * try
 * {
 * 		THROW(Exception, "This is the first exception thrown")
 * }
 * catch(Exception& excp)
 * {
 * 		THROW(Exception, "This is the second exception thrown, as a result of first exception", &excp)
 * }
 * @endcode
 */
#define THROW(ExceptionName, ...) throw ExceptionName(__func__, __FILE__, __LINE__, __VA_ARGS__);

namespace DynabyteSoftware
{
	/*********************************************************************************************************************
	 * @class Exception
	 * @ingroup DynabyteSoftware
	 * @brief Exception base class that keeps additional information and self-logs
	 * @see THROW
	 * @see Log
	 * @see std::clog
	 * 
	 * @details
	 * This Exception class is meant to provide additional information that std::exception does not (it does inherit from
	 * std::exception, so it can be handled normally)
	 * 
	 * The additional information it contains is the function name, source filename, line number, and potentially
	 * inner exceptions in the case of cascaded exception-handling.  If thrown using the intended THROW macro, this
	 * information is populated automatically
	 * 
	 * In addition, this class also automatically self-logs whenever it is thrown, using std::clog.  If Log has been
	 * initialized with a Log::Error logfile, clog will output to the selected file stream.
	 * 
	 * @note
	 * When inheriting from this class, ensure the constructor parameters start by taking the function name, 
	 * the source filename, and the line number--in this order.  Additional parameters may be added as desired, after
	 * the required parameters.  This setup ensures your exceptions will be able to use the THROW macro to automatically
	 * populate that information
	 ********************************************************************************************************************/
	class Exception : public std::exception
	{
	public:
		/**
		 * Constructor for an Exception object
		 * 
		 * @param functionName[in] The function name where the exception was thrown
		 * @param sourceFilename[in] The filename where the exception was thrown
		 * @param sourceLineNumber[in] The line number where the exception was thrown
		 * @param message[in] The message associated with this exception
		 **/
    CORE_EXPORT
		Exception(const std::string& functionName, const std::string& sourceFilename, unsigned int sourceLineNumber,
							const std::string& message);
		/**
		 * Virtual destructor for an Exception object
		 **/
    CORE_EXPORT
		virtual ~Exception() throw();

		/**
		 * @return The exception message
		 **/
    CORE_EXPORT
		const std::string& getMessage() const;
		/**
		 * @return The function name where the exception was thrown
		 **/
    CORE_EXPORT
		const std::string& getFunctionName() const;
		/**
		 * @return The source filename where the exception was thrown
		 **/
    CORE_EXPORT
		const std::string& getSourceFilename() const;
		/**
		 * @return A string representation of this Exception
		 **/
    CORE_EXPORT
		const std::string& toString() const;
		/**
		 * @return The line number in the source file where th exception was thrown
		 **/
    CORE_EXPORT
		unsigned int getSourceLineNumber() const;

    /****** exception ******/
		/**
		 * @return A description of this Exception
		 **/
    CORE_EXPORT
		virtual const char* what() const noexcept override;
	private:
    void createStringValue() const;
  private:
		const unsigned int sourceLineNumber;
		const std::string message;
		const std::string functionName;
		const std::string sourceFilename;

    mutable std::string stringValue;
	};
}

