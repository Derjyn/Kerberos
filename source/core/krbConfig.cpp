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
* @file   krbConfig.cpp
* @author Nathan Harris
* @date   19 December 2014
* @brief  Handles configuration/properties files
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "core/krbConfig.h"
#include "utility/krbMath.h"

#include "Ook/Ook.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

Config::Config(string file)
{
  str_File = file;
}

Config::~Config()
{
}

/*****************************************************************************
*****************************************************************************/

bool Config::getBool(string section, string key)
{
  Ook::File file;
  file.unserialise(ifstream(str_File.c_str(), ios::in | ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  return ookSet[key.c_str()].asBool();
}

int Config::getInt(std::string section, std::string key)
{
  Ook::File file;
  file.unserialise(ifstream(str_File.c_str(), ios::in | ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  return ookSet[key.c_str()].asInt();
}

float Config::getFloat(string section, string key)
{
  Ook::File file;
  file.unserialise(ifstream(str_File.c_str(), ios::in | ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  return ookSet[key.c_str()].asFloat();
}

std::string Config::getString(string section, string key)
{
  Ook::File file;
  file.unserialise(ifstream(str_File.c_str(), ios::in | ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  return ookSet[key.c_str()].asString();
}

Color Config::getColor(string section, std::string key)
{
  Ook::File file;
  file.unserialise(ifstream(str_File.c_str(), ios::in | ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  float r = ookSet[key].atFloat(0);
  float g = ookSet[key].atFloat(1);
  float b = ookSet[key].atFloat(2);
  float a = ookSet[key].atFloat(3);

  return Color(r,g,b,a);
}

Vector3 Config::getVec3(string section, string key)
{
  Ook::File file;
  file.unserialise(ifstream(str_File.c_str(), ios::in | ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  float x = ookSet[key].atFloat(0);
  float y = ookSet[key].atFloat(1);
  float z = ookSet[key].atFloat(2);

  return Vector3(x, y, z);
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/