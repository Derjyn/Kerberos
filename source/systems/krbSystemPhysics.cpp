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
* @file   krbSystemPhysics.cpp
* @author Nathan Harris
* @date   26 December 2014
* @brief  Physics system
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemPhysics.h"
#include "systems/krbSystemRender.h"

#include "Ogre3D/OgreSceneManager.h"
#include "Ogre3D/OgreSceneNode.h"

/*****************************************************************************
*****************************************************************************/

template<> Kerberos::SystemPhysics* Ogre::Singleton<Kerberos::SystemPhysics>::msSingleton = 0;

namespace Kerberos {

SystemPhysics* SystemPhysics::getSingletonPtr(void) { return msSingleton; }
SystemPhysics& SystemPhysics::getSingleton(void)    { return (*msSingleton); }

/*****************************************************************************
*****************************************************************************/

SystemPhysics::SystemPhysics(Config* config, Logger* log)
{
  str_Name  = "Physics";
  m_Config  = config;
  m_Log     = log;
  b_DebugOn = false;
  b_InfinitePlane = false;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Gravity check good!");
}

SystemPhysics::~SystemPhysics()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Don't cry to me, if you fall.");
}

/*****************************************************************************
*****************************************************************************/

void SystemPhysics::init()
{
  parseConfig();

  m_SceneMgr  = SystemRender::getSingletonPtr()->getSceneManager();
  m_WorldNode = m_SceneMgr->getRootSceneNode();
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Connected to Ogre");

  m_PhysBroadphase = new btDbvtBroadphase();
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Broadphase created");

	m_PhysCollisionConfig = new btDefaultCollisionConfiguration();
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Collision config created");

	m_PhysDispatcher = new btCollisionDispatcher(m_PhysCollisionConfig);
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Collision dispatcher created");

	m_PhysSolver = new btSequentialImpulseConstraintSolver();
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Physics solver created");

	m_PhysWorld = new btDiscreteDynamicsWorld(
    m_PhysDispatcher, m_PhysBroadphase, m_PhysSolver, m_PhysCollisionConfig);
	m_PhysWorld->setGravity(btVector3(0, f_Gravity, 0));
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Physics world created");

  if (b_InfinitePlane)
  {
    btDefaultMotionState* plane_MS = new btDefaultMotionState(
      btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));

    btRigidBody::btRigidBodyConstructionInfo plane_CI(
      0, plane_MS, 
      new btStaticPlaneShape(btVector3(0, 1, 0), 1),
      btVector3(0, 0, 0));
    plane_CI.m_friction = 0.54f;
    plane_CI.m_restitution = 0.81f;

    m_PhysWorld->addRigidBody(new btRigidBody(plane_CI));

    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
      str_Name + ": Infinite collision plane created");
  }

  m_PhysDebug = new BtOgre::DebugDrawer(m_WorldNode, m_PhysWorld);
	m_PhysWorld->setDebugDrawer(m_PhysDebug);
  m_PhysDebug->setDebugMode(0);
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Debugger created");

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Initialized :)");
}

void SystemPhysics::createBody(string name, string mesh, Vector3 pos)
{
  delete m_PhysDebug;
  delete m_PhysWorld;

  delete m_PhysSolver;
  delete m_PhysDispatcher;
  delete m_PhysCollisionConfig;
  delete m_PhysBroadphase;
}

/*****************************************************************************
*****************************************************************************/

void SystemPhysics::cycle(float delta, float rate, bool paused)
{
  if (!paused)
  {
    m_PhysWorld->stepSimulation(delta, i_PhysicsSteps, f_PhysicsRate * rate);
    m_PhysDebug->step();
  }

  m_PhysWorld->debugDrawWorld();
}

/*****************************************************************************
*****************************************************************************/

void SystemPhysics::halt()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Halted :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemPhysics::parseConfig()
{
  b_InfinitePlane = m_Config->getBool("PHYSICS", "InfinitePlane");
  i_PhysicsSteps  = m_Config->getInt("PHYSICS", "PhysicsSteps");
  f_PhysicsRate   = 1.0f / m_Config->getFloat("PHYSICS", "PhysicsRPS");
  f_Gravity       = m_Config->getFloat("PHYSICS", "Gravity");

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

/*****************************************************************************
*****************************************************************************/

void SystemPhysics::toggleDebug()
{
  b_DebugOn = !b_DebugOn;

  if (b_DebugOn)
  {
    m_PhysDebug->setDebugMode(1);
  }
  else
  {
    m_PhysDebug->setDebugMode(0);
  }  
}

/*****************************************************************************
*****************************************************************************/

float SystemPhysics::getPhysicsRate()
{
  return f_PhysicsRate;
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/