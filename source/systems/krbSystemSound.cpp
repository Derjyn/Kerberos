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
* @file   krbSystemSound.cpp
* @author Nathan Harris
* @date   17 December 2014
* @brief  Sound system
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemSound.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

SystemSound::SystemSound()
{
  m_strName = "Sound";
  cout << "System created: " << m_strName << endl;
}

SystemSound::~SystemSound()
{
  cout << "System destroyed: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

void SystemSound::init()
{
  cout << "System initialized: " << m_strName << endl;
}

void SystemSound::cycle()
{
  cout << m_strName << " system cycled." <<  endl;
}

void SystemSound::halt()
{
  cout << "System halted: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/