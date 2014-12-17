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
* @file   krbSystemWorld.h
* @author Nathan Harris
* @date   17 December 2014
* @brief  World system
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbSystemWorld_h
#define krbSystemWorld_h

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystem.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

class SystemWorld final : public System
{
public:
  SystemWorld();
  ~SystemWorld();

  void init();
  void cycle();
  void halt();
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbSystemWorld_h

/***]EOF[*********************************************************************/