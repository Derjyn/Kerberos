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
* @file   krbSystemNetwork.cpp
* @author Nathan Harris
* @date   26 December 2014
* @brief  Network system
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemNetwork.h"

/*****************************************************************************
*****************************************************************************/

template<> Kerberos::SystemNetwork* Ogre::Singleton<Kerberos::SystemNetwork>::msSingleton = 0;

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

SystemNetwork::SystemNetwork(Config* config, Logger* log)
{
  str_Name  = "Network";
  m_Config  = config;
  m_Log     = log;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": 'Lemme at them fat pipes...");
}

SystemNetwork::~SystemNetwork()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": I'll leave my packets here then.");
}

SystemNetwork* SystemNetwork::getSingletonPtr(void)
{
    return msSingleton;
}
SystemNetwork& SystemNetwork::getSingleton(void)
{  
    return (*msSingleton);  
}

/*****************************************************************************
*****************************************************************************/

void SystemNetwork::init()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Initialized :)");
}

void SystemNetwork::cycle()
{
}

void SystemNetwork::halt()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Halted :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemNetwork::parseConfig()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/