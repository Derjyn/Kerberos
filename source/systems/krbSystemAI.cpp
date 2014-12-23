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
* @file   krbSystemAI.cpp
* @author Nathan Harris
* @date   17 December 2014
* @brief  AI system
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemAI.h"
#include "core/krbConfig.h"
#include "core/krbClock.h"
#include "core/krbLogger.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

SystemAI::SystemAI(Config* config, Logger* log)
{
  str_Name  = "AI";
  m_Config  = config;
  m_Log     = log;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": 010010000110100100100001");
}

SystemAI::~SystemAI()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Almost got all your bases :/");
}

/*****************************************************************************
*****************************************************************************/

void SystemAI::init()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Initialized :)");
}

void SystemAI::cycle()
{
}

void SystemAI::halt()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Halted :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemAI::parseConfig()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/