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

#include "core\krbConfig.h"

#include "Ook\Ook.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

Config::Config(std::string cfgFile)
{
  strFile = cfgFile;
}

Config::~Config()
{
}

/*****************************************************************************
*****************************************************************************/

bool Config::getBool(std::string section, std::string key)
{
  Ook::File file;
  file.unserialise(
    std::ifstream(strFile.c_str(), std::ios::in | std::ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  return ookSet[key.c_str()].asBool();
}

int Config::getInt(std::string section, std::string key)
{
  Ook::File file;
  file.unserialise(
    std::ifstream(strFile.c_str(), std::ios::in | std::ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  return ookSet[key.c_str()].asInt();
}

float Config::getFloat(std::string section, std::string key)
{
  Ook::File file;
  file.unserialise(
    std::ifstream(strFile.c_str(), std::ios::in | std::ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  return ookSet[key.c_str()].asFloat();
}

std::string Config::getString(std::string section, std::string key)
{
  Ook::File file;
  file.unserialise(
    std::ifstream(strFile.c_str(), std::ios::in | std::ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  return ookSet[key.c_str()].asString();
}

Color Config::getColor(std::string section, std::string key)
{
  Ook::File file;
  file.unserialise(
    std::ifstream(strFile.c_str(), std::ios::in | std::ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  float r = ookSet[key].atFloat(0);
  float g = ookSet[key].atFloat(1);
  float b = ookSet[key].atFloat(2);
  float a = ookSet[key].atFloat(3);

  return Color(r,g,b,a);
}

Vector3 Config::getVec3(std::string section, std::string key)
{
  Ook::File file;
  file.unserialise(
    std::ifstream(strFile.c_str(), std::ios::in | std::ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  float x = ookSet[key].atFloat(0);
  float y = ookSet[key].atFloat(1);
  float z = ookSet[key].atFloat(2);

  return Vector3(x, y, z);
}

/*****************************************************************************
*****************************************************************************/

std::string Config::getFileName()
{
  return strFile;
}

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos

/***]EOF[*********************************************************************/