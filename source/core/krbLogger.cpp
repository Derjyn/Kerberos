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

#include "core\krbLogger.h"

#include <iomanip>

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

Logger::Logger(std::string file, std::string title, int level)
{
  strLogFile  = file;
  iLogLevel   = level;
  iCntDebug   = 0;
  iCntError   = 0;
  iCntWarning = 0;
  iCntInfo    = 0;

  mLog.open(strLogFile);

  if (mLog.is_open())
  {
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

Logger::~Logger()
{
}

/*****************************************************************************
*****************************************************************************/

void Logger::logMessage(MsgLevel level, MsgType type, std::string message)
{
  switch (level) 
  {
  case LOG_ERROR:
    mLog.open(strLogFile, std::ios::out | std::ios::app);
    mLog << "[ERROR] ";
    switch (type)
    {
    case MsgType::MSG_CORE:
      mLog << "[CORE] " << std::setfill(' ') << std::setw(12);
      break;
    case MsgType::MSG_SYSTEM:
      mLog << "[SYSTEM] " << std::setfill(' ') << std::setw(10);
      break;
    case MsgType::MSG_MODULE:
      mLog << "[MODULE] " << std::setfill(' ') << std::setw(13);
      break;
    case MsgType::MSG_STAT:
      mLog << "[STAT] " << std::setfill(' ') << std::setw(12);
      break;
    case MsgType::MSG_LAB:
      mLog << "[LAB] " << std::setfill(' ') << std::setw(13);
      break;
    }
    switch (iLogLevel)
    {
    case(1) :
      mLog << message.c_str() << std::endl;
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
    switch (type)
    {
    case MsgType::MSG_CORE:
      mLog << "[CORE] ";
      break;
    case MsgType::MSG_SYSTEM:
      mLog << "[SYSTEM] ";
      break;
    case MsgType::MSG_MODULE:
      mLog << "[MODULE] ";
      break;
    case MsgType::MSG_STAT:
      mLog << "[STAT] ";
      break;
    case MsgType::MSG_LAB:
      mLog << "[LAB] ";
      break;
    }
    switch (iLogLevel)
    {
    case(1) :
      mLog << message.c_str() << std::endl;
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
    switch (type)
    {
    case MsgType::MSG_CORE:
      mLog << "[CORE] ";
      break;
    case MsgType::MSG_SYSTEM:
      mLog << "[SYSTEM] ";
      break;
    case MsgType::MSG_MODULE:
      mLog << "[MODULE] ";
      break;
    case MsgType::MSG_STAT:
      mLog << "[STAT] ";
      break;
    case MsgType::MSG_LAB:
      mLog << "[LAB] ";
      break;
    }
    switch (iLogLevel)
    {
    case(1) :
      mLog << message.c_str() << std::endl;
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

/*****************************************************************************
*****************************************************************************/

void Logger::logSection(std::string name) 
{
  mLog.open(strLogFile, std::ios::out | std::ios::app);
  if (mLog.is_open()) 
  {
    mLog << std::endl;
    mLog << std::setfill('/') << std::setw(79) << '/' << std::endl;
    mLog << "// " << name.c_str() << std::endl;
    mLog << std::setfill('/') << std::setw(79) << '/' << std::endl;
    mLog << std::endl;
    mLog.close();
  }
}

/*****************************************************************************
*****************************************************************************/

void Logger::closeLog()
{
  mLog.open(strLogFile, std::ios::out | std::ios::app);

  if (mLog.is_open()) 
  {
    mLog << std::endl;
    mLog << std::setfill('/') << std::setw(79) << '/' << std::endl;
    mLog << "//" << std::endl;
    mLog << "// MESSAGE COUNT" << std::endl << "//" << std::endl;
    mLog << "// [ERROR]   : " << iCntError << std::endl;
    mLog << "// [WARNING] : " << iCntWarning << std::endl;
    mLog << "// [INFO]    : " << iCntInfo << std::endl;
    mLog << "//" << std::endl;
    mLog << std::setfill('/') << std::setw(79) << '/';

    mLog.close();
  }
}

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos

/***]EOF[*********************************************************************/