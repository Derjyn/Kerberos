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
\file   krbEntity.h
\author Nathan Harris
\date   14 December 2014
\brief  Base class for entities.
\details
Need to write some stuff. Me so lazy.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntity_h
#define krbEntity_h

/*****************************************************************************
*****************************************************************************/

#include "..\KerberosUtility.h"

#include "Ogre3D\OgreSceneManager.h"
#include "Ogre3D\OgreSceneNode.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class Entity
{
public:
  Entity() {}
  virtual ~Entity() {}

  virtual void update() = 0;

  std::string getName()       { return strName; }
  Vector3 getPosition()       { return toKerberos(pNode->getPosition()); }
  Ogre::SceneNode* getNode()  { return pNode; }

protected:
  std::string         strName;
  Ogre::SceneManager* pSceneMgr;
  Ogre::SceneNode*    pNode;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbEntity_h

/***]EOF[*********************************************************************/