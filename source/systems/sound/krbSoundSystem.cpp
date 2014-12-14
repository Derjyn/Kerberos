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
* @file   krbsoundSystem.cpp
* @author Nathan Harris
* @date   13 December 2014
* @brief  Did you hear something?
*/

/*****************************************************************************
*****************************************************************************/

#include "core\krbLogger.h"

#include "systems\sound\krbSoundSystem.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

SoundSystem::SoundSystem(Config* config, Logger* log, Timer* timer)
{
  setName("Sound system");

  pConfig = config;
  pLog    = log;
  pTimer  = timer;

  logCreation();
}

SoundSystem::~SoundSystem()
{
  logDestruction();
}

/*****************************************************************************
*****************************************************************************/

void SoundSystem::start()
{
  logStart();
}

void SoundSystem::cycle()
{
}

void SoundSystem::stop()
{
  logStop();
}

/*****************************************************************************
*****************************************************************************/

}       // namepsace Kerberos

/***]EOF[*********************************************************************/