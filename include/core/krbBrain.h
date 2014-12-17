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
* @file   krbBrain.h
* @author Nathan Harris
* @date   17 December 2014
*
* @details 
*  Brain is the central core of Kerberos responsible for overseeing all the 
*  systems that build up the engine. The main loop, timing, and general
*  wizardry is handled by Brain.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbBrain_h
#define krbBrain_h

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystem.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

class Clock;
class Config;
class Logger;

class SystemAI;
class SystemInput;
class SystemNetwork;
class SystemPhysics;
class SystemRender;
class SystemScript;
class SystemSound;
class SystemWorld;

/*****************************************************************************
*****************************************************************************/

//
//! \brief The central nervous system of Kerberos
//
class Brain
{
public:
  Brain();

  void init();
  void cycle();
  void halt();

  Clock* getClock()     { return m_Clock; }
  Config* getConfig()   { return m_Config; }
  Logger* getLogger()   { return m_Logger; }

  SystemAI*       getSysAI()      { return m_sysAI; }
  SystemInput*    getSysInput()   { return m_sysInput; }
  SystemNetwork*  getSysNetwork() { return m_sysNetwork; }
  SystemPhysics*  getSysPhysics() { return m_sysPhysics; }
  SystemRender*   getSysRender()  { return m_sysRender; }
  SystemScript*   getSysScript()  { return m_sysScript; }
  SystemSound*    getSysSound()   { return m_sysSound; }

protected:
  Clock*          m_Clock;
  Config*         m_Config;
  Logger*         m_Logger;

  SystemAI*       m_sysAI;
  SystemInput*    m_sysInput;
  SystemNetwork*  m_sysNetwork;
  SystemPhysics*  m_sysPhysics;
  SystemRender*   m_sysRender;
  SystemScript*   m_sysScript;
  SystemSound*    m_sysSound;
  SystemWorld*    m_sysWorld;

private:
  void addSystems();
  void initSystems();
  void cycleSystems();
  void haltSystems();
  void destroySystems();

  vector<System*> vec_Sys;
  map<string, System*> map_Sys;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbBrain_h

/***]EOF[*********************************************************************/