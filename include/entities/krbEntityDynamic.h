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
\file   krbEntityDynamic.h
\author Nathan Harris
\date   14 December 2014
\brief  Dynamic entity base class. Dynamic entities are graced with physics.
\details
Need to write some stuff. Me so lazy.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntityDynamic_h
#define krbEntityDynamic_h

/*****************************************************************************
*****************************************************************************/

#include "entities\krbEntity.h"

#include "BtOgre\BtOgreGP.h"
#include "BtOgre\BtOgrePG.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class EntityDynamic : public Entity
{
public:
  EntityDynamic() {}
  virtual ~EntityDynamic() {}

  virtual void update() = 0;

  btRigidBody* getBody(void) { return objBody; }

protected:
  btDynamicsWorld*        pBulletWorld;
  btRigidBody*            objBody;
  BtOgre::RigidBodyState* objState;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbEEntityDynamic_h

/***]EOF[*********************************************************************/