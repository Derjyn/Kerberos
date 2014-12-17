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
* @file   krbUtility.h
* @author Nathan Harris
* @date   17 December 2014
* @brief  Deeper down the rabbit hole?
*
* @description
*   These varied utility functions and such are globally available, though
*   if you want to change that, comment the #define UTIL_GLOBAL line
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbUtility_h
#define krbUtility_h

/*****************************************************************************
*****************************************************************************/

#define UTIL_GLOBAL
#ifndef UTIL_GLOBAL
namespace Kerberos {
#endif

/*****************************************************************************
*****************************************************************************/

// HANDY FOR ERROR REPORTING - FROM http://goo.gl/c0yroZ
// TO USE, DO: CONMSG(AT, "YOUR MESSAGE");
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ " at line " TOSTRING(__LINE__) " : (" __FUNCTION__ ")"

static void CONMSG(const char *location, const char* msg)
{
  const char *no_path = strrchr(location, '\\');
  if (no_path)
  {
    ++no_path;  // move off of '\\'
  }
  else
  {
    no_path = location;
  }

  printf("ALERT: %s in %s\n", msg, no_path);
}

/*****************************************************************************
*****************************************************************************/

#ifndef UTIL_GLOBAL
}
#endif // namespace Kerberos
#endif // krbUtility_h

/***]EOF[*********************************************************************/