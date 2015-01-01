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
* @file   krbEntCompVisual.h
* @author Nathan Harris
* @date   31 December 2014
* @brief  ECS visual components
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbEntCompVisual_h
#define krbEntCompVisual_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "entities/krbEntCompBase.h"

#include "Ogre3D/OgreBillboard.h"
#include "Ogre3D/OgreBillboardSet.h"
#include "Ogre3D/OgreCamera.h"
#include "Ogre3D/OgreEuler.h"
#include "Ogre3D/OgreLight.h"
#include "Ogre3D/OgreSceneManager.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

struct EntCompNode : EX::Component<EntCompNode>
{
  EntCompNode(string name, Ogre::SceneNode* parentNode)
  {
    _node = parentNode->createChildSceneNode(name + "_NODE");
  }

  Ogre::SceneNode* _node;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

struct EntCompBillboard : EX::Component<EntCompBillboard> 
{
public:
  EntCompBillboard(Ogre::BillboardSet* bbSet)
  {
    _billboardSet = bbSet;
    _billboard = _billboardSet->createBillboard(Ogre::Vector3::ZERO);
  }

  Ogre::BillboardSet* _billboardSet;
  Ogre::Billboard* _billboard;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

struct EntCompCamera : EX::Component<EntCompCamera>
{
public:
  EntCompCamera(string name, Ogre::SceneManager* sceneMgr)
  {
    _camera = sceneMgr->createCamera(name + "_CAMERA");
    _camera->setNearClipDistance(0.01);
    _camera->setAutoAspectRatio(true);
  }

  Ogre::Camera* _camera;
  Ogre::Viewport* _viewport;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

struct EntCompLightPoint : EX::Component<EntCompLightPoint>
{
public:
  EntCompLightPoint(string name, Ogre::SceneManager* sceneMgr)
  {
    _light = sceneMgr->createLight(name + "_LIGHT_POINT");
    _light->setType(Ogre::Light::LT_POINT);
  }

  Ogre::Light* _light;
};

struct EntCompLightSpot : EX::Component<EntCompLightSpot>
{
public:
  EntCompLightSpot(string name, Ogre::SceneManager* sceneMgr)
  {
    _light = sceneMgr->createLight(name + "_LIGHT_SPOT");
    _light->setType(Ogre::Light::LT_SPOTLIGHT);
  }

  Ogre::Light* _light;
};

struct EntCompLightInfinite : EX::Component<EntCompLightInfinite>
{
public:
  EntCompLightInfinite(string name, Ogre::SceneManager* sceneMgr)
  {
    _light = sceneMgr->createLight(name + "_LIGHT_INFINITE");
    _light->setType(Ogre::Light::LT_SPOTLIGHT);
  }

  Ogre::Light* _light;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbEntCompVisual_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\