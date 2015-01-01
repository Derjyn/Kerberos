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
* @file   krbVector2.h
* @author Nathan Harris
* @date   31 December 2014
* @brief  Vector2 class with support for Ogre3D
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbVector2_h
#define krbVector2_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "Ogre3D/OgreVector2.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

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
  
  float x, y;

  // KRB & OGRE EQUALS OPERATOR ///////////////////////////////////////////////
  Vector2 operator=(const Vector2& v)
  {
    Vector2 result;
    result.x = v.x;
    result.y = v.y;

    return result;
  };
  Vector2 operator=(const Ogre::Vector2& v)
  {
    Vector2 result;
    result.x = v.x;
    result.y = v.y;

    return result;
  };

  // KRB & OGRE ADD OPERATOR //////////////////////////////////////////////////
  Vector2 operator+(const Vector2& v)
  {
    Vector2 result;
    result.x = this->x + v.x;
    result.y = this->y + v.y;

    return result;
  };
  Vector2 operator+(const Ogre::Vector2& v)
  {
    Vector2 result;
    result.x = this->x + v.x;
    result.y = this->y + v.y;

    return result;
  };

  // KRB & OGRE MINUS OPERATOR ////////////////////////////////////////////////
  Vector2 operator-(const Vector2& v)
  {
    Vector2 result;
    result.x = this->x - v.x;
    result.y = this->y - v.y;

    return result;
  };
  Vector2 operator-(const Ogre::Vector2& v)
  {
    Vector2 result;
    result.x = this->x - v.x;
    result.y = this->y - v.y;

    return result;
  };

  // KRB & OGRE MULTIPLY OPERATOR /////////////////////////////////////////////
  Vector2 operator*(const Vector2& v)
  {
    Vector2 result;
    result.x = this->x * v.x;
    result.y = this->y * v.y;

    return result;
  };
  Vector2 operator*(const Ogre::Vector2& v)
  {
    Vector2 result;
    result.x = this->x * v.x;
    result.y = this->y * v.y;

    return result;
  };

  // KRB & OGRE DIVIDE OPERATOR ///////////////////////////////////////////////
  Vector2 operator/(const Vector2& v)
  {
    Vector2 result;
    result.x = this->x / v.x;
    result.y = this->y / v.y;

    return result;
  };
  Vector2 operator/(const Ogre::Vector2& v)
  {
    Vector2 result;
    result.x = this->x / v.x;
    result.y = this->y / v.y;

    return result;
  };

  // MULTIPLY BY FLOAT ////////////////////////////////////////////////////////
  Vector2 operator*(const float& v)
  {
    Vector2 result;
    result.x = this->x * v;
    result.y = this->y * v;

    return result;
  };

  // DIVIDE BY FLOAT //////////////////////////////////////////////////////////
  Vector2 operator/(const float& v)
  {
    Vector2 result;
    result.x = this->x / v;
    result.y = this->y / v;

    return result;
  };
};
///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbVector3_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\