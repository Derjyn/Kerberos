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
* @file   krbBrain.cpp
* @author Nathan Harris
* @date   17 December 2014
* @brief  The central nervous system of Kerberos
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "core/krbBrain.h"
#include "core/krbClock.h"
#include "core/krbConfig.h"
#include "core/krbLogger.h"

#include "systems/krbSystemAI.h"
#include "systems/krbSystemInput.h"
#include "systems/krbSystemNetwork.h"
#include "systems/krbSystemPhysics.h"
#include "systems/krbSystemRender.h"
#include "systems/krbSystemScript.h"
#include "systems/krbSystemSound.h"
#include "systems/krbSystemWorld.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

Brain::Brain()
{
  m_sysAI       = nullptr;
  m_sysInput    = nullptr;
  m_sysNetwork  = nullptr;
  m_sysPhysics  = nullptr;
  m_sysRender   = nullptr;
  m_sysScript   = nullptr;
  m_sysSound    = nullptr;
  m_sysWorld    = nullptr;
}

/*****************************************************************************
*****************************************************************************/

void Brain::init()
{
  addSystems();
  // PERHAPS DO THINGS BEFORE INITIALIZING SYSTEMS
  initSystems();
}

/*****************************************************************************
*****************************************************************************/

void Brain::cycle()
{
  cycleSystems();
}

/*****************************************************************************
*****************************************************************************/

void Brain::halt()
{
  haltSystems();
  // PERHAPS DO THINGS BEFORE DESTROYING SYSTEMS
  destroySystems();
}

/*****************************************************************************
*****************************************************************************/

// ADD SYSTEMS TO MAP FOR REFERENCE & VECTOR FOR ACTION
void Brain::addSystems()
{
  m_sysScript   = new SystemScript(); 
  m_sysRender   = new SystemRender();
  m_sysInput    = new SystemInput();
  m_sysWorld    = new SystemWorld();
  m_sysPhysics  = new SystemPhysics();
  m_sysSound    = new SystemSound();
  m_sysAI       = new SystemAI();
  m_sysNetwork  = new SystemNetwork();

  vec_Sys.push_back(m_sysScript);
  vec_Sys.push_back(m_sysRender);
  vec_Sys.push_back(m_sysInput);
  vec_Sys.push_back(m_sysWorld);
  vec_Sys.push_back(m_sysPhysics);
  vec_Sys.push_back(m_sysSound);
  vec_Sys.push_back(m_sysAI);
  vec_Sys.push_back(m_sysNetwork);
  cout << "vec_Systems size: " << vec_Sys.size() << endl;

  map_Sys[m_sysScript->getName()]   = m_sysScript;
  map_Sys[m_sysRender->getName()]   = m_sysRender;
  map_Sys[m_sysInput->getName()]    = m_sysInput;
  map_Sys[m_sysWorld->getName()]    = m_sysWorld;
  map_Sys[m_sysPhysics->getName()]  = m_sysPhysics;
  map_Sys[m_sysSound->getName()]    = m_sysSound;
  map_Sys[m_sysAI->getName()]       = m_sysAI;
  map_Sys[m_sysNetwork->getName()]  = m_sysNetwork;
  cout << "map_Systems size: " << map_Sys.size() << endl;
}

/*****************************************************************************
*****************************************************************************/

void Brain::initSystems()
{
  vector<System*>::iterator vec_SysIT = vec_Sys.begin();
  for (; vec_SysIT != vec_Sys.end(); ++vec_SysIT)
  {
    cout << "Initializing system: " << (*vec_SysIT)->getName() << endl;
    (*vec_SysIT)->init();
  }
}

/*****************************************************************************
*****************************************************************************/

void Brain::cycleSystems()
{
  vector<System*>::iterator vec_SysIT = vec_Sys.begin();
  for (; vec_SysIT != vec_Sys.end(); ++vec_SysIT)
  {
    (*vec_SysIT)->cycle();
  }
}

/*****************************************************************************
*****************************************************************************/

void Brain::haltSystems()
{
  vector<System*>::reverse_iterator rit = vec_Sys.rbegin();
  for (; rit != vec_Sys.rend(); ++rit)
  {
    cout << "Halting system: " << (*rit)->getName() << endl;
    (*rit)->halt();
  }
}

/*****************************************************************************
*****************************************************************************/

void Brain::destroySystems()
{
  vector<System*>::reverse_iterator rit = vec_Sys.rbegin();
  for (; rit != vec_Sys.rend(); ++rit)
  {
    cout << "Destroying system: " << (*rit)->getName() << endl;
    delete (*rit);
  }
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/