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
* @file   krbUI_Menu.h
* @author Nathan Harris
* @date   28 December 2014
* @brief  Menu UI element
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbUI_Menu_h
#define krbUI_Menu_h

/*****************************************************************************
*****************************************************************************/

#include "utility/krbMath.h"

#include "Gorilla/Gorilla.h"
#include "Monkey/Monkey.h"

#include <string>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class UI_Menu
{
public:
  UI_Menu(string name, string atlas, string background, 
    bool visible, Vector2 dimensions,
    Ogre::Viewport* vp, Gorilla::Silverback* silverback)
  {
    str_Name        = name;
    b_Visible       = visible;
    vec_Dimensions  = dimensions;
    m_Screen        = silverback->createScreen(vp, atlas);
    m_Layer         = m_Screen->createLayer();
    
    vec_Position = Vector2(
      m_Screen->getWidth() / 2 - vec_Dimensions.x / 2, 
      m_Screen->getHeight() / 2 - vec_Dimensions.y / 2);
   
    m_Background = m_Layer->createRectangle(
      Ogre::Vector2(vec_Position.x, vec_Position.y),
      Ogre::Vector2(vec_Dimensions.x, vec_Dimensions.y));
	  m_Background->background_image(background);

    m_Screen->setVisible(b_Visible);
  }

  UI_Menu(string name, string atlas, string background,
    bool visible, Vector2 position, Vector2 dimensions,
    Ogre::Viewport* vp, Gorilla::Silverback* silverback)
  {
    str_Name        = name;
    b_Visible       = visible;
    vec_Dimensions  = dimensions;
    vec_Position    = position;
    m_Screen        = silverback->createScreen(vp, atlas);
    m_Layer         = m_Screen->createLayer();

    m_Background = m_Layer->createRectangle(
      Ogre::Vector2(vec_Position.x, vec_Position.y),
      Ogre::Vector2(vec_Dimensions.x, vec_Dimensions.y));
	  m_Background->background_image(background);

    m_Screen->setVisible(b_Visible);
  }

  ~UI_Menu()
  {
  }

  void toggleVisible()
  {
    b_Visible = !b_Visible;

    if (b_Visible)
    {
      m_Screen->show();
    }
    else
    {
      m_Screen->hide();
    }
  }

  bool isVisible() { return b_Visible; }

  Gorilla::Screen* getScreen()  { return m_Screen; }
  Gorilla::Layer* getLayer()    { return m_Layer; }
  Vector2 getPosition()         { return vec_Position; }
  Vector2 getDimensions()       { return vec_Dimensions; }

protected:
  string                str_Name;
  bool                  b_Visible;

  Vector2               vec_Position;
  Vector2               vec_Dimensions;

  Gorilla::Screen*	    m_Screen;
	Gorilla::Layer*		    m_Layer;
	Gorilla::Rectangle*   m_Background;

private:
  friend class UI_GUI;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbUI_Menu_h

/***]EOF[*********************************************************************/
