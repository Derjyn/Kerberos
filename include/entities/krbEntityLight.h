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
* @file   krbEntityLight.h
* @author Nathan Harris
* @date   30 December 2014
* @brief  Light entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntityLight_h
#define krbEntityLight_h

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntCompPhysical.h"
#include "entities/krbEntCompVisual.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class EntityLight
{
public:
  EntityLight(string name, Vector3 position, 
    Ogre::BillboardSet* bbSet, Ogre::SceneManager* sceneMgr)
  {
    ent_Name = name;

    _entity = m_EntX.entities.create();

    _entity.assign<EntCompPosition>(position);
    ech_Position = _entity.component<EntCompPosition>();

    _entity.assign<EntCompBillboard>(bbSet, position);
    ech_Billboard = _entity.component<EntCompBillboard>();

    _entity.assign<EntCompLightPoint>(name, sceneMgr);
    ech_LightPoint = _entity.component<EntCompLightPoint>();

    ent_Light       = ech_LightPoint.get()->_light;
    ent_Position    = ech_Position.get()->_position;
    ent_Billboard   = ech_Billboard.get()->_billboard;
  }

  ~EntityLight()
  {
    _entity.destroy();
  }

  // SETTERS //////////////////////////////////////////////////////////////////
  void setPosition(Vector3 position)
  {
    ent_Billboard->setPosition(toOgre(position));
    ent_Light->setPosition(toOgre(position));
    ent_Position = position;
  }

  void setDiffuseColor(Color color)
  {
    ent_Light->setDiffuseColour(toOgre(color));
  }
  void setSpecularColor(Color color)
  {
    ent_Light->setSpecularColour(toOgre(color));
  }

  // GETTERS //////////////////////////////////////////////////////////////////
  string getName()
  {
    return ent_Name;
  }

  Vector3 getPosition()
  {
    return toKRB(ent_Light->getPosition());
  }

private:
  string                      ent_Name;
  Vector3                     ent_Position;
  Ogre::Light*                ent_Light;
  Ogre::Billboard*            ent_Billboard;

  EX::EntityX                 m_EntX;
  EX::Entity                  _entity;
  EntCompPosition::Handle     ech_Position;
  EntCompBillboard::Handle    ech_Billboard;
  EntCompLightPoint::Handle   ech_LightPoint;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbEntityLight_h

/***]EOF[*********************************************************************/