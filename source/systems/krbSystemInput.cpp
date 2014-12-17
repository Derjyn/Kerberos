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
* @file   krbSystemInput.cpp
* @author Nathan Harris
* @date   17 December 2014
* @brief  Input system
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemInput.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

SystemInput::SystemInput()
{
  m_strName = "Input";
  cout << "System created: " << m_strName << endl;
}

SystemInput::~SystemInput()
{
  cout << "System destroyed: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

void SystemInput::init()
{
  cout << "System initialized: " << m_strName << endl;
}

void SystemInput::cycle()
{
  cout << m_strName << " system cycled." <<  endl;
}

void SystemInput::halt()
{
  cout << "System halted: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/