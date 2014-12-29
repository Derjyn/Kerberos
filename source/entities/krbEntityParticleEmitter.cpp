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
* @file   krbEntityParticleEmitter.cpp
* @author Nathan Harris
* @date   26 December 2014
* @brief  Particle emitter entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntityParticleEmitter.h"

#include "ParticleUniverse/ParticleUniverseSystem.h"
#include "ParticleUniverse/ParticleUniverseSystemManager.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

EntityParticleEmitter::EntityParticleEmitter(string name, Ogre::SceneManager* scenemgr)
{
  str_Name    = name;
  m_SceneMgr  = scenemgr;
  m_WorldNode = m_SceneMgr->getRootSceneNode();
  m_PUSysMgr  = ParticleUniverse::ParticleSystemManager::getSingletonPtr();

  // SET UP PARTICLE SYSTEM
  m_PUSystem = m_PUSysMgr->createParticleSystem(name, name, m_SceneMgr);
  m_WorldNode->createChildSceneNode("NODE_" + name);
  m_SceneMgr->getSceneNode("NODE_" + name)->attachObject(m_PUSystem);

  m_PUSystem->prepare();
}

EntityParticleEmitter::~EntityParticleEmitter()
{
}

/*****************************************************************************
*****************************************************************************/

void EntityParticleEmitter::start()
{
  m_PUSystem->start();
}

void EntityParticleEmitter::stop()
{
  m_PUSystem->stop();
}

void EntityParticleEmitter::togglePause()
{
 if (m_PUSystem->getState() != ParticleUniverse::ParticleSystem::PSS_PAUSED)
  {
    m_PUSystem->pause();
  }
  else if (m_PUSystem->getState() == ParticleUniverse::ParticleSystem::PSS_PAUSED)
  {
    m_PUSystem->resume();
  }
}

void EntityParticleEmitter::setTimeScale(float scale)
{
  m_PUSystem->setScaleTime(scale);
}

/*****************************************************************************
*****************************************************************************/

ParticleUniverse::ParticleSystem* EntityParticleEmitter::getPUSystem()
{
  return m_PUSystem;
}

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos

/***]EOF[*********************************************************************/