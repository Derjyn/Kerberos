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

#include "Kerberos.h"

#include "Ogre3D\OgreWindowEventUtilities.h"

#include <iostream>
#include <sstream>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

Brain::Brain()
{
  stringstream ss_ver;
  ss_ver << 
  KRB_VERSION_MAJOR << "." <<
  KRB_VERSION_MINOR << "." <<
  KRB_VERSION_PATCH << "." <<
  KRB_VERSION_ALPHA << " (" << KRB_VERSION_NAME ")";
  str_Version = ss_ver.str();

  m_Clock       = new Clock(false);

  m_sysAI       = nullptr;
  m_sysInput    = nullptr;
  m_sysNetwork  = nullptr;
  m_sysPhysics  = nullptr;
  m_sysRender   = nullptr;
  m_sysScript   = nullptr;
  m_sysSound    = nullptr;
  m_sysWorld    = nullptr;

  b_Alive       = false;
  d_Accumulator = 0.0;
  d_Counter     = 0.0;
  d_DeltaTime   = 0.0;
  d_LogicRate   = 0.0;
  d_CurrentTime = 0.0;
  d_NewTime     = 0.0;
  d_TickCount   = 0.0;
}

Brain::~Brain()
{
  b_Alive = false;

  delete m_Log;
  delete m_Config;
  delete m_Clock;
}

/*****************************************************************************
*****************************************************************************/

void Brain::init()
{
  m_Config = new Config("./Kerberos.kpf");
  parseConfig();

  m_Log = new Logger(str_LogFile, 0, str_Version);  

  b_Alive = true;

  addSystems();

  // PERHAPS DO THINGS BEFORE INITIALIZING SYSTEMS

  initSystems();
}

/*****************************************************************************
*****************************************************************************/

void Brain::cycle()
{
  m_Clock->reset();
  m_Clock->resetClock();

  while (b_Alive)
  {
    Ogre::WindowEventUtilities::messagePump();

    d_NewTime = m_Clock->msex();
    d_DeltaTime = d_NewTime - d_CurrentTime;

    if (d_DeltaTime <= 0.0)
    {
      continue;
    }

    d_CurrentTime = d_NewTime;
    d_Accumulator += d_DeltaTime;

    while (d_Accumulator >= d_LogicRate)
    {
      m_Clock->tick(1.0);

      m_sysScript->cycle();
      m_sysInput->cycle();
      m_sysPhysics->cycle();
      m_sysSound->cycle();
      m_sysAI->cycle();
      m_sysWorld->cycle();
      m_sysNetwork->cycle();

      if (m_Clock->Hand.second >= f_DemoTime)
      {
        b_Alive = false;
      }

      d_Counter += d_LogicRate;
      d_Accumulator -= d_LogicRate;      

      d_TickCount++;
    }

    m_sysRender->cycle();
  }
}

/*****************************************************************************
*****************************************************************************/

void Brain::halt()
{
  haltSystems();

  // PERHAPS DO THINGS BEFORE DESTROYING SYSTEMS 

  destroySystems();

  // LOG SOME STATISTICS
  m_Log->logSection("STATISTICS");
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
    ("Brain time: " + m_Clock->msexString()));
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
    ("Clock time: " + m_Clock->clockString()));
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
    ("Logic ticks: " + toString(d_TickCount)));
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
    ("Logic RPS: " + toString(d_TickCount / (m_Clock->msex() / 1000.0))));

  m_Log->closeLog();
}

/*****************************************************************************
*****************************************************************************/

void Brain::parseConfig()
{
  str_LogFile   = m_Config->getString("BRAIN", "LogFile");
  d_LogicRate   = 1000.0 / m_Config->getDouble("BRAIN", "LogicRate");

  f_DemoTime    = m_Config->getFloat("DEMO", "TimeLimit");
}

/*****************************************************************************
*****************************************************************************/

void Brain::addSystems()
{
  m_Log->logSection("SYSTEMS PRIME");

  // CREATE AND ADD SYSTEMS TO VECTOR FOR ACTION
  m_sysScript = new SystemScript(m_Config, m_Log);
  vec_Sys.push_back(m_sysScript);

  m_sysRender = new SystemRender(m_Config, m_Log);
  vec_Sys.push_back(m_sysRender);

  m_sysInput = new SystemInput(m_Config, m_Log);
  vec_Sys.push_back(m_sysInput);

  m_sysWorld = new SystemWorld(m_Config, m_Log);
  vec_Sys.push_back(m_sysWorld);

  m_sysPhysics = new SystemPhysics(m_Config, m_Log);
  vec_Sys.push_back(m_sysPhysics);

  m_sysSound = new SystemSound(m_Config, m_Log);
  vec_Sys.push_back(m_sysSound);

  m_sysAI = new SystemAI(m_Config, m_Log);
  vec_Sys.push_back(m_sysAI);

  m_sysNetwork = new SystemNetwork(m_Config, m_Log);
  vec_Sys.push_back(m_sysNetwork);

  vector<System*>::iterator vec_SysIT = vec_Sys.begin();
  for (; vec_SysIT != vec_Sys.end(); ++vec_SysIT)
  {
    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Touching system: " + (*vec_SysIT)->getName()));
  }

  // ADD EM TO MAP FOR REFERENCE
  map_Sys[m_sysScript->getName()]   = m_sysScript;
  map_Sys[m_sysRender->getName()]   = m_sysRender;
  map_Sys[m_sysInput->getName()]    = m_sysInput;
  map_Sys[m_sysWorld->getName()]    = m_sysWorld;
  map_Sys[m_sysPhysics->getName()]  = m_sysPhysics;
  map_Sys[m_sysSound->getName()]    = m_sysSound;
  map_Sys[m_sysAI->getName()]       = m_sysAI;
  map_Sys[m_sysNetwork->getName()]  = m_sysNetwork;
}

/*****************************************************************************
*****************************************************************************/

void Brain::initSystems()
{
  m_Log->logSection("SYSTEMS INIT");

  vector<System*>::iterator vec_SysIT = vec_Sys.begin();
  for (; vec_SysIT != vec_Sys.end(); ++vec_SysIT)
  {
    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + (*vec_SysIT)->getName()));

    (*vec_SysIT)->init();
  }
}

/*****************************************************************************
*****************************************************************************/

void Brain::haltSystems()
{
  m_Log->logSection("SYSTEMS HALT");

  vector<System*>::reverse_iterator rit = vec_Sys.rbegin();
  for (; rit != vec_Sys.rend(); ++rit)
  {
    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Halting system: " + (*rit)->getName()));

    (*rit)->halt();
  }
}

/*****************************************************************************
*****************************************************************************/

void Brain::destroySystems()
{
  m_Log->logSection("SYSTEMS DESTROY");

  vector<System*>::reverse_iterator rit = vec_Sys.rbegin();
  for (; rit != vec_Sys.rend(); ++rit)
  {
    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Destroying system: " + (*rit)->getName()));

    delete (*rit);
  }
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/