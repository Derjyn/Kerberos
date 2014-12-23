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
* @file   krbSystemWorld.cpp
* @author Nathan Harris
* @date   23 December 2014
* @brief  World system
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemWorld.h"
#include "core/krbConfig.h"
#include "core/krbClock.h"
#include "core/krbLogger.h"

#include "Bullet/BulletDynamics/Dynamics/btDynamicsWorld.h"

#include "Ogre3D/OgreBillboardSet.h"
#include "Ogre3D/OgreManualObject.h"
#include "Ogre3D/OgreSceneManager.h"
#include "Ogre3D/OgreViewport.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

SystemWorld::SystemWorld(Config* config, Logger* log)
{
  str_Name      = "World";
  m_Clock       = new Clock(false);
  ent_Clock     = new Clock(false);
  m_Config      = config;
  m_Log         = log;
  b_WorldPaused = false;
  b_GridVisible = false;
  i_EntityCount = 0;

  vec_Time.ms   = 0;
  vec_Time.sec  = 0;
  vec_Time.min  = 0;
  vec_Time.hr   = 0;
  vec_Time.day  = 0;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": 7 days? Really?");
}

SystemWorld::~SystemWorld()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Another world, another time.");
}

/*****************************************************************************
*****************************************************************************/

void SystemWorld::init()
{
  parseConfig();

  createGrid();

  //m_SceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

  ent_Clock->reset();

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Initialized :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemWorld::cycle()
{
  if (!b_WorldPaused)
  {
    vec_Time.ms = m_Clock->msex() * (f_WorldTimeRate * f_WorldRate);

    if(vec_Time.ms >= 1000.0)
    {
      m_Clock->reset();

      int secPrev = vec_Time.sec;
      vec_Time.sec++;
      ent_Pulse += vec_Time.sec - secPrev;

      if (vec_Time.sec >= 60)
      {
        m_Clock->reset();
        vec_Time.sec = 0;

        vec_Time.min++;

        if (vec_Time.sec >= 60)
        {
          m_Clock->reset();
          vec_Time.sec = 0;

          vec_Time.hr++;

          if (vec_Time.hr >= 24)
          {
            m_Clock->reset();
            vec_Time.hr = 0;

            vec_Time.day++;
          }
        }
      }
    }

    // REMOVE OLD ENTITIES... GOTTA BE A BETTER WAY TO DO THIS!
    vit_Entities = vec_Entities.begin();
    for (; vit_Entities != vec_Entities.end(); vit_Entities++)
    {
      if ((*vit_Entities)->getMaxAge() > 0)
      {
        if ((*vit_Entities)->getAge(ent_Pulse) > (*vit_Entities)->getMaxAge())
        {          
          delete (*vit_Entities);
          vec_Entities.erase(vit_Entities);

          i_EntityCount--;
        }
      }
    }
  }
}

/*****************************************************************************
*****************************************************************************/

void SystemWorld::halt()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Halted :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemWorld::parseConfig()
{
  f_WorldRate     = m_Config->getFloat("WORLD", "WorldRate");
  f_WorldTimeRate = m_Config->getFloat("WORLD", "WorldTimeRate");

  f_GridScale     = m_Config->getFloat("WORLD", "GridScale");
  f_GridExtent    = m_Config->getFloat("WORLD", "GridExtent");

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

/*****************************************************************************
*****************************************************************************/

void SystemWorld::connectOgre(
  Ogre::SceneManager* sceneMgr, Ogre::Viewport* viewport)
{
  m_SceneMgr  = sceneMgr;
  m_OgreVP    = viewport;

  m_WorldNode = 
    m_SceneMgr->getRootSceneNode()->createChildSceneNode("WORLD_NODE");
}


void SystemWorld::connectBullet(btDynamicsWorld* world)
{
  m_BulletWorld = world;
}

/*****************************************************************************
*****************************************************************************/

void SystemWorld::resetClock()
{
  m_Clock->reset();
}

void SystemWorld::pauseWorld()
{
  b_WorldPaused = !b_WorldPaused;
}

/*****************************************************************************
*****************************************************************************/

void SystemWorld::setAmbient(Color color)
{
  m_SceneMgr->setAmbientLight(Ogre::ColourValue(color.r, color.g, color.b));

  env_Color = color;
}

void SystemWorld::setFog(Color color, float density, float start, float end)
{
  m_SceneMgr->setFog(Ogre::FOG_EXP2, Ogre::ColourValue(
    color.r, color.g, color.b), density, start, end);

  m_OgreVP->setBackgroundColour(Ogre::ColourValue(
    color.r, color.g, color.b));
}

void SystemWorld::setEnvironment(Color baseColor,
  float fogDensity, float fogStart, float fogEnd)
{
  env_Color = baseColor;

  m_SceneMgr->setAmbientLight(Ogre::ColourValue(
    baseColor.r, baseColor.g, baseColor.b));

  m_SceneMgr->setFog(Ogre::FOG_EXP2, Ogre::ColourValue(
    baseColor.r, baseColor.g, baseColor.b), 
    fogDensity, fogStart, fogEnd);

  m_OgreVP->setBackgroundColour(Ogre::ColourValue(
    baseColor.r, baseColor.g, baseColor.b));
}

/*****************************************************************************
*****************************************************************************/

// REFERENCE GRID, STARTS AT WORLD CENTER (Vector3(0,0,0)) AND WALKS OUT FROM THERE
void SystemWorld::createGrid()
{
  m_Grid = new Ogre::ManualObject("WORLD_GRID");

  m_Grid->begin("grid", Ogre::RenderOperation::OT_LINE_LIST);

  Ogre::Real res = f_GridScale;
  unsigned int count = f_GridExtent;
  unsigned int halfCount = count / 2;
  Ogre::Real full = (res * count);
  Ogre::Real half = full / 2;
  Ogre::Real y = 0;

  for (unsigned i = 0; i < count + 1; i++)
  {
    m_Grid->position(-half, y, -half + (res * i));
    m_Grid->position(0, y, -half + (res * i));
    m_Grid->position(0, y, -half + (res * i));
    m_Grid->position(half, y, -half + (res * i));
    m_Grid->position(-half + (res * i), y, -half);
    m_Grid->position(-half + (res * i), y, 0);
    m_Grid->position(-half + (res * i), y, 0);
    m_Grid->position(-half + (res * i), y, half);
  }

  m_Grid->end();
  m_Grid->setVisible(b_GridVisible);

  m_SceneMgr->getRootSceneNode()->attachObject(m_Grid);
}

/*****************************************************************************
*****************************************************************************/

void SystemWorld::toggleGrid()
{
  b_GridVisible = !b_GridVisible;

  m_Grid->setVisible(b_GridVisible);
}

/*****************************************************************************
*****************************************************************************/

EntityCamera* SystemWorld::addCamera(string name)
{
  EntityCamera* entCamera = new EntityCamera(name, m_SceneMgr);

  vec_Entities.push_back(dynamic_cast<Entity*>(entCamera));
  i_EntityCount++;

  return entCamera;
}

/*****************************************************************************
*****************************************************************************/

EntityLight* SystemWorld::addLight(string name, EntityLight::LightType type)
{
  EntityLight* entLight = new EntityLight(name, type, m_SceneMgr);
  vec_Entities.push_back(dynamic_cast<Entity*>(entLight));
  i_EntityCount++;

  return entLight;
}

/*****************************************************************************
*****************************************************************************/

EntityMesh* SystemWorld::addMesh(string name, string mesh, float scale)
{
  EntityMesh* entMesh = new EntityMesh(name, mesh, scale, m_SceneMgr);
  vec_Entities.push_back(dynamic_cast<Entity*>(entMesh));
  i_EntityCount++;

  return entMesh;
}

/*****************************************************************************
*****************************************************************************/

EntityPhysicsDynamic* SystemWorld::addDynamic(string name, string mesh, 
  int maxAge, float mass, Vector3 pos)
{
  EntityPhysicsDynamic* entDynamic = new EntityPhysicsDynamic(name, mesh, 
    maxAge * f_WorldTimeRate, ent_Pulse, mass, pos, 
    m_SceneMgr, m_BulletWorld);

  vec_Entities.push_back(dynamic_cast<Entity*>(entDynamic));
  i_EntityCount++;

  return entDynamic;
}

/*****************************************************************************
*****************************************************************************/

EntityPhysicsStatic* SystemWorld::addStatic(string name, string mesh, 
  int maxAge, Vector3 pos)
{
  EntityPhysicsStatic* entStatic = new EntityPhysicsStatic(name, mesh, 
    maxAge * f_WorldTimeRate, ent_Pulse, pos, 
    m_SceneMgr, m_BulletWorld);

  vec_Entities.push_back(dynamic_cast<Entity*>(entStatic));
  i_EntityCount++;

  return entStatic;
}

/*****************************************************************************
*****************************************************************************/

void SystemWorld::setWorldRate(float rate)    { f_WorldRate = rate; }

/*****************************************************************************
*****************************************************************************/

float SystemWorld::getWorldRate()       { return f_WorldRate; }
float SystemWorld::getWorldTimeRate()   { return f_WorldTimeRate; }
bool SystemWorld::isPaused()            { return b_WorldPaused; }
int SystemWorld::getEntityCount()       { return i_EntityCount; }
TimeVector SystemWorld::getTimeVector() { return vec_Time; }

string SystemWorld::getTimeString()
{
  stringstream ss;
  ss <<
    vec_Time.day  << "days, " <<
    vec_Time.hr   << "hr " <<
    vec_Time.min  << "min " <<
    vec_Time.sec  << "sec ";

  return ss.str();
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/