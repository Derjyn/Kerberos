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
* @file   krbSystemAI.h
* @author Nathan Harris
* @date   31 December 2014
* @brief  AI system
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbSystemAI_h
#define krbSystemAI_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "systems/krbSystem.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

//
//! \brief AI system (currently empty)
//
class SystemAI final : 
  public System, 
  public Ogre::Singleton<SystemAI>
{
public:
  SystemAI(Config* config, Logger* log);
  ~SystemAI();

  static SystemAI& getSingleton();
  static SystemAI* getSingletonPtr();

  void init();
  void cycle();
  void halt();

private:
  void parseConfig();
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbSystemAI_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\