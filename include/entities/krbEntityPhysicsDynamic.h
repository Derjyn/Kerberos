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
* @file   krbEntityPhysicsDynamic.h
* @author Nathan Harris
* @date   22 December 2014
* @brief  Dynamic physics entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntityPhysicsDynamic_h
#define krbEntityPhysicsDynamic_h

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntityPhysics.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief Dynamic physics entity
//
class EntityPhysicsDynamic : public EntityPhysics
{
public:
  EntityPhysicsDynamic(string name, string mesh,
    int maxAge, float createTime, float mass, Vector3 position,
    Ogre::SceneManager* sceneMgr, btDynamicsWorld* world);

  ~EntityPhysicsDynamic();

  void lockAxisLinear(Vector3 axis);
  void lockAxisAngular(Vector3 axis);

protected:
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbEntityPhysicsDynamic_h

/***]EOF[*********************************************************************/