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
* @file   krbAISystem.cpp
* @author Nathan Harris
* @date   13 December 2014
* @brief  The singularity nears!
*/

/*****************************************************************************
*****************************************************************************/

#include "core\krbLogger.h"

#include "systems\ai\krbAISystem.h"

#include <string>

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

AISystem::AISystem(Config* config, Logger* log, Timer* timer)
{
  setName("AI system");

  pConfig = config;
  pLog    = log;
  pTimer  = timer;

  logCreation();
}

AISystem::~AISystem()
{
  logDestruction();
}

/*****************************************************************************
*****************************************************************************/

void AISystem::start()
{
  logStart();
}

void AISystem::cycle()
{
}

void AISystem::stop()
{
  logStop();
}

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos

/***]EOF[*********************************************************************/