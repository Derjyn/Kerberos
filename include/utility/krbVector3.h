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
* @file   krbVector3.h
* @author Nathan Harris
* @date   31 December 2014
* @brief  Vector3 class with support for Ogre3D and Bullet
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbVector3_h
#define krbVector3_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "Ogre3D/OgreVector3.h"
#include "Bullet/LinearMath/btVector3.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

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
  
  float x, y, z;

  // KRB, OGRE, & BULLET EQUALS OPERATOR //////////////////////////////////////
  Vector3 operator=(const Vector3& v)
  {
    Vector3 result;
    result.x = v.x;
    result.y = v.y;
    result.z = v.z;

    return result;
  };
  Vector3 operator=(const Ogre::Vector3& v)
  {
    Vector3 result;
    result.x = v.x;
    result.y = v.y;
    result.z = v.z;

    return result;
  };
  Vector3 operator=(const btVector3& v)
  {
    Vector3 result;
    result.x = v.x();
    result.y = v.y();
    result.z = v.z();

    return result;
  };

  // KRB, OGRE, & BULLET ADD OPERATOR /////////////////////////////////////////
  Vector3 operator+(const Vector3& v)
  {
    Vector3 result;
    result.x = this->x + v.x;
    result.y = this->y + v.y;
    result.z = this->z + v.z;

    return result;
  };
  Vector3 operator+(const Ogre::Vector3& v)
  {
    Vector3 result;
    result.x = this->x + v.x;
    result.y = this->y + v.y;
    result.z = this->z + v.z;

    return result;
  };
  Vector3 operator+(const btVector3& v)
  {
    Vector3 result;
    result.x = this->x + v.x();
    result.y = this->y + v.y();
    result.z = this->z + v.z();

    return result;
  };

  // KRB, OGRE, & BULLET MINUS OPERATOR ///////////////////////////////////////
  Vector3 operator-(const Vector3& v)
  {
    Vector3 result;
    result.x = this->x - v.x;
    result.y = this->y - v.y;
    result.z = this->z - v.z;

    return result;
  };
  Vector3 operator-(const Ogre::Vector3& v)
  {
    Vector3 result;
    result.x = this->x - v.x;
    result.y = this->y - v.y;
    result.z = this->z - v.z;

    return result;
  };
  Vector3 operator-(const btVector3& v)
  {
    Vector3 result;
    result.x = this->x - v.x();
    result.y = this->y - v.y();
    result.z = this->z - v.z();

    return result;
  };

  // KRB, OGRE, & BULLET MULTIPLY OPERATOR ////////////////////////////////////
  Vector3 operator*(const Vector3& v)
  {
    Vector3 result;
    result.x = this->x * v.x;
    result.y = this->y * v.y;
    result.z = this->z * v.z;

    return result;
  };
  Vector3 operator*(const Ogre::Vector3& v)
  {
    Vector3 result;
    result.x = this->x * v.x;
    result.y = this->y * v.y;
    result.z = this->z * v.z;

    return result;
  };
  Vector3 operator*(const btVector3& v)
  {
    Vector3 result;
    result.x = this->x * v.x();
    result.y = this->y * v.y();
    result.z = this->z * v.z();

    return result;
  };

  // KRB, OGRE, & BULLET DIVIDE OPERATOR //////////////////////////////////////
  Vector3 operator/(const Vector3& v)
  {
    Vector3 result;
    result.x = this->x / v.x;
    result.y = this->y / v.y;
    result.z = this->z / v.z;

    return result;
  };
  Vector3 operator/(const Ogre::Vector3& v)
  {
    Vector3 result;
    result.x = this->x / v.x;
    result.y = this->y / v.y;
    result.z = this->z / v.z;z;

    return result;
  };
  Vector3 operator/(const btVector3& v)
  {
    Vector3 result;
    result.x = this->x / v.x();
    result.y = this->y / v.y();
    result.z = this->z / v.z();

    return result;
  };

  // MULTIPLY BY FLOAT ////////////////////////////////////////////////////////
  Vector3 operator*(const float& v)
  {
    Vector3 result;
    result.x = this->x * v;
    result.y = this->y * v;
    result.z = this->z * v;

    return result;
  };

  // DIVIDE BY FLOAT //////////////////////////////////////////////////////////
  Vector3 operator/(const float& v)
  {
    Vector3 result;
    result.x = this->x / v;
    result.y = this->y / v;
    result.z = this->z / v;

    return result;
  };
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbVector3_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\