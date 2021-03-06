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
* @date   01 January 2015
* @brief  Button UI element
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbUI_Button_h
#define krbUI_Button_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "utility/krbMath.h"

#include "Gorilla/Gorilla.h"
#include "Monkey/Monkey.h"

#include "Ogre3D/OgreVector2.h"

#include "OIS/OISMouse.h"

#include <string>
using namespace std;

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

class UI_Button
{
public:
  UI_Button(string name, Gorilla::Layer* layer, 
    string baseImg, string hoverImg,
    Vector2 position, Vector2 dimensions,
    OIS::Mouse* mouse)
  {
    str_Name  = name;
    _layer    = layer;
    _bgBase   = baseImg;
    _bgHover  = hoverImg;
    _mouse    = mouse;

    _rectangle = _layer->createRectangle(position.x, position.y, 
      dimensions.x, dimensions.y);

    _rectangle->background_image(_bgBase);
  }

  bool isOver()
  {    
    bool result = _rectangle->intersects(Ogre::Vector2(
      _mouse->getMouseState().X.abs, 
      _mouse->getMouseState().Y.abs));

	  if(result)
		{
			_rectangle->background_image(_bgHover);
		}
		else
		{
			_rectangle->background_image(_bgBase);
		}

	  return result;
  }

  bool mouseDown(OIS::MouseButtonID button)
  {
    if(_layer->isVisible())
	  {
      if (isOver() && _mouse->getMouseState().buttonDown(button))
      { 
        return true; 
      }
		}

	  return false;
  }

protected:
  string              str_Name;
  
  Gorilla::Layer*     _layer;
  Gorilla::Rectangle* _rectangle;
  string              _bgBase;
  string		          _bgHover;

  OIS::Mouse*         _mouse;
};
  
///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbUI_Button_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\