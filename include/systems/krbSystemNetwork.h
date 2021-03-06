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
* @file   krbSystemNetwork.h
* @author Nathan Harris
* @date   31 December 2014
* @brief  Network system
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbSystemNetwork_h
#define krbSystemNetwork_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "systems/krbSystem.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

//
//! \brief Network system (currently empty)
//
class SystemNetwork final : 
  public System, 
  public Ogre::Singleton<SystemNetwork>
{
public:
  SystemNetwork(Config* config, Logger* log);
  ~SystemNetwork();

  static SystemNetwork& getSingleton();
  static SystemNetwork* getSingletonPtr();

  void init();
  void cycle();
  void halt();

private:
  void parseConfig();
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbSystemNetwork_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\