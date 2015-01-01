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
* @file   krbEntCompPhysical.h
* @author Nathan Harris
* @date   31 December 2014
* @brief  ECS physical components
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbEntCompPhysical_h
#define krbEntCompPhysical_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "entities/krbEntCompBase.h"

#include "Ogre3D/OgreEuler.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

struct EntCompPosition : EX::Component<EntCompPosition> 
{
public:
  EntCompPosition(float x, float y, float z)
  {
    _position.x = x;
    _position.y = y;
    _position.z = z;
  }
  EntCompPosition(Vector3 position)
  {
    _position = position;
  }

  Vector3 _position;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

struct EntCompDirection : EX::Component<EntCompDirection>
{
public:
  EntCompDirection()
  {
    _euler.yaw(Ogre::Radian(0));
    _euler.pitch(Ogre::Radian(0));
    _euler.roll(Ogre::Radian(0));
  }
  EntCompDirection(Vector3 direction)
  {
    _euler.yaw(Ogre::Radian(direction.x));
    _euler.pitch(Ogre::Radian(direction.y));
    _euler.roll(Ogre::Radian(direction.z));
  }

  Ogre::Euler _euler;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbEntCompPhysical_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\