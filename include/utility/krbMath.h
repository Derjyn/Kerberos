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
* @file   krbMath.h
* @author Nathan Harris
* @date   31 December 2014
* @brief  Helpful maths and things to do with numbers
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbMath_h
#define krbMath_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "utility/krbVector2.h"
#include "utility/krbVector3.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

// COLOR
class Color
{
public:
  Color()
  {
    r = 1.0f;
    g = 1.0f;
    b = 1.0f;
    a = 1.0f;
  }
  Color(float red, float green, float blue)
  {
    r = red;
    g = green;
    b = blue;
    a = 1.0f;
  }
  Color(float red, float green, float blue, float alpha)
  {
    r = red;
    g = green;
    b = blue;
    a = alpha;
  }

  float r, g, b, a;
};

// TIME VECTOR
class TimeVector
{
public:
  TimeVector()
  {
    day = 0;
    hr  = 0;
    min = 0;
    sec = 0;
    ms  = 0;
  }

  unsigned int day;
  unsigned int hr;
  unsigned int min;
  unsigned int sec;
  double ms;
};

// FUNCTIONS

inline float findElemCenter(float parentLength, float elemLength)
{
  return (parentLength / 2) - (elemLength / 2);
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbMath_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\