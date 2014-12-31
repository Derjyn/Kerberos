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
* @file   krbEntityCamera.h
* @author Nathan Harris
* @date   30 December 2014
* @brief  Camera entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntityCamera_h
#define krbEntityCamera_h

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntCompPhysical.h"
#include "entities/krbEntCompVisual.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class EntityCamera
{
public:
  EntityCamera(string name, Vector3 position,
    Ogre::BillboardSet* bbSet, Ogre::SceneManager* sceneMgr)
  {
    ent_Name = name;

    _entity = m_EntX.entities.create();

    _entity.assign<EntCompPosition>(position);
    ech_Position = _entity.component<EntCompPosition>();

    _entity.assign<EntCompDirection>();
    ech_Direction = _entity.component<EntCompDirection>();

    _entity.assign<EntCompBillboard>(bbSet, position);
    ech_Billboard = _entity.component<EntCompBillboard>();

    _entity.assign<EntCompCamera>(name, position, sceneMgr);
    ech_Camera = _entity.component<EntCompCamera>();

    ent_Position    = ech_Position.get()->_position;
    ent_Euler       = ech_Direction.get()->_euler;
    ent_Billboard   = ech_Billboard.get()->_billboard;
    ent_Camera      = ech_Camera.get()->_camera;    
    ent_Viewport    = ech_Camera.get()->_viewport;
  }

  ~EntityCamera()
  {
    _entity.destroy();
  }
  
  // ACTIONS //////////////////////////////////////////////////////////////////
  void lookAt(Vector3 target)
  {
    ent_Euler.direction(toOgre(target - ent_Position));
    ent_Camera->setOrientation(ent_Euler);
  }

  // X MOVEMENT
  void moveAbscissa(float speed)
  {
    ent_Camera->move(ent_Euler.left() * speed);
    ent_Position = toKRB(ent_Camera->getPosition());
    ent_Billboard->setPosition(ent_Camera->getPosition());
  }
  // Y MOVEMENT
  void moveOrdinate(float speed)
  {
    ent_Camera->move(ent_Euler.up() * speed);
    ent_Position = toKRB(ent_Camera->getPosition());
    ent_Billboard->setPosition(ent_Camera->getPosition());
  }
  // Z MOVEMENT
  void moveApplicate(float speed)
  {
    ent_Camera->move(ent_Euler.forward() * speed);
    ent_Position = toKRB(ent_Camera->getPosition());
    ent_Billboard->setPosition(ent_Camera->getPosition());
  }

  // SETTERS //////////////////////////////////////////////////////////////////
  void setPosition(Vector3 position)
  {    
    ent_Billboard->setPosition(toOgre(position));
    ent_Camera->setPosition(toOgre(position));
    ent_Position = position;
  }

  void setOrientation(float yaw, float pitch, float speed)
  {
    ent_Euler.yaw(Ogre::Radian(yaw * speed));
    ent_Euler.pitch(Ogre::Radian(pitch * speed));
    ent_Euler.setRoll(Ogre::Degree(0));

    ent_Camera->setOrientation(ent_Euler);
  }

  void setViewport(Ogre::Viewport* viewport)
  {
    ent_Viewport = viewport;
  }

  void setActive()
  {
    ent_Viewport->setCamera(ent_Camera);
  }

  // GETTERS //////////////////////////////////////////////////////////////////
  string getName()      { return ent_Name; }
  Vector3 getPosition() { return ent_Position; }
  Vector3 getForward()  { return toKRB(ent_Euler.forward()); }
  Vector3 getSideward() { return toKRB(ent_Euler.left()); }
  Vector3 getUpward()   { return toKRB(ent_Euler.up()); }

private:
  string                      ent_Name;
  Vector3                     ent_Position;
  Ogre::Euler                 ent_Euler;
  Ogre::Viewport*             ent_Viewport;
  Ogre::Camera*               ent_Camera;
  Ogre::Billboard*            ent_Billboard;

  EX::EntityX                 m_EntX;
  EX::Entity                  _entity;
  EntCompPosition::Handle     ech_Position;
  EntCompDirection::Handle    ech_Direction;
  EntCompBillboard::Handle    ech_Billboard;
  EntCompCamera::Handle       ech_Camera;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbEntityLight_h

/***]EOF[*********************************************************************/