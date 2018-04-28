/******************************************************************************************************************//**
 * @file Log.h
 * @author Rod Leonard
 * @version 0.0.2
 * @date 2015/10/27
 * @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
 * @brief Header file for DynabyteSoftware's Log framework
 *********************************************************************************************************************/

#pragma once

#include <fstream>
#include <map>
#include <string>
#include "CoreExports.h"

namespace DynabyteSoftware
{
	/*****************************************************************************************************************//**
	 * @class Log
	 * @ingroup DynabyteSoftware
	 * @brief DynabyteSoftware's logging framework
	 * @see std::clog
	 * 
	 * @details
	 * This class provides the functionality for a simple logging system.  Once initialized, it will replaced the stream
	 * buffer for std::clog, and therefore using it as simple as invoking clog.
	 * 
	 * In addition, this class also automatically self-logs whenever it is thrown, using std::clog.  If Log has been
	 * initialized with a Log::Error logfile, clog will output to the selected file stream.
	 * 
	 * Three log types are supported.  Information logs, warning logs, and error logs.  Different log files may be
	 * assigned for each log type, or a common log files for multiple types.  Any log type not assigned a log file will
	 * simply log to clog's default stream buffer.
	 * 
	 * @code{.cpp}
	 * Log::getLogger().assignLogFile("common.log"); //assigns a common log file for all levels
	 * clog << Log::Information << "This is an information-type log" << endl;
	 * clog << Log::Warning << "This in a warning-type log" << endl;
	 * clog << Log::Error << "This is an error-type log" << endl;
	 * Log::endlogger(); //Stops logging and reverts clog's stream buffer to its default buffer
	 * @endcode
	 * 
	 * Alternatively, log files can be assigned to specific log types
	 * 
	 * @code{.cpp}
	 * Log::getLogger().assignLogFile(Log::Error, "Error.log") //assigns a log file for error-type logs
	 * clog << Log::Information << "This is an information-type log" << endl;
	 * clog << Log::Warning << "This in a warning-type log" << endl;
	 * clog << Log::Error << "This is an error-type log" << endl; //this is the only log that gets written to above file
	 * Log::endlogger(); //Stops logging and reverts clog's stream buffer to its default buffer
	 * 
	 * @note
	 * Not thread-safe
	 ********************************************************************************************************************/
  class Log final : public std::streambuf
  {
  public:
		/**
		 * @enum LogType
		 * @brief Enumeration for different log levels
		 **/
		enum LogType
		{
			Information,
			Warning,
			Error
		};
	
  public:
		/**
		 * Destructor for the Log buffer
		 **/
    CORE_EXPORT
		~Log();
  public:
		/**
		 * @return Reference to the log buffer associated with clog.  This is a *reference*, so don't copy it.
		 **/
    CORE_EXPORT
		static Log& getLogger();
		/**
		 * Stops logging and reverts clog to its default buffer
		 * 
		 * @note 
		 * Not to be used to pause logging. After endLogger() has been called, if a log file is assigned with the same
		 * filename as a previous log file, data will not be appended to it, the file will be overriden.  This is done so as
		 * to not grow the log file unnecessarily. If the developer intends to keep log files indefinitely, they should
		 * include date and time in the filename.
		 **/
    CORE_EXPORT
		static void endLogger();
	
		/**
		 * Assigns a common log file to all log levels
		 * @param sFilename[in] The filename of the log file
		 * @return true if file was successfully opened and associated, false otherwise
		 **/
    CORE_EXPORT
		bool assignLogFile(const std::string& sFilename);
		/**
		 * Assigns a log file to the specified log levels
		 * @param eLogType[in] The log type to asociate with the log file
		 * @param sFilename[in] The filename of the log file
		 * @return true if file was successfully opened and associated, false otherwise
		 **/
    CORE_EXPORT
		bool assignLogFile(enum LogType eLogType, const std::string& sFilename);
  private:
		static Log *m_pLogger;
	
		enum LogType m_eCurrentLogType;
		std::map<enum LogType, std::string> m_oOutputStreamsMap;
		std::map<std::string, std::ofstream*> m_oFileStreams;
		std::string m_sBuffer;
  private:
		Log();
  private:
		int sync() override;
		int overflow(int nCharacter = EOF) override;
		void closeAllExistingStreams();
	
    /**
    * Overrides the stream operator to allow for assignment of log type to a Log stream buffer
    * @see Log
    * @see Log::LogType
    *
    * @param OutputSream[in,out] The output stream we're writing a log type to.
    * @param eLogType[in] The log type to assign to the output stream
    * @return Reference to the output stream, modified to expect the specified log type
    *
    * @note If the OutputStream is not of type Log, eLogType will be ignored
    **/
		CORE_EXPORT friend std::ostream& operator<<(std::ostream& oOutputStream, enum LogType eLogType);                               
  };
}
