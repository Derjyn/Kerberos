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
* @date   25 December 2014
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

/*****************************************************************************
*****************************************************************************/

#include "utility/krbMath.h"

#include "Ogre3D/OgreColourValue.h"
#include "Ogre3D/OgreVector3.h"

#include <iomanip>
#include <string>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

// COLOR CONVERSION

inline Color toScalar(int r, int g, int b, int a)
{
  return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255);
}
inline Color toScalar(int r, int g, int b, float a)
{
  return Color(r / 255.0f, g / 255.0f, b / 255.0f, a);
}
inline Color toScalar(float r, float g, float b, float a)
{
  return Color(r / 255.0f, g / 255.0f, b / 255.0f, a);
}
inline Color toScalar(Color color)
{
  return Color(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
}

/*****************************************************************************
*****************************************************************************/

// STRING CONVERSION

inline string toString(const int& i)
{
  return to_string(i);
}
inline string toString(const unsigned int& ui)
{
  return to_string(ui);
}
inline string toString(const float& f, const int n = 3)
{
  stringstream out;
  out << fixed << setprecision(n) << f;

  return out.str();
}
inline string toString(const double& d, const int n = 3)
{
  stringstream out;
  out << fixed << setprecision(n) << d;

  return out.str();
}
inline string toString(const Vector3& vec, const int n = 3)
{
  stringstream out;
  out << fixed << setprecision(n) << vec.x << " ";
  out << fixed << setprecision(n) << vec.y << " ";
  out << fixed << setprecision(n) << vec.z;

  return out.str();
}
inline string toString(const Ogre::Vector3& vec, const int n = 3)
{
  stringstream out;
  out << fixed << setprecision(n) << vec.x << " ";
  out << fixed << setprecision(n) << vec.y << " ";
  out << fixed << setprecision(n) << vec.z;

  return out.str();
}

/*****************************************************************************
*****************************************************************************/

// KRB <-> OGRE CONVERSION

inline Ogre::ColourValue toOgre(Color color)
{
  return Ogre::ColourValue(color.r, color.g, color.b, color.a);
}
inline Color toKRB(Ogre::ColourValue color)
{
  return Color(color.r, color.g, color.b, color.a);
}

inline Ogre::Vector3 toOgre(const Vector3& vector)
{
  return Ogre::Vector3(vector.x, vector.y, vector.z);
}
inline Vector3 toKRB(const Ogre::Vector3& vector)
{
  return Vector3(vector.x, vector.y, vector.z);
}

/*****************************************************************************
*****************************************************************************/

// KRB <-> BULLET CONVERSION

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbConverter_h

/***]EOF[*********************************************************************/