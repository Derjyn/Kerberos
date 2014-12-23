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
* @date   22 December 2014
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

#include "BtOgre/BtOgreGP.h"
#include "BtOgre/BtOgrePG.h"

/*****************************************************************************
*****************************************************************************/

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
  virtual void setBulletWorld(btDynamicsWorld* world)
  {
    m_BulletWorld = world;
  }

  virtual void setGravity(Vector3 gravity)
  {
    ent_Body->setGravity(toBullet(gravity));
  }

  virtual void setMass(float mass)
  {
    f_MassKg = mass;
  }

  virtual void setConvexMargin(float margin)
  {
    f_Margin = margin;
    ent_ShapeConvex->setMargin(f_Margin);
  }
  virtual void setTrimeshMargin(float margin)
  {
    f_Margin = margin;
    ent_ShapeTrimesh->setMargin(f_Margin);
  }

  // GETTERS //////////////////////////////////////////////////////////////////

  inline bool isResting() 
  { 
    b_Resting = ent_Body->isActive();

    return b_Resting; 
  }

  inline Vector3 getVelocity() // Returns linear velocity.
  {
    ent_Velocity = toKRB(ent_Body->getLinearVelocity());

    return ent_Velocity;
  }

protected:
  bool      b_Resting;
  float     f_Margin;
  float     f_Gravity;
  float     f_MassKg;
  Vector3   ent_Velocity;

  btDynamicsWorld*        m_BulletWorld;
  btConvexHullShape*      ent_ShapeConvex;
  btBvhTriangleMeshShape* ent_ShapeTrimesh;
  btRigidBody*            ent_Body;
  btTransform             ent_Transform;
  BtOgre::RigidBodyState* ent_State;
  Ogre::Entity*           ent_Mesh;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbEntityDynamic_h

/***]EOF[*********************************************************************/