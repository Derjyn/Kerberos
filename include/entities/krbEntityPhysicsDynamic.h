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
* @file   krbEntityPhysicsDynamic.h
* @author Nathan Harris
* @date   26 December 2014
* @brief  Dynamic physics entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntityPhysicsDynamic_h
#define krbEntityPhysicsDynamic_h

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntityPhysics.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief Dynamic physics entity
//
class EntityPhysicsDynamic : public EntityPhysics
{
public:
  EntityPhysicsDynamic(string name, string mesh,float mass,
    int maxAge, float createTime, Vector3 position);

  ~EntityPhysicsDynamic();
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbEntityPhysicsDynamic_h

/***]EOF[*********************************************************************/