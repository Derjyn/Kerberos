/*******************************************************************************
*                                                                              *
* Copyright (C) 2014 Nathan Harris                                             *
*                                                                              *
* This file is part of Kerberos.                                               *
*                                                                              *
*   Kerberos is free software. Enjoy it, modify it, contribute to it.          *
*   For sales inqueries, see <http://www.omglasergunspewpewpew.com/>           *
*                                                                              *
*******************************************************************************/

/**
* @file   krbLogger.h
* @author Nathan Harris
* @date   13 December 2014
* @brief  Utility for logging info to file
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbLogger_h
#define krbLogger_h

/*****************************************************************************
*****************************************************************************/

#include <fstream>
#include <string>

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class Logger
{
public:
  Logger(std::string file, std::string title, int level);
  ~Logger();

  typedef enum MsgLevel
  {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
  } MsgLevel;

  typedef enum MsgType
  {
    MSG_CORE,
    MSG_SYSTEM,
    MSG_MODULE,
    MSG_STAT,
    MSG_LAB
  } MsgType;

  void logMessage(MsgLevel level, MsgType type, std::string message);
  void logSection(std::string name);
  void closeLog();

private:
  std::ofstream mLog;
  std::string strLogFile;

  int iLogLevel;
  int iCntDebug;
  int iCntError;
  int iCntWarning;
  int iCntInfo;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbLogger_h

/***]EOF[*********************************************************************/