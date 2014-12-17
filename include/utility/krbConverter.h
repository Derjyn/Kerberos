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
* @file   krbConverter.h
* @author Nathan Harris
* @date   17 December 2014
* @brief  Various functions for converting to/from various other things
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbConverter_h
#define krbConverter_h

#include <iomanip>
#include <string>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

// STRING CONVERSION
static string toString(const int& i)
{
  return to_string(i);
}
static string toString(const unsigned int& ui)
{
  return to_string(ui);
}
static string toString(const float& f, const int n = 3)
{
  stringstream out;
  out << fixed << setprecision(n) << f;

  return out.str();
}
static string toString(const double& d, const int n = 3)
{
  stringstream out;
  out << fixed << setprecision(n) << d;

  return out.str();
}
/*
static std::string toString(const Vector3& vec, const int n = 3)
{
  std::stringstream out;
  out << std::fixed << std::setprecision(n) << vec.x << " ";
  out << std::fixed << std::setprecision(n) << vec.y << " ";
  out << std::fixed << std::setprecision(n) << vec.z;

  return out.str();
}
static std::string toString(const Ogre::Vector3& vec, const int n = 3)
{
  std::stringstream out;
  out << std::fixed << std::setprecision(n) << vec.x << " ";
  out << std::fixed << std::setprecision(n) << vec.y << " ";
  out << std::fixed << std::setprecision(n) << vec.z;

  return out.str();
}
static std::string toString(const btVector3& vec, const int n = 3)
{
  std::stringstream out;
  out << std::fixed << std::setprecision(n) << vec.x() << " ";
  out << std::fixed << std::setprecision(n) << vec.y() << " ";
  out << std::fixed << std::setprecision(n) << vec.z();

  return out.str();
}
*/
/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbConverter_h

/***]EOF[*********************************************************************/