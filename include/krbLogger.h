#pragma once

#ifndef krbLogger_H
#define krbLogger_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbLogger.h
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <string>

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

class Timer;

///////////////////////////////////////////////////////////////////////////////

class Logger {
public:
  typedef enum MsgLevel {
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO
  } MsgLevel;

  typedef enum MsgType {
    MSG_CORE,
    MSG_GAME,
    MSG_LAB,
    MSG_MODULE,
    MSG_STAT,
    MSG_SYSTEM
  } MsgType;

  Logger(Timer *timer);

  void CreateLog(std::string file, std::string title, int level);
  void LogMessage(const MsgLevel, const MsgType, std::string message);
  void LogSection(std::string name);
  void CloseLog();

  void LogDebugCount();
  void LogErrorCount();
  void LogWarningCount();
  void LogInfoCount();

private:
  static void CleanUp();

  Timer* pTimer;

  std::ofstream mLog;
  std::string strLogFile;

  int iCntDebug;
  int iCntError;
  int iCntWarning;
  int iCntInfo;
  int iLogLevel;
};

// EOF ////////////////////////////////////////////////////////////////////////

}
#endif