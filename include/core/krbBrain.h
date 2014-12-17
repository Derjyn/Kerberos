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

#include <map>
#include <vector>
using namespace std;

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
  ~Brain();

  void init();
  void cycle();
  void halt();

  string          getVersion()    { return str_Version; }
  Clock*          getClock()      { return m_Clock; }
  Config*         getConfig()     { return m_Config; }
  Logger*         getLogger()     { return m_Log; }

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
  Logger*         m_Log;

  SystemAI*       m_sysAI;
  SystemInput*    m_sysInput;
  SystemNetwork*  m_sysNetwork;
  SystemPhysics*  m_sysPhysics;
  SystemRender*   m_sysRender;
  SystemScript*   m_sysScript;
  SystemSound*    m_sysSound;
  SystemWorld*    m_sysWorld;

  bool            b_Alive;
  string          str_Version;
  string          str_LogFile;
  float           f_DemoTime;

private:
  void parseConfig();

  void addSystems();
  void initSystems();
  void haltSystems();
  void destroySystems();

  // TIMER JUNK
  double          d_Accumulator;
  double          d_Counter;
  double          d_DeltaTime;
  double          d_LogicRate;
  double          d_CurrentTime;
  double          d_NewTime;
  double          d_TickCount;

  vector<System*>       vec_Sys;
  map<string, System*>  map_Sys;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbBrain_h

/***]EOF[*********************************************************************/