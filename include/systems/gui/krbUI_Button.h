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
* @file   krbUI_Button.h
* @author Nathan Harris
* @date   28 December 2014
* @brief  Button UI element
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbUI_Button_h
#define krbUI_Button_h

/*****************************************************************************
*****************************************************************************/

#include "Gorilla/Gorilla.h"
#include "Monkey/Monkey.h"

#include "Ogre3D/OgreVector2.h"

#include "OIS/OISMouse.h"

#include <string>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class UI_Button
{
public:
  UI_Button(string name, Gorilla::Layer* layer, 
    string baseImg, string hoverImg,
    Vector2 position, Vector2 dimensions,
    OIS::Mouse* mouse)
  {
    str_Name = name;
    m_Layer = layer;

    m_Background = m_Layer->createRectangle(
      position.x, position.y, 
      dimensions.x, dimensions.y);

    img_Base = baseImg;
    img_Hover = hoverImg;

    m_Background->background_image(img_Base);

    m_Mouse = mouse;
  }

  bool isOver()
  {    
    bool result = m_Background->intersects(Ogre::Vector2(
      m_Mouse->getMouseState().X.abs, 
      m_Mouse->getMouseState().Y.abs));

	  if(result)
		{
			m_Background->background_image(img_Hover);
		}
		else
		{
			m_Background->background_image(img_Base);
		}

	  return result;
  }

  bool mouseDown(OIS::MouseButtonID button)
  {
    if(m_Layer->isVisible())
	  {
      if (isOver() && m_Mouse->getMouseState().buttonDown(button))
      { 
        return true; 
      }
		}

	  return false;
  }

  bool mouseUp(OIS::MouseButtonID id)
  {
    if(m_Layer->isVisible())
	  {
      //if (isOver() && m_Mouse->getMouseState().buttonDown(button))
      //{ 
      //  return true; 
      //}
		}

	  return false;
  }

protected:
  string              str_Name;
  
  Gorilla::Layer*     m_Layer;
  Gorilla::Rectangle* m_Background;
  string              img_Base;
  string		          img_Hover;

  OIS::Mouse*         m_Mouse;
};
  
/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbUI_Button_h

/***]EOF[*********************************************************************/