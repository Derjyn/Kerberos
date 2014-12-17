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
* @file   krbSystemNetwork.cpp
* @author Nathan Harris
* @date   17 December 2014
* @brief  Network system
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemNetwork.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

SystemNetwork::SystemNetwork()
{
  m_strName = "Network";
  cout << "System created: " << m_strName << endl;
}

SystemNetwork::~SystemNetwork()
{
  cout << "System destroyed: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

void SystemNetwork::init()
{
  cout << "System initialized: " << m_strName << endl;
}

void SystemNetwork::cycle()
{
  cout << m_strName << " system cycled." <<  endl;
}

void SystemNetwork::halt()
{
  cout << "System halted: " << m_strName << endl;
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/