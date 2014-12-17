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
* @file   krbSystemWorld.cpp
* @author Nathan Harris
* @date   17 December 2014
* @brief  World system
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemWorld.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

SystemWorld::SystemWorld()
{
  m_strName = "World";
  cout << "System created: " << m_strName << endl;
}

SystemWorld::~SystemWorld()
{
  cout << "System destroyed: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

void SystemWorld::init()
{
  cout << "System initialized: " << m_strName << endl;
}

void SystemWorld::cycle()
{
  cout << m_strName << " system cycled." <<  endl;
}

void SystemWorld::halt()
{
  cout << "System halted: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/