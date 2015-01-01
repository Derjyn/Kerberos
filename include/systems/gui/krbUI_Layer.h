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
* @file   krbUI_Layer.h
* @author Nathan Harris
* @date   01 January 2015
* @brief  Layer UI element
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbUI_Layer_h
#define krbUI_Layer_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "Gorilla/Gorilla.h"
#include "Monkey/Monkey.h"

#include <string>
using namespace std;

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

class UI_Layer
{
public:
  UI_Layer(const string& name, bool visible, unsigned int index, Gorilla::Screen* screen)
  {
    str_Name  = name;
    b_Visible = visible;
    _screen   = screen;
    
    _layer = _screen->createLayer(index);

    _layer->setVisible(b_Visible);
  }

  ~UI_Layer()
  {
    _screen->destroy(_layer);
  }

  void toggleVisible()
  {
    b_Visible = !b_Visible;

    if (b_Visible)
    {
      _layer->show();
    }
    else
    {
      _layer->hide();
    }
  }

  void hide() { _layer->hide(); }
  void show() { _layer->show(); }

  // GETTERS //////////////////////////////////////////////////////////////////
  Gorilla::Layer* getLayer() { return _layer; }

  bool isVisible() 
  { 
    b_Visible = _layer->isVisible();
    return b_Visible; 
  }  

protected:
  string                str_Name;
  bool                  b_Visible;

  Gorilla::Layer*       _layer;
  Gorilla::Screen*      _screen;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbGUI_Screen_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\
