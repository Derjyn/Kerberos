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
* @file   krbLogger.h
* @author Nathan Harris
* @date   31 December 2014
* @brief  Takes care of logging information to file
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbLogger_h
#define krbLogger_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include <fstream>
#include <string>

using namespace std;

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\/

namespace Kerberos
{

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

//
//! \brief Handy logger that writes to file. It's pretty.
//
class Logger
{
public:
  Logger(string file, int level, string version);
  ~Logger();

  typedef enum
  {
    LVL_ERROR,
    LVL_INFO,
    LVL_WARNING    
  } MsgLevel;

  typedef enum
  {
    MSG_BRAIN,
    MSG_ENTITY,
    MSG_LAB,
    MSG_NOTE,
    MSG_STAT,
    MSG_SYSTEM
  } MsgType;

  void logMessage(MsgLevel level, MsgType type, std::string message);
  void logSection(std::string name);
  void closeLog();
  void closeLog(string clock);

private:
  std::ofstream   ofs_Log;
  std::string     str_File;

  int             i_LogLevel;
  int             i_CntError;
  int             i_CntWarning;
  int             i_CntInfo;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbLogger_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\