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
* @date   01 January 2015
* @brief  The central nervous system of Kerberos
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "Kerberos.h"
#include "krbLab.h"

#include "Ogre3D/OgreWindowEventUtilities.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

Brain::Brain()
{
  m_Clock         = new Clock(false);

  m_SysAI         = nullptr;
  m_SysInput      = nullptr;
  m_SysNetwork    = nullptr;
  m_SysPhysics    = nullptr;
  m_SysRender     = nullptr;
  m_SysScript     = nullptr;
  m_SysSound      = nullptr;
  m_SysWorld      = nullptr;

  m_Lab           = nullptr;

  d_Accumulator   = 0.0;
  d_Counter       = 0.0;
  d_DeltaTime     = 0.0;
  d_LogicRate     = 0.0;
  d_CurrentTime   = 0.0;
  d_NewTime       = 0.0;
  d_TickCount     = 0.0;
}

Brain::~Brain()
{
  delete m_Lab;

  delete m_Log;
  delete m_Config;
  delete m_Clock;
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Brain::init()
{
  m_Config = new Config("./Kerberos.kcp");
  parseConfig();
  
  m_Log = new Logger(str_LogFile, 0, getVersionString());  

  addSystems();
  // PERHAPS DO THINGS BEFORE INITIALIZING SYSTEMS
  initSystems();

  m_Lab = new Lab(m_Config, m_Clock, m_Log);

  m_Clock->reset();
  m_SysWorld->resetClock();

  m_Lab->init();
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Brain::cycle()
{
  while (m_Lab->isAlive())
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
      m_SysScript->cycle();
      m_SysInput->cycle();      
      m_SysWorld->cycle();

      m_SysPhysics->cycle(
        d_LogicRate,
        m_SysWorld->getWorldRate(), 
        m_SysWorld->isPaused());

      m_SysAI->cycle();
      m_SysSound->cycle();
      m_SysGUI->cycle();
      m_SysNetwork->cycle();

      m_Lab->cycle(d_DeltaTime);

      d_Accumulator -= d_LogicRate;

      d_TickCount++;
    }

    m_SysRender->cycle(d_LogicRate);
  }
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Brain::halt()
{
  m_Lab->halt();

  haltSystems();
  // PERHAPS DO THINGS BEFORE DESTROYING SYSTEMS 
  destroySystems();

  // LOG SOME STATISTICS
  m_Log->logSection("STATISTICS");
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
    ("Brain time: " + m_Clock->msexString()));
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
    ("World time: " + m_SysWorld->getTimeString()));
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
    ("Logic ticks: " + toString(d_TickCount)));
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
    ("Logic RPS: " + toString(d_TickCount / (m_Clock->msex() / 1000.0))));

  m_Log->closeLog();
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Brain::parseConfig()
{
  str_LogFile = m_Config->getString("BRAIN", "LogFile");
  d_LogicRate = 1000.0 / m_Config->getFloat("BRAIN", "LogicRate");
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Brain::addSystems()
{
  m_Log->logSection("SYSTEMS PRIME");

  // ADD SCRIPT SYSTEM
  m_SysScript = new SystemScript(m_Config, m_Log);
  vec_Sys.push_back(m_SysScript);
  map_Sys[m_SysScript->getName()] = m_SysScript;

  // ADD RENDER SYSTEM
  m_SysRender = new SystemRender(m_Config, m_Log);
  vec_Sys.push_back(m_SysRender);
  map_Sys[m_SysRender->getName()] = m_SysRender;

  // ADD INPUT SYSTEM
  m_SysInput = new SystemInput(m_Config, m_Log);
  vec_Sys.push_back(m_SysInput);
  map_Sys[m_SysInput->getName()] = m_SysInput;

  // ADD PHYSICS SYSTEM
  m_SysPhysics = new SystemPhysics(m_Config, m_Log);
  vec_Sys.push_back(m_SysPhysics);
  map_Sys[m_SysPhysics->getName()] = m_SysPhysics;

  // ADD WORLD SYSTEM
  m_SysWorld = new SystemWorld(m_Config, m_Log);
  vec_Sys.push_back(m_SysWorld);
  map_Sys[m_SysWorld->getName()] = m_SysWorld;

  // ADD SOUND SYSTEM
  m_SysSound = new SystemSound(m_Config, m_Log);
  vec_Sys.push_back(m_SysSound);
  map_Sys[m_SysSound->getName()] = m_SysSound;

  // ADD GUI SYSTEM
  m_SysGUI = new SystemGUI(m_Config, m_Log);
  vec_Sys.push_back(m_SysGUI);
  map_Sys[m_SysGUI->getName()] = m_SysGUI;

  // ADD AI SYSTEM
  m_SysAI = new SystemAI(m_Config, m_Log);
  vec_Sys.push_back(m_SysAI);
  map_Sys[m_SysAI->getName()] = m_SysAI;

  // ADD NETWORK SYSTEM
  m_SysNetwork = new SystemNetwork(m_Config, m_Log);
  vec_Sys.push_back(m_SysNetwork);
  map_Sys[m_SysNetwork->getName()] = m_SysNetwork;

  vector<System*>::iterator vec_SysIT = vec_Sys.begin();
  for(; vec_SysIT != vec_Sys.end(); ++vec_SysIT)
  {
    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      "Touching system: " + (*vec_SysIT)->getName());
  }
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Brain::initSystems()
{
  m_Log->logSection("SYSTEMS INIT");

  // INIT SCRIPT SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysScript->getName()));
  m_SysScript->init();

  // INIT RENDER SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysRender->getName()));
  m_SysRender->init();

  // INIT INPUT SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysInput->getName()));
  m_SysInput->init();

  // INIT PHYSICS SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysPhysics->getName()));
  m_SysPhysics->init();

  // INIT WORLD SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysWorld->getName()));
  m_SysWorld->init();

  // INIT SOUND SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysSound->getName()));
  m_SysSound->init();

  // INIT GUI SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysGUI->getName()));
  m_SysGUI->init();

  // INIT AI SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysAI->getName()));
  m_SysAI->init();

  // INIT NETWORK SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysNetwork->getName()));
  m_SysNetwork->init();
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Brain::haltSystems()
{
  m_Log->logSection("SYSTEMS HALT");

  vector<System*>::reverse_iterator rit = vec_Sys.rbegin();
  for(; rit != vec_Sys.rend(); ++rit)
  {
    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Halting system: " + (*rit)->getName()));

    (*rit)->halt();
  }
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Brain::destroySystems()
{
  m_Log->logSection("SYSTEMS DESTROY");

  vector<System*>::reverse_iterator rit = vec_Sys.rbegin();
  for(; rit != vec_Sys.rend(); ++rit)
  {
    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Destroying system: " + (*rit)->getName()));

    delete (*rit);
  }
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

}

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\