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
* @file   krbSystemScript.cpp
* @author Nathan Harris
* @date   26 December 2014
* @brief  Script system
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemScript.h"

/*****************************************************************************
*****************************************************************************/

template<> Kerberos::SystemScript* Ogre::Singleton<Kerberos::SystemScript>::msSingleton = 0;

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

SystemScript::SystemScript(Config* config, Logger* log)
{
  str_Name  = "Script";
  m_Config  = config;
  m_Log     = log;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Got anything that needs parsing?");
}

SystemScript::~SystemScript()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": I was getting bored anyhow...");
}

SystemScript* SystemScript::getSingletonPtr(void)
{
    return msSingleton;
}
SystemScript& SystemScript::getSingleton(void)
{  
    return (*msSingleton);  
}

/*****************************************************************************
*****************************************************************************/

void SystemScript::init()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Initialized :)");
}

void SystemScript::cycle()
{
}

void SystemScript::halt()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Halted :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemScript::parseConfig()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/