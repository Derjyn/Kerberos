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
* @file   krbSystemScript.h
* @author Nathan Harris
* @date   26 December 2014
* @brief  Script system
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbSystemScript_h
#define krbSystemScript_h

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystem.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief Script system (currently empty)
//
class SystemScript final : 
  public System, 
  public Ogre::Singleton<SystemScript>
{
public:
  SystemScript(Config* config, Logger* log);
  ~SystemScript();

  static SystemScript& getSingleton();
  static SystemScript* getSingletonPtr();

  void init();
  void cycle();
  void halt();

private:
  void parseConfig();
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbSystemScript_h

/***]EOF[*********************************************************************/