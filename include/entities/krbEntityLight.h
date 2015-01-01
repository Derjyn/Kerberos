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
* @date   01 January 2015
* @brief  Light entity
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbEntityLight_h
#define krbEntityLight_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "entities/krbEntCompPhysical.h"
#include "entities/krbEntCompVisual.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

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
    ent_Position = ech_Position.get()->_position;

    _entity.assign<EntCompBillboard>(bbSet);
    ech_Billboard = _entity.component<EntCompBillboard>();
    ent_Billboard = ech_Billboard.get()->_billboard;

    _entity.assign<EntCompLightPoint>(name, sceneMgr);
    ech_LightPoint = _entity.component<EntCompLightPoint>();
    ent_Light = ech_LightPoint.get()->_light;

    ent_Position = position;
    ent_Billboard->setPosition(toOgre(position));
    ent_Light->setPosition(toOgre(position));
  }

  ~EntityLight()
  {
    _entity.destroy();
  }

  // SETTERS //////////////////////////////////////////////////////////////////
  void setPosition(Vector3 position)
  {
    //ent_Position = position;
    ent_Billboard->setPosition(toOgre(position));
    ent_Light->setPosition(toOgre(position));
  }

  void setDiffuseColor(Color color)
  {
    ent_Light->setDiffuseColour(toOgre(color));
  }
  void setSpecularColor(Color color)
  {
    ent_Light->setSpecularColour(toOgre(color));
  }

  void setAttenuation(float range, float constant, 
    float linear, float quadratic)
  {
    ent_Light->setAttenuation(range, constant, linear, quadratic);
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

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbEntityLight_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\