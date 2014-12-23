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
* @file   krbEntityPhysicsStatic.h
* @author Nathan Harris
* @date   22 December 2014
* @brief  Static physics entity. Good for solid scene meshes.
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntityPhysicsStatic_h
#define krbEntityPhysicsStatic_h

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntityPhysics.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief Static physics entity. Good for solid scene meshes.
//
class EntityPhysicsStatic : public EntityPhysics
{
public:
  EntityPhysicsStatic(string name, string mesh,
    int maxAge, float createTime, Vector3 position,
    Ogre::SceneManager* sceneMgr, btDynamicsWorld* world);

  ~EntityPhysicsStatic();

protected:
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbEntityPhysicsStatic_h

/***]EOF[*********************************************************************/