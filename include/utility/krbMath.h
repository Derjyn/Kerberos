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
* @file   krbMath.h
* @author Nathan Harris
* @date   19 December 2014
* @brief  Helpful maths
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbMath_h
#define krbMath_h

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
  Vector2 operator/(const Vector2& v)
  {
    Vector2 result;
    result.x = this->x / v.x;
    result.y = this->y / v.y;

    return result;
  };
  Vector2 operator*(const float& v)
  {
    Vector2 result;
    result.x = this->x * v;
    result.y = this->y * v;

    return result;
  };
  Vector2 operator/(const float& v)
  {
    Vector2 result;
    result.x = this->x * v;
    result.y = this->y * v;

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
  Vector3 operator/(const Vector3& v)
  {
    Vector3 result;
    result.x = this->x / v.x;
    result.y = this->y / v.y;
    result.z = this->z / v.z;

    return result;
  };
  Vector3 operator*(const float& v)
  {
    Vector3 result;
    result.x = this->x * v;
    result.y = this->y * v;
    result.z = this->z * v;

    return result;
  };
  Vector3 operator/(const float& v)
  {
    Vector3 result;
    result.x = this->x * v;
    result.y = this->y * v;
    result.z = this->z * v;

    return result;
  };
  
  float x, y, z;
};

// TIME VECTOR
class TimeVector
{
public:
  TimeVector()
  {
    day = 0;
    hr  = 0;
    min = 0;
    sec = 0;
    ms  = 0;
  }

  unsigned int day;
  unsigned int hr;
  unsigned int min;
  unsigned int sec;
  double ms;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbMath_h

/***]EOF[*********************************************************************/