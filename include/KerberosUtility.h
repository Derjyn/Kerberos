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
* @file   KerberosUtility.h
* @author Nathan Harris
* @date   14 December 2014
* @brief  Various handy utilities
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef KerberosUtility_h
#define KerberosUtility_h

/*****************************************************************************
*****************************************************************************/

#include "Ogre3D\OgreColourValue.h"
#include "Ogre3D\OgreVector2.h"
#include "Ogre3D\OgreVector3.h"

#include "Bullet\LinearMath\btVector3.h"

#include <string>

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

// COLOR
class Color
{
public:
  Color()
  {
    r = 1.0f;
    g = 1.0f;
    b = 1.0f;
    a = 1.0f;
  }

  Color(float red, float green, float blue)
  {
    r = red;
    g = green;
    b = blue;
    a = 1.0f;
  }

  Color(float red, float green, float blue, float alpha)
  {
    r = red;
    g = green;
    b = blue;
    a = alpha;
  }

  float r, g, b, a;
};

// VECTOR 2
class Vector2
{
public:
  Vector2()
  {
    x = 0.0f;
    y = 0.0f;
  }

  Vector2(float vx, float vy)
  {
    x = float(vx);
    y = float(vy);
  }

  Vector2 operator+(const Vector2& v)
  {
    Vector2 result;
    result.x = this->x + v.x;
    result.y = this->y + v.y;

    return result;
  };
  Vector2 operator-(const Vector2& v)
  {
    Vector2 result;
    result.x = this->x - v.x;
    result.y = this->y - v.y;

    return result;
  };
  Vector2 operator*(const Vector2& v)
  {
    Vector2 result;
    result.x = this->x * v.x;
    result.y = this->y * v.y;

    return result;
  };

  float x, y;
};

// VECTOR 3
class Vector3
{
public:
  Vector3()
  {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }

  Vector3(float vx, float vy, float vz)
  {
    x = float(vx);
    y = float(vy);
    z = float(vz);
  }

  Vector3 operator+(const Vector3& v)
  {
    Vector3 result;
    result.x = this->x + v.x;
    result.y = this->y + v.y;
    result.z = this->z + v.z;

    return result;
  };
  Vector3 operator-(const Vector3& v)
  {
    Vector3 result;
    result.x = this->x - v.x;
    result.y = this->y - v.y;
    result.z = this->z - v.z;

    return result;
  };
  Vector3 operator*(const Vector3& v)
  {
    Vector3 result;
    result.x = this->x * v.x;
    result.y = this->y * v.y;
    result.z = this->z * v.z;

    return result;
  };

  float x, y, z;
};

/*****************************************************************************
*****************************************************************************/
// CONVERTERS

// VECTORS
static Color toKerberos(const Ogre::ColourValue& color)
{
  return Color(color.r, color.g, color.b, color.a);
}
static Ogre::ColourValue toOgre(const Color& color)
{
  return Ogre::ColourValue(color.r, color.g, color.b, color.a);
}
static Vector2 toKerberos(const Ogre::Vector2& v)
{
  return Vector2(v.x, v.y);
}
static Ogre::Vector2 toOgre(const Vector2& v)
{
  return Ogre::Vector2(v.x, v.y);
}
static Vector3 toKerberos(const Ogre::Vector3& v)
{
  return Vector3(v.x, v.y, v.z);
}
static Vector3 toKerberos(const btVector3& v)
{
  return Vector3(v.x(), v.y(), v.z());
}
static Ogre::Vector3 toOgre(const Vector3& v)
{
  return Ogre::Vector3(v.x, v.y, v.z);
}
static btVector3 toBullet(const Vector3& v)
{
  return btVector3(v.x, v.y, v.z);
}

// STRINGS
static std::string toString(const int& i)
{
  return std::to_string(i);
}
static std::string toString(const unsigned int& ui)
{
  return std::to_string(ui);
}
static std::string toString(const float& f, const int n = 3)
{
  std::stringstream out;
  out << std::fixed << std::setprecision(n) << f;

  return out.str();
}
static std::string toString(const double& d, const int n = 3)
{
  std::stringstream out;
  out << std::fixed << std::setprecision(n) << d;

  return out.str();
}
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

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // KerberosUtility_h

/***]EOF[*********************************************************************/