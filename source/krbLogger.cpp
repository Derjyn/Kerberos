///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbLogger.cpp
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "krbLogger.h"
#include "krbTimer.h"

#include <iomanip>

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

Logger::Logger(Timer *timer) : strLogFile("") {
  pTimer = timer;
}

///////////////////////////////////////////////////////////////////////////////
// CREATE LOG

void Logger::CreateLog(std::string file, std::string title, int level) {

  strLogFile = file;
  iLogLevel = level;

  iCntDebug = 0;
  iCntError = 0;
  iCntWarning = 0;
  iCntInfo = 0;

  mLog.open(strLogFile);

  if (mLog.is_open()) {
    time_t rawtime;
    struct tm timeinfo;
    char buffer[80];
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);

    strftime(buffer, 80, "%m-%d-%y %I:%M:%S", &timeinfo);
    mLog << std::setfill('/') << std::setw(79) << '/' << std::endl;
    mLog << "//" << std::endl;
    mLog << "// " << title.c_str() << std::endl;
    mLog << "// Log created: " << buffer << std::endl;
    mLog << "//" << std::endl;
    mLog << std::setfill('/') << std::setw(79) << '/' << std::endl;
    mLog << std::endl;

    mLog.close();
  }
}

///////////////////////////////////////////////////////////////////////////////
// LOG MESSAGE

void Logger::LogMessage(const MsgLevel logType, const MsgType msgType, std::string message) {

  switch (logType) {
  case LOG_ERROR:
    mLog.open(strLogFile, std::ios::out | std::ios::app);
    mLog << "[ERROR] ";
    switch (msgType)
    {
    case MsgType::MSG_CORE:
      mLog << "[CORE] " << std::setfill(' ') << std::setw(12);
      break;
    case MsgType::MSG_GAME:
      mLog << "[GAME] " << std::setfill(' ') << std::setw(12);
      break;
    case MsgType::MSG_LAB:
      mLog << "[LAB] " << std::setfill(' ') << std::setw(13);
      break;
    case MsgType::MSG_MODULE:
      mLog << "[MODULE] " << std::setfill(' ') << std::setw(13);
      break;
    case MsgType::MSG_STAT:
      mLog << "[STAT] " << std::setfill(' ') << std::setw(12);
      break;
    case MsgType::MSG_SYSTEM:
      mLog << "[SYSTEM] " << std::setfill(' ') << std::setw(10);
      break;
    }
    switch (iLogLevel)
    {
    case(1) :
      mLog << "\t" << pTimer->getMilliseconds() << "ms\t: " << message.c_str() << std::endl;
      break;
    case(0) :
      mLog << message.c_str() << std::endl;
      break;
    }
    ++iCntError;
    mLog.close();
    break;

  case LOG_WARNING:
    mLog.open(strLogFile, std::ios::out | std::ios::app);
    mLog << "[WARNING] ";
    switch (msgType)
    {
    case MsgType::MSG_CORE:
      mLog << "[CORE] " << std::setfill(' ') << std::setw(12);
      break;
    case MsgType::MSG_GAME:
      mLog << "[GAME] " << std::setfill(' ') << std::setw(12);
      break;
    case MsgType::MSG_LAB:
      mLog << "[LAB] " << std::setfill(' ') << std::setw(13);
      break;
    case MsgType::MSG_MODULE:
      mLog << "[MODULE] " << std::setfill(' ') << std::setw(13);
      break;
    case MsgType::MSG_STAT:
      mLog << "[STAT] " << std::setfill(' ') << std::setw(12);
      break;
    case MsgType::MSG_SYSTEM:
      mLog << "[SYSTEM] " << std::setfill(' ') << std::setw(10);
      break;
    }
    switch (iLogLevel)
    {
    case(1) :
      mLog << "\t" << pTimer->getMilliseconds() << "ms\t: " << message.c_str() << std::endl;
      break;
    case(0) :
      mLog << message.c_str() << std::endl;
      break;
    }
    ++iCntWarning;
    mLog.close();
    break;

  case LOG_INFO:
    mLog.open(strLogFile, std::ios::out | std::ios::app);
    mLog << "[INFO] ";
    switch (msgType)
    {
    case MsgType::MSG_CORE:
      mLog << "[CORE] " << std::setfill(' ') << std::setw(12);
      break;
    case MsgType::MSG_GAME:
      mLog << "[GAME] " << std::setfill(' ') << std::setw(12);
      break;
    case MsgType::MSG_LAB:
      mLog << "[LAB] " << std::setfill(' ') << std::setw(13);
      break;
    case MsgType::MSG_MODULE:
      mLog << "[MODULE] " << std::setfill(' ') << std::setw(12);
      break;
    case MsgType::MSG_STAT:
      mLog << "[STAT] " << std::setfill(' ') << std::setw(12);
      break;
    case MsgType::MSG_SYSTEM:
      mLog << "[SYSTEM] " << std::setfill(' ') << std::setw(10);
      break;
    }
    switch (iLogLevel)
    {
    case(1) :
      mLog << pTimer->getMilliseconds() << "ms : " << message.c_str() << std::endl;
      break;
    case(0) :
      mLog << message.c_str() << std::endl;
      break;
    }
    ++iCntInfo;
    mLog.close();
    break;
  }
}

///////////////////////////////////////////////////////////////////////////////
// LOG SECTION

void Logger::LogSection(std::string name) {
  mLog.open(strLogFile, std::ios::out | std::ios::app);
  if (mLog.is_open()) {
    mLog << std::endl;
    mLog << std::setfill('/') << std::setw(79) << '/' << std::endl;
    mLog << "// " << name.c_str() << std::endl;
    mLog << std::setfill('/') << std::setw(79) << '/' << std::endl;
    mLog << std::endl;
    mLog.close();
  }
}

///////////////////////////////////////////////////////////////////////////////
// CLOSE THE LOG

void Logger::CloseLog() {
  mLog.open(strLogFile, std::ios::out | std::ios::app);

  if (mLog.is_open()) {
    mLog << std::endl << std::endl;
    mLog << std::setfill('/') << std::setw(79) << '/' << std::endl;
    mLog << "//" << std::endl;
    mLog << "// MESSAGE COUNT" << std::endl << "//" << std::endl;
    mLog << "// [ERROR]   : " << iCntError << std::endl;
    mLog << "// [WARNING] : " << iCntWarning << std::endl;
    mLog << "// [INFO]    : " << iCntInfo << std::endl;
    mLog << "//" << std::endl;
    mLog << std::setfill('/') << std::setw(79) << '/' << std::endl;

    mLog.close();
  }

  delete this;
}

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////