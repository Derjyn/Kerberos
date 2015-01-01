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
* @file   krbSystemGUI.cpp
* @author Nathan Harris
* @date   31 December 2014
* @brief  GUI system
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "systems/krbSystemGUI.h"
#include "systems/krbSystemRender.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

template<> Kerberos::SystemGUI* Ogre::Singleton<Kerberos::SystemGUI>::msSingleton = 0;

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

SystemGUI::SystemGUI(Config* config, Logger* log)
{
  str_Name  = "GUI";
  m_Config  = config;
  m_Log     = log;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Gorillas just came outta the mist :O");
}

SystemGUI::~SystemGUI()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Gorillas went back into the mist...");
}

SystemGUI* SystemGUI::getSingletonPtr(void)
{
    return msSingleton;
}
SystemGUI& SystemGUI::getSingleton(void)
{  
    return (*msSingleton);  
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void SystemGUI::init()
{
  m_Silverback = new Gorilla::Silverback();

  m_Viewport = SystemRender::getSingletonPtr()->getViewport();
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Got Ogre viewport");

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Initialized :)");
}

void SystemGUI::cycle()
{
}

void SystemGUI::halt()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Halted :)");
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void SystemGUI::parseConfig()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

UI_GUI* SystemGUI::createGUI(const string& name, bool visible)
{
  UI_GUI* _gui = new UI_GUI(name, visible, m_Viewport, m_Silverback);

  if (map_GUI[name] == nullptr) 
  {
    map_GUI[name] = _gui;
  }

  return _gui;
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

Gorilla::Silverback* SystemGUI::getSilverback()
{
  return m_Silverback;
}

UI_GUI* SystemGUI::getGUI(string name)
{
  if (map_GUI[name] != nullptr) 
  {
    return map_GUI[name];
  }

  return nullptr;
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

bool SystemGUI::keyPressed(const OIS::KeyEvent &e)
{
  return true;
}
  
bool SystemGUI::keyReleased(const OIS::KeyEvent &e)
{   
  return true;
}
  
bool SystemGUI::mouseMoved(const OIS::MouseEvent &arg)
{
  return true;
}
  
bool SystemGUI::mousePressed(
  const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
  return true;
}
  
bool SystemGUI::mouseReleased(
  const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
  return true;
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

}

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\
