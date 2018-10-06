#include "DateTime.h"
#include "Log.h"
#include<iostream>

using namespace std;
using namespace DynabyteSoftware;

static constexpr const char* const TIME_OPEN_BRACKET = "(";
static constexpr const char* const TIME_CLOSE_BRACKET = ")]";

Log* Log::m_pLogger = nullptr;

Log::Log()
{  
  clog.rdbuf(this);
}

Log::~Log()
{
  clog.rdbuf(cerr.rdbuf());
  closeAllExistingStreams();
}

Log& Log::getLogger()
{
  if(!m_pLogger)
    m_pLogger = new Log();
  
  return *m_pLogger;
}

void Log::endLogger()
{
  if(m_pLogger)
  {
    delete m_pLogger;
    m_pLogger = nullptr;
  }
}

bool Log::assignLogFile(const std::string& sFilename)
{
  closeAllExistingStreams();

  return assignLogFile(Information, sFilename) && assignLogFile(Warning, sFilename) && assignLogFile(Error, sFilename);
}

bool Log::assignLogFile(enum LogType eLogType, const std::string& sFilename)
{
  auto oFileStream = m_oFileStreams.find(sFilename);
  if (oFileStream == m_oFileStreams.end())
  {
    ofstream *pStream = new ofstream(sFilename.c_str());
    if (!pStream)
      return false;

    m_oFileStreams[sFilename] = pStream;
  }

  m_oOutputStreamsMap[eLogType] = sFilename;
  
  return true;
}

int Log::sync()
{
  ostream *pStream;
  auto oFilenameMap = m_oOutputStreamsMap.find(m_eCurrentLogType);
  
  if(oFilenameMap == m_oOutputStreamsMap.end())
  {
    pStream = &cerr;
  }
  else
  {
    pStream = m_oFileStreams[oFilenameMap->second];
  }
  
  switch(m_eCurrentLogType)
  {    
    case Information:
      *pStream << "[Information ";
      break;
    case Warning:
      *pStream << "[Warning ";
      break;
    case Error:
      *pStream << "[Error ";
      break;
  }
  
  *pStream << TIME_OPEN_BRACKET << DateTime::now(DateTimeKind::UTC) << TIME_CLOSE_BRACKET << ' ' << m_sBuffer << flush;
  m_sBuffer.erase();
  
  return 0;
}

int Log::overflow(int nCharacter)
{
  if(nCharacter == EOF)
  {
    sync();
  }
  else
  {
    m_sBuffer += (char)nCharacter;
  }
  
  return nCharacter;
}

void Log::closeAllExistingStreams()
{
  for (auto& oFileStream : m_oFileStreams)
  {
    if (oFileStream.second->is_open())
      oFileStream.second->close();

    delete oFileStream.second;
  }

  m_oFileStreams.clear();
  m_oOutputStreamsMap.clear();
}

namespace DynabyteSoftware
{
  std::ostream& operator<<(std::ostream& oOutputStream, enum Log::LogType eLogType)
  {
    if(Log *pLog = dynamic_cast<Log*>(oOutputStream.rdbuf()))
    {
      pLog->m_eCurrentLogType = eLogType;
    }
  
    return oOutputStream;
  }
}