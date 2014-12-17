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
* @file   krbSystemScript.cpp
* @author Nathan Harris
* @date   17 December 2014
* @brief  Script system
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemScript.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

SystemScript::SystemScript()
{
  m_strName = "Script";
  cout << "System created: " << m_strName << endl;
}

SystemScript::~SystemScript()
{
  cout << "System destroyed: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

void SystemScript::init()
{
  cout << "System initialized: " << m_strName << endl;
}

void SystemScript::cycle()
{
  cout << m_strName << " system cycled." <<  endl;
}

void SystemScript::halt()
{
  cout << "System halted: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/