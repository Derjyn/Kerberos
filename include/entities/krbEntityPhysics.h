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
* @file   krbEntityPhysics.h
* @author Nathan Harris
* @date   26 December 2014
* @brief  Physics entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntityPhysics_h
#define krbEntityPhysics_h

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntity.h"

/*****************************************************************************
*****************************************************************************/

class btDynamicsWorld;
class btConvexHullShape;
class btTriangleMeshShape;
class btRigidBody;

namespace BtOgre
{
  class RigidBodyState;
}

namespace Ogre
{
  class Entity;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief Physics entity base class
//
class EntityPhysics : public Entity
{
public:
  virtual void setGravity(Vector3 gravity)
  {
  }

  virtual void setMass(float mass)
  {
    f_MassKg = mass;
  }

  // GETTERS //////////////////////////////////////////////////////////////////

  inline bool isResting() 
  { 
    return b_Resting; 
  }

  inline Vector3 getVelocity()
  {
    return ent_Velocity;
  }

protected:
  bool      b_Resting;
  float     f_Margin;
  float     f_Gravity;
  float     f_MassKg;
  Vector3   ent_Velocity;

  Ogre::Entity*               ent_Mesh;
  btRigidBody*                ent_Body;
  btConvexHullShape*          ent_HullConvex;
  btTriangleMeshShape*        ent_HullTrimesh;
  BtOgre::RigidBodyState*     ent_State;
  btDynamicsWorld*            m_PhysWorld;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbEntityDynamic_h

/***]EOF[*********************************************************************/