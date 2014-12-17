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
* @file   krbSystemPhysics.cpp
* @author Nathan Harris
* @date   17 December 2014
* @brief  Physics system
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemPhysics.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

SystemPhysics::SystemPhysics()
{
  m_strName = "Physics";
  cout << "System created: " << m_strName << endl;
}

SystemPhysics::~SystemPhysics()
{
  cout << "System destroyed: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

void SystemPhysics::init()
{
  cout << "System intialized: " << m_strName << endl;
}

void SystemPhysics::cycle()
{
  cout << m_strName << " system cycled." <<  endl;
}

void SystemPhysics::halt()
{
  cout << "System halted: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/