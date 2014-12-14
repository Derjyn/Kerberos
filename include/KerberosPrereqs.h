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
* @file   KerberosPrereqs.h
* @author Nathan Harris
* @date   13 December 2014
* @brief  Prerequisites and what-have-you
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef KerberosPrereqs_h
#define KerberosPrereqs_h

#include "KerberosUtility.h"

/*****************************************************************************
*****************************************************************************/

#define KRB_VERSION_MAJOR 0
#define KRB_VERSION_MINOR 0
#define KRB_VERSION_PATCH 1
#define KRB_VERSION_NAME "Conceptus"

#define KRB_VERSION ((KRB_VERSION_MAJOR << 16) | (KRB_VERSION_PATCH << 8) | KRB_VERSION_PATCH)

/*****************************************************************************
*****************************************************************************/

#endif // KerberosPrereqs_h

/***]EOF[*********************************************************************/