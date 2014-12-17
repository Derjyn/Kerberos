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
* @file   krbSystemRender.cpp
* @author Nathan Harris
* @date   17 December 2014
* @brief  Rendering system
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemRender.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

SystemRender::SystemRender()
{
  m_strName = "Render";
  cout << "System created: " << m_strName << endl;
}

SystemRender::~SystemRender()
{
  cout << "System destroyed: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

void SystemRender::init()
{
  cout << "System intialized: " << m_strName << endl;
}

void SystemRender::cycle()
{
  cout << m_strName << " system cycled." <<  endl;
}

void SystemRender::halt()
{
  cout << "System halted: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/