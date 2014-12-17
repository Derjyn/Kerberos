/*******************************************************************************
*                                                                              *
* Copyright (C) 2014 Nathan Harris                                             *
*                                                                              *
* This file is part of Kerberos.                                               *
*                                                                              *
*   Kerberos is free software. Enjoy it, modify it, contribute to it.          *
*                                                                              *
*******************************************************************************/

/**
* @file   krbLogger.cpp
* @author Nathan Harris
* @date   17 December 2014
* @brief  Takes care of logging information to file
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "core/krbLogger.h"

#include <iomanip>

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

Logger::Logger(std::string file, int level, string version)
{
  str_File  = file;
  i_LogLevel   = level;
  i_CntError   = 0;
  i_CntWarning = 0;
  i_CntInfo    = 0;

  ofs_Log.open(str_File);

  if (ofs_Log.is_open())
  {
    time_t rawtime;
    struct tm timeinfo;
    char buffer[80];
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);

    strftime(buffer, 80, "%m-%d-%y %I:%M:%S", &timeinfo);
    ofs_Log << std::setfill('/') << std::setw(79) << '/' << std::endl;
    ofs_Log << "//" << std::endl;
    ofs_Log << "// Kerberos Debug Log" << std::endl;
    ofs_Log << "// Engine version " << version << std::endl;
    ofs_Log << "// " << std::endl;
    ofs_Log << "// Log created: " << buffer << std::endl;
    ofs_Log << "//" << std::endl;
    ofs_Log << std::setfill('/') << std::setw(79) << '/' << std::endl;
    ofs_Log << std::endl;

    ofs_Log.close();
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
    case LVL_ERROR:
      ofs_Log.open(str_File, std::ios::out | std::ios::app);
      ofs_Log << "[ERROR] ";
      switch (type)
      {
        case MsgType::MSG_BRAIN:
          ofs_Log << "[BRAIN] " << std::setfill(' ') << std::setw(12);
          break;
        case MsgType::MSG_ENTITY:
          ofs_Log << "[ENTITY] " << std::setfill(' ') << std::setw(13);
          break;
        case MsgType::MSG_LAB:
          ofs_Log << "[LAB] " << std::setfill(' ') << std::setw(13);
          break;
        case MsgType::MSG_NOTE:
          ofs_Log << "[NOTE] " << std::setfill(' ') << std::setw(13);
          break;
        case MsgType::MSG_STAT:
          ofs_Log << "[STAT] " << std::setfill(' ') << std::setw(12);
          break;
        case MsgType::MSG_SYSTEM:
          ofs_Log << "[SYSTEM] " << std::setfill(' ') << std::setw(10);
          break;
      }
      switch (i_LogLevel)
      {
        case(1) :
          ofs_Log << "[!!!]" << message.c_str() << std::endl;
          break;
        case(0) :
          ofs_Log << message.c_str() << std::endl;
          break;
      }
      ++i_CntError;
      ofs_Log.close();
      break;

    case LVL_INFO:
      ofs_Log.open(str_File, std::ios::out | std::ios::app);
      ofs_Log << "[INFO] ";
      switch (type)
      {
        case MsgType::MSG_BRAIN:
          ofs_Log << "[BRAIN] " << std::setfill(' ') << std::setw(12);
          break;
        case MsgType::MSG_ENTITY:
          ofs_Log << "[ENTITY] " << std::setfill(' ') << std::setw(13);
          break;
        case MsgType::MSG_LAB:
          ofs_Log << "[LAB] " << std::setfill(' ') << std::setw(13);
          break;
        case MsgType::MSG_NOTE:
          ofs_Log << "[NOTE] " << std::setfill(' ') << std::setw(13);
          break;
        case MsgType::MSG_STAT:
          ofs_Log << "[STAT] " << std::setfill(' ') << std::setw(12);
          break;
        case MsgType::MSG_SYSTEM:
          ofs_Log << "[SYSTEM] " << std::setfill(' ') << std::setw(10);
          break;
      }
      switch (i_LogLevel)
      {
        case(1) :
          ofs_Log << "[!!!]" << message.c_str() << std::endl;
          break;
        case(0) :
          ofs_Log << message.c_str() << std::endl;
          break;
      }
      ++i_CntInfo;
      ofs_Log.close();
      break;

    case LVL_WARNING:
      ofs_Log.open(str_File, std::ios::out | std::ios::app);
      ofs_Log << "[WARNING] ";
      switch (type)
      {
        case MsgType::MSG_BRAIN:
          ofs_Log << "[BRAIN] " << std::setfill(' ') << std::setw(12);
          break;
        case MsgType::MSG_ENTITY:
          ofs_Log << "[ENTITY] " << std::setfill(' ') << std::setw(13);
          break;
        case MsgType::MSG_LAB:
          ofs_Log << "[LAB] " << std::setfill(' ') << std::setw(13);
          break;
        case MsgType::MSG_NOTE:
          ofs_Log << "[NOTE] " << std::setfill(' ') << std::setw(13);
          break;
        case MsgType::MSG_STAT:
          ofs_Log << "[STAT] " << std::setfill(' ') << std::setw(12);
          break;
        case MsgType::MSG_SYSTEM:
          ofs_Log << "[SYSTEM] " << std::setfill(' ') << std::setw(10);
          break;
      }
      switch (i_LogLevel)
      {
        case(1) :
          ofs_Log << "[!!!]" << message.c_str() << std::endl;
          break;
        case(0) :
          ofs_Log << message.c_str() << std::endl;
          break;
      }
      ++i_CntWarning;
      ofs_Log.close();
      break;
  }
}

/*****************************************************************************
*****************************************************************************/

void Logger::logSection(std::string name) 
{
  ofs_Log.open(str_File, std::ios::out | std::ios::app);
  if (ofs_Log.is_open()) 
  {
    ofs_Log << std::endl;
    ofs_Log << std::setfill('/') << std::setw(79) << '/' << std::endl;
    ofs_Log << "// " << name.c_str() << std::endl;
    ofs_Log << std::setfill('/') << std::setw(79) << '/' << std::endl;
    ofs_Log << std::endl;
    ofs_Log.close();
  }
}

/*****************************************************************************
*****************************************************************************/

void Logger::closeLog()
{
  ofs_Log.open(str_File, std::ios::out | std::ios::app);

  if (ofs_Log.is_open()) 
  {
    ofs_Log << endl;
    ofs_Log << setfill('/') << setw(79) << '/' << endl;
    ofs_Log << "//" << std::endl;
    ofs_Log << "// MESSAGE COUNT" << endl;
    ofs_Log << "// --------------------" << endl;
    ofs_Log << "// [ERROR]   : " << i_CntError << endl;
    ofs_Log << "// [INFO]    : " << i_CntInfo << endl;
    ofs_Log << "// [WARNING] : " << i_CntWarning << endl;
    ofs_Log << "//" << endl;
    ofs_Log << setfill('/') << setw(79) << '/';

    ofs_Log.close();
  }
}

void Logger::closeLog(string clock)
{
  ofs_Log.open(str_File, ios::out | ios::app);

  if (ofs_Log.is_open()) 
  {
    ofs_Log << endl;
    ofs_Log << setfill('/') << setw(79) << '/' << endl;
    ofs_Log << "//" << std::endl;
    ofs_Log << "// RUN TIME: " << clock << std::endl;
    ofs_Log << "//" << std::endl;
    ofs_Log << "// MESSAGE COUNT" << endl;
    ofs_Log << "// --------------------" << endl;
    ofs_Log << "// [ERROR]   : " << i_CntError << endl;
    ofs_Log << "// [INFO]    : " << i_CntInfo << endl;
    ofs_Log << "// [WARNING] : " << i_CntWarning << endl;
    ofs_Log << "//" << std::endl;
    ofs_Log << setfill('/') << setw(79) << '/';

    ofs_Log.close();
  }
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/