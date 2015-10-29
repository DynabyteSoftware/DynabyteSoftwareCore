/***********************************************************************************************************************
 * @file Exception.h
 * @author Rod Leonard
 * @version 0.0.1
 * @date 2015/10/27
 * @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
 * @brief Header file for DynabyteSoftware's Exception object
 **********************************************************************************************************************/

#pragma once
#pragma warning(disable: 4251) //microsoft is dumb, because stl components are a standard part of c++
#pragma warning(disable: 4275) //microsoft is dumb, because exception is a standard part of c++

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
	class CORE_EXPORT Exception : public std::exception
	{
	public:
		/**
		 * Constructor for an Exception object
		 * 
		 * @param sFunctionName[in] The function name where the exception was thrown
		 * @param sSourceFilename[in] The filename where the exception was thrown
		 * @param unSourceLineNumber[in] The line number where the exception was thrown
		 * @param sMessage[in] The message associated with this exception
		 * @param pInnerException[in] Optionally, the caught exception that caused this exception to be thrown
		 **/
		Exception(std::string const sFunctionName, std::string const sSourceFilename, unsigned int unSourceLineNumber,
							std::string const sMessage, std::exception* const pInnerException = nullptr);
		/**
		 * Virtual destructor for an Exception object
		 **/
		virtual ~Exception() throw();

		/**
		 * @return The exception message
		 **/
		std::string const& getMessage() const;
		/**
		 * @return The function name where the exception was thrown
		 **/
		std::string const& getFunctionName() const;
		/**
		 * @return The source filename where the exception was thrown
		 **/
		std::string const& getSourceFilename() const;
		/**
		 * @return A string representation of this Exception
		 **/
		std::string const toString() const;
		/**
		 * @return The line number in the source file where th exception was thrown
		 **/
		unsigned int getSourceLineNumber() const;
		/**
		 * @return The inner exception that caused this exception to be thrown
		 * @note Could return a nullptr if no inner exception
		 **/
		std::exception* const getInnerException() const;

		/**
		 * @return A description of this Exception
		 **/
		virtual const char* what() const noexcept;
	private:
		unsigned int m_unSourceLineNumber;
		std::string m_sStringValue;
		std::string m_sMessage;
		std::string m_sFunctionName;
		std::string m_sSourceFilename;
		std::exception *m_pInnerException;

		void createStringValue();
	};
}

