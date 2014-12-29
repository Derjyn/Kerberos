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
* @date   28 December 2014
* @brief  GUI system
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemGUI.h"
#include "systems/krbSystemRender.h"

/*****************************************************************************
*****************************************************************************/

template<> Kerberos::SystemGUI* Ogre::Singleton<Kerberos::SystemGUI>::msSingleton = 0;

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

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

/*****************************************************************************
*****************************************************************************/

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

/*****************************************************************************
*****************************************************************************/

void SystemGUI::parseConfig()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

/*****************************************************************************
*****************************************************************************/

UI_GUI* SystemGUI::createGUI(string name, bool visible)
{
  UI_GUI* gui = new UI_GUI(name, visible, m_Viewport, m_Silverback);
  if (map_GUI[name] == nullptr) 
  {
    map_GUI[name] = gui;
  }

  return gui;
}

/*****************************************************************************
*****************************************************************************/

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

/*****************************************************************************
*****************************************************************************/

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

/*****************************************************************************
*****************************************************************************/

//Menu::Menu(string name, string atlas, string bgImage, Vector2 dimensions, 
//  GUI* gui, Ogre::Viewport* viewport)
//{
//  str_Name = name;
//
//  if (!gui)
//  {
//    return;
//  }
//
//  m_Screen = gui->createScreen("GUI_SCREEN_MENU_" + name, atlas, viewport);
//  m_Layer = gui->createLayer("GUI_LAYER_MENU_" + name, m_Screen);
//	
//	m_vSize = Ogre::Vector2(dimensions.x, dimensions.y);
//	m_vPosition = Ogre::Vector2(
//    m_Screen->getWidth() / 2 - m_vSize.x / 2, 
//    m_Screen->getHeight() / 2 - m_vSize.y / 2);
//	//m_vButtonOffset = Ogre::Vector2(60,135);
//	//m_vButtonSize = Ogre::Vector2(275,60);
//	
//	m_Background = m_Layer->createRectangle(m_vPosition, m_vSize);
//	m_Background->background_image(bgImage);
//	
//	//m_Exit = new GUI::Button();
//	//m_Exit->background = m_Layer->createRectangle(
// //   m_vPosition + m_vButtonOffset + Ogre::Vector2(0, m_vButtonSize.y) * 2, 
// //   m_vButtonSize);
//	//m_Exit->img_base = "quickmenu_exit";
//	//m_Exit->img_hover = "quickmenu_exit_hover";
//	//m_Exit->hover(false);
//
//	setVisible(false);
//}
//
//void Menu::setVisible(bool value)
//{
//	m_Layer->setVisible(value);
//	b_isVisible = value;
//}
//
//bool Menu::mouseDown(unsigned int x, unsigned int y, OIS::MouseButtonID id)
//{
//  if (m_Background->intersects(Ogre::Vector2(x, y)) && isVisible())
//  {
//    return false;
//  }
//
//	return true;
//}
//
//bool Menu::mouseUp(unsigned int x, unsigned int y, OIS::MouseButtonID id)
//{
//	/*if(id == OIS::MB_Left && isVisible())
//	{
//    if (isOver(Ogre::Vector2(x, y), m_Exit))
//    {
//      if (m_Listener != nullptr)
//      {
//        m_Listener->MenuExit();
//      }
//
//			return false;
//		}
//	}*/
//
//  if (m_Background->intersects(Ogre::Vector2(x, y)) && isVisible())
//  {
//    return false;
//  }
//
//	return true;
//}
//
//void Menu::mouseMoved(unsigned int x, unsigned int y)
//{
//	//isOver(Ogre::Vector2(x, y), m_Exit);	
//}
//
//bool Menu::isOver(Ogre::Vector2 pos, GUI::Button *button)
//{
//	bool result = button->background->intersects(pos);
//	button->hover(result);
//
//	return result;
//}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/