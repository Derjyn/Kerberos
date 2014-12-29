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
* @date   26 December 2014
* @brief  Input system
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemInput.h"
#include "systems/krbSystemRender.h"

#include "Ogre3D/OgreRenderWindow.h"
#include "Ogre3D/OgreStringConverter.h"

/*****************************************************************************
*****************************************************************************/

template<> Kerberos::SystemInput* Ogre::Singleton<Kerberos::SystemInput>::msSingleton = 0;

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

SystemInput::SystemInput(Config* config, Logger* log)
{
  str_Name  = "Input";
  m_Config  = config;
  m_Log     = log;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Awaiting your input.");
}

SystemInput::~SystemInput()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": No keyloggers here. Move along.");
}

SystemInput* SystemInput::getSingletonPtr(void)
{
    return msSingleton;
}
SystemInput& SystemInput::getSingleton(void)
{  
    return (*msSingleton);  
}

/*****************************************************************************
*****************************************************************************/

void SystemInput::init()
{
  m_Window = SystemRender::getSingletonPtr()->getWindow();
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Ogre Ogre window");

  m_Window->getCustomAttribute("WINDOW", &hWnd);

  OIS::ParamList pl;
  pl.insert(OIS::ParamList::value_type(
    "WINDOW", Ogre::StringConverter::toString(hWnd)));
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Got window handle");

  m_InputMgr = OIS::InputManager::createInputSystem(pl);
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": OIS input manager created");

  m_Keyboard = static_cast<OIS::Keyboard*>(
    m_InputMgr->createInputObject(OIS::OISKeyboard, true));
  m_Keyboard->setEventCallback(this);
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Keyboard created");

  m_Mouse = static_cast<OIS::Mouse*>(
    m_InputMgr->createInputObject(OIS::OISMouse, true));
  m_Mouse->setEventCallback(this);
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Mouse created");

  setWindowExtents(m_Window->getWidth(), m_Window->getHeight());
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Set window extents");

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Initialized :)");
}

void SystemInput::cycle()
{
  m_Mouse->capture();
  m_Keyboard->capture();
}

void SystemInput::halt()
{
  if (m_Mouse)
  {
    m_InputMgr->destroyInputObject(m_Mouse);

    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
      str_Name + ": Mouse removed");
  }

  if (m_Keyboard)
  {
    m_InputMgr->destroyInputObject(m_Keyboard);

    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
      str_Name + ": Keyboard removed");
  }

  OIS::InputManager::destroyInputSystem(m_InputMgr);
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": OIS input manager removed");

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Halted :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemInput::parseConfig()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

/*****************************************************************************
*****************************************************************************/

void SystemInput::setWindowExtents(int width, int height)
{
  const OIS::MouseState& ms = m_Mouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

/*****************************************************************************
*****************************************************************************/

bool SystemInput::keyDown(const OIS::KeyCode& keycode)
{
  return m_Keyboard->isKeyDown(keycode);
}

bool SystemInput::modDown(const OIS::Keyboard::Modifier& mod)
{
  return m_Keyboard->isModifierDown(mod);
}

/*****************************************************************************
*****************************************************************************/

OIS::Keyboard* SystemInput::getKeyboard()
{
  return m_Keyboard;
}
OIS::Mouse* SystemInput::getMouse()
{
  return m_Mouse;
}

/*****************************************************************************
*****************************************************************************/

bool SystemInput::mouseMoved(const OIS::MouseEvent& evt)
{
  return true;
}
bool SystemInput::mousePressed(
  const OIS::MouseEvent& evt, OIS::MouseButtonID btn)
{
  return true;
}
bool SystemInput::mouseReleased(
  const OIS::MouseEvent& evt, OIS::MouseButtonID btn)
{
  return true;
}

/*****************************************************************************
*****************************************************************************/

bool SystemInput::keyPressed(const OIS::KeyEvent& evt)
{
  return true;
}
bool SystemInput::keyReleased(const OIS::KeyEvent& evt)
{
  return true;
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/