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
\file   krbConfig.h
\author Nathan Harris
\date   13 December 2014
\brief  Takes care of parsing properties from file, thanks to Ook!
\details
  Need to write some stuff. Me so lazy.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbConfig_h
#define krbConfig_h

/*****************************************************************************
*****************************************************************************/

#include "..\KerberosUtility.h"

#include <string>

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class Config
{
public:
  Config(std::string cfgFile);
  ~Config();

  bool          getBool(std::string section, std::string key);
  int           getInt(std::string section, std::string key);
  float         getFloat(std::string section, std::string key);
  std::string   getString(std::string section, std::string key);
  Color         getColor(std::string, std::string key);
  Vector3       getVec3(std::string, std::string key);

  std::string   getFileName();

protected:
  std::string   strFile;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbConfig_h

/***]EOF[*********************************************************************/