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
\file   krbEntityPhysicsSphere.h
\author Nathan Harris
\date   13 December 2014
\brief  A physics empowered sphere. That has to be worth something.
\details
Need to write some stuff. Me so lazy.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntityPhysicsSphere_h
#define krbEntityPhysicsSphere_h

#include "krbEntityDynamic.h"

#include "BtOgre\BtOgreGP.h"
#include "BtOgre\BtOgrePG.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class EntityPhysicsSphere : public EntityDynamic
{
public:
  EntityPhysicsSphere(
    std::string name, int state, 
    Ogre::Vector3 position, float radius, float mass, 
    float friction, float restitution, float rollFrict,
    float linDamp, float rotDamp,  
    btDynamicsWorld* bulletWorld, Ogre::SceneManager* sceneMgr);
  ~EntityPhysicsSphere();

  void update();

  btSphereShape*  getShape(void);

protected:
  btSphereShape*  objShape;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbEntityPhysicsSphere_h

/***]EOF[*********************************************************************/