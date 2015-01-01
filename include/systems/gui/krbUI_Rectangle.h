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
* @file   krbUI_Rectangle.h
* @author Nathan Harris
* @date   31 December 2014
* @brief  Layer UI element
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbUI_Rectangle_h
#define krbUI_Rectangle_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "utility/krbConverter.h"

#include "Gorilla/Gorilla.h"
#include "Monkey/Monkey.h"

#include <string>
using namespace std;

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

class UI_Rectangle
{
public:
  UI_Rectangle(const string& name, const string& bgImg, 
    Vector2 position, Vector2 dimensions, 
    Gorilla::Layer* layer)
  {
    str_Name    = name;
    _layer      = layer;
    _position   = position;

    _rectangle = _layer->createRectangle(toOgre(position), toOgre(dimensions));
    _rectangle->background_image(bgImg);
  }

  UI_Rectangle(const string& name, Color bgColor, 
    Vector2 position, Vector2 dimensions, 
    Gorilla::Layer* layer)
  {
    str_Name  = name;
    _layer = layer;

    _rectangle = _layer->createRectangle(toOgre(position), toOgre(dimensions));
    _rectangle->background_colour(toOgre(bgColor));
  }

  ~UI_Rectangle()
  {
    _layer->destroyRectangle(_rectangle);
  }  

  void setPosition(Vector2 position)
  {
    _rectangle->left(position.x);
    _rectangle->top(position.y);

    _position = position;
  }

  // GETTERS //////////////////////////////////////////////////////////////////
  Gorilla::Rectangle* getRectangle() { return _rectangle; }

  float getWidth()      { return _rectangle->width(); }
  float getHeight()     { return _rectangle->height(); }

protected:
  string                str_Name;
  bool                  b_Visible;

  Gorilla::Layer*       _layer;
  Gorilla::Rectangle*   _rectangle;

  Vector2               _position;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbGUI_Screen_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\
