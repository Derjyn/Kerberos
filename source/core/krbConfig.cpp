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
* @date   17 December 2014
* @brief  Handles configuration/properties files
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "core/krbConfig.h"

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

double Config::getDouble(string section, string key)
{
  Ook::File file;
  file.unserialise(ifstream(str_File.c_str(), ios::in | ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  return ookSet[key.c_str()].asDouble();
}

std::string Config::getString(string section, string key)
{
  Ook::File file;
  file.unserialise(ifstream(str_File.c_str(), ios::in | ios::binary));
  Ook::Set &ookSet = file[section.c_str()];

  return ookSet[key.c_str()].asString();
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/