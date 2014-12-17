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
* @file   krbConfig.h
* @author Nathan Harris
* @date   17 December 2014
* @brief  Handles configuration/properties files
*
* @details
*  The config class is a handy little guy that makes it easy to deal with
*  properties from files. Thanks to betajaen for developing and providing
*  Ook: https://github.com/betajaen/ook
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbConfig_h
#define krbConfig_h

/*****************************************************************************
*****************************************************************************/

#include <string>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

class Config
{
public:
  Config(string cfgFile);
  ~Config();

  bool          getBool(string section, string key);
  int           getInt(string section, string key);
  float         getFloat(string section, string key);
  double        getDouble(string section, string key);
  string        getString(string section, string key);
  //Color       getColor(std::string, std::string key);
  //Vector3     getVec3(std::string, std::string key);

  string        getFileName();

protected:
  string        str_File;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbConfig_h

/***]EOF[*********************************************************************/