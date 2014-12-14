/*******************************************************************************
*                                                                              *
* Copyright (C) 2014 Nathan Harris                                             *
*                                                                              *
* This file is part of Kerberos.                                               *
*                                                                              *
*   Kerberos is free software. Enjoy it, modify it, contribute to it.          *
*   For sales inqueries, see <http://www.omglasergunspewpewpew.com/>           *
*                                                                              *
*******************************************************************************/

/**
* @file   krbInputSystem.cpp
* @author Nathan Harris
* @date   13 December 2014
* @brief  Takes care of input stuff.
*/

/*****************************************************************************
*****************************************************************************/

#include "core\krbLogger.h"

#include "systems\input\krbInputSystem.h"

#include "Ogre3D\OgreRenderWindow.h"
#include "Ogre3D\OgreStringConverter.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

InputSystem::InputSystem(Config* config, Logger* log, Timer* timer, 
  Ogre::RenderWindow* win)
{
  setName("Input system");

  pConfig = config;
  pLog    = log;
  pTimer  = timer;
  pWindow = win;

  logCreation();
}

InputSystem::~InputSystem()
{
  logDestruction();
}

/*****************************************************************************
*****************************************************************************/

void InputSystem::start()
{
  pWindow->getCustomAttribute("WINDOW", &hWnd);

  OIS::ParamList pl;
  pl.insert(OIS::ParamList::value_type(
    "WINDOW", Ogre::StringConverter::toString(hWnd)));

  pInputMgr = OIS::InputManager::createInputSystem(pl);

  pKeyboard = static_cast<OIS::Keyboard*>(
    pInputMgr->createInputObject(OIS::OISKeyboard, true));
  pKeyboard->setEventCallback(this);

  pMouse = static_cast<OIS::Mouse*>(
    pInputMgr->createInputObject(OIS::OISMouse, true));
  pMouse->setEventCallback(this);

  setWindowExtents(pWindow->getWidth(), pWindow->getHeight());

  logStart();
}

/*****************************************************************************
*****************************************************************************/

void InputSystem::cycle()
{
  pMouse->capture();
  pKeyboard->capture();
}

/*****************************************************************************
*****************************************************************************/

void InputSystem::stop()
{
  if (pMouse)
  {
    pInputMgr->destroyInputObject(pMouse);
  }
  if (pKeyboard)
  {
    pInputMgr->destroyInputObject(pKeyboard);
  }

  OIS::InputManager::destroyInputSystem(pInputMgr);

  logStop();
}

/*****************************************************************************
*****************************************************************************/

void InputSystem::setWindowExtents(int width, int height)
{
  const OIS::MouseState& ms = pMouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

/*****************************************************************************
*****************************************************************************/

bool InputSystem::keyDown(const OIS::KeyCode& keycode)
{
  return pKeyboard->isKeyDown(keycode);
}

bool InputSystem::modDown(const OIS::Keyboard::Modifier& mod)
{
  return pKeyboard->isModifierDown(mod);
}

/*****************************************************************************
*****************************************************************************/

OIS::Keyboard* InputSystem::getKeyboard()
{
  return pKeyboard;
}
OIS::Mouse* InputSystem::getMouse()
{
  return pMouse;
}

/*****************************************************************************
*****************************************************************************/

bool InputSystem::mouseMoved(const OIS::MouseEvent& evt)
{
  return true;
}
bool InputSystem::mousePressed(
  const OIS::MouseEvent& evt, OIS::MouseButtonID btn)
{
  return true;
}
bool InputSystem::mouseReleased(
  const OIS::MouseEvent& evt, OIS::MouseButtonID btn)
{
  return true;
}

/*****************************************************************************
*****************************************************************************/

bool InputSystem::keyPressed(const OIS::KeyEvent& evt)
{
  return true;
}
bool InputSystem::keyReleased(const OIS::KeyEvent& evt)
{
  return true;
}

/*****************************************************************************
*****************************************************************************/

}       // namepsace Kerberos

/***]EOF[*********************************************************************/