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
* @date   01 January 2015
* @brief  World system
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "systems/krbSystemWorld.h"
#include "systems/krbSystemPhysics.h"
#include "systems/krbSystemRender.h"

#include "Ogre3D/OgreBillboardSet.h"
#include "Ogre3D/OgreEntity.h"
#include "Ogre3D/OgreManualObject.h"
#include "Ogre3D/OgreMeshManager.h"
#include "Ogre3D/OgreSceneManager.h"
#include "Ogre3D/OgreViewport.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

template<> Kerberos::SystemWorld* Ogre::Singleton<Kerberos::SystemWorld>::msSingleton = 0;

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

SystemWorld::SystemWorld(Config* config, Logger* log)
{
  str_Name        = "World";
  m_Clock         = new Clock(false);
  ent_Clock       = new Clock(false);
  m_Config        = config;
  m_Log           = log;
  b_WorldPaused   = false;
  f_WorldTimeRate = 1.0f;
  f_WorldScale    = 1.0f;

  b_GridVisible   = false;
  i_EntityCount   = 0;
  i_EmitterCount  = 0;

  vec_Time.ms     = 0;
  vec_Time.sec    = 0;
  vec_Time.min    = 0;
  vec_Time.hr     = 0;
  vec_Time.day    = 0;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": 7 days? Really?");
}

SystemWorld::~SystemWorld()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Another world, another time.");
}

SystemWorld* SystemWorld::getSingletonPtr(void)
{
    return msSingleton;
}
SystemWorld& SystemWorld::getSingleton(void)
{  
    return (*msSingleton);  
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void SystemWorld::init()
{
  parseConfig();

  m_SceneMgr = SystemRender::getSingletonPtr()->getSceneManager();
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Got scene manager");

  m_OgreVP = SystemRender::getSingletonPtr()->getViewport();
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Got Ogre viewport");

  m_WorldNode = m_SceneMgr->getRootSceneNode();
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Got root scene node");

  createEntityBBS();
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Entity billboards created");

  ent_Clock->reset();

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Initialized :)");
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

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
  }
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void SystemWorld::halt()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Halted :)");
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void SystemWorld::parseConfig()
{
  f_WorldScale    = m_Config->getFloat("WORLD", "WorldScale");
  f_WorldRate     = m_Config->getFloat("WORLD", "WorldRate");
  f_WorldRateTemp = f_WorldTimeRate;
  f_WorldTimeRate = m_Config->getFloat("WORLD", "WorldTimeRate");

  f_GridScale     = m_Config->getFloat("WORLD", "GridScale");
  f_GridExtent    = m_Config->getFloat("WORLD", "GridExtent");

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void SystemWorld::resetClock()
{
  m_Clock->reset();
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void SystemWorld::pauseWorld()
{
  b_WorldPaused = !b_WorldPaused;  

  if (b_WorldPaused)
  {
    f_WorldRateTemp = f_WorldRate;
    f_WorldRate = 0.0f;
  }
  else
  {
    f_WorldRate = f_WorldRateTemp;
  }
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void SystemWorld::setWorldRate(float rate) 
{
  if (!b_WorldPaused)
  {
    f_WorldRateTemp = f_WorldRate;
    f_WorldRate = rate;
  }
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void SystemWorld::setAmbient(Color color)
{
  m_SceneMgr->setAmbientLight(toOgre(color));
  m_OgreVP->setBackgroundColour(toOgre(color));

  env_Color = color;
}

void SystemWorld::setFog(Color color, int type, float density, float start, float end)
{
  switch (type)
  {
    case 1:
      m_SceneMgr->setFog(
        Ogre::FOG_LINEAR, toOgre(color), density, start, end);
      break;
    case 2:
      m_SceneMgr->setFog(
        Ogre::FOG_EXP, toOgre(color), density, start, end);
      break;
    case 3:
      m_SceneMgr->setFog(
        Ogre::FOG_EXP2, toOgre(color), density, start, end);
      break;
    default:
      m_SceneMgr->setFog(
        Ogre::FOG_LINEAR, toOgre(color), density, start, end);
      break;
  }
}

void SystemWorld::setEnvironment(Color baseColor, Vector3 fogSettings)
{
  env_Color = baseColor;

  m_SceneMgr->setAmbientLight(toOgre(baseColor));

  m_OgreVP->setBackgroundColour(toOgre(baseColor));

  m_SceneMgr->setFog(Ogre::FOG_EXP2, toOgre(baseColor), 
    fogSettings.x, fogSettings.y, fogSettings.z);
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

// REFERENCE GRID, STARTS AT WORLD CENTER (Vector3(0,0,0)) AND WALKS OUT FROM THERE
void SystemWorld::createGrid()
{
  m_Grid = new Ogre::ManualObject("WORLD_GRID");

  m_Grid->begin("world_grid", Ogre::RenderOperation::OT_LINE_LIST);

  Ogre::Real res = f_GridScale * f_WorldScale;
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

  m_WorldNode->attachObject(m_Grid);
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void SystemWorld::createPlane(Vector2 extent)
{
  Ogre::Plane plane;
	plane.normal = Ogre::Vector3::UNIT_Y;
	plane.d = 0;
 
	Ogre::MeshManager::getSingleton().createPlane(
    "world_plane_mesh", 
    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
    plane, 
    extent.x * f_WorldScale, extent.y * f_WorldScale, 
    extent.x, extent.y,
    true, 1, 
    (extent.x * f_WorldScale) / 2, (extent.y * f_WorldScale) / 2,
    Ogre::Vector3::UNIT_Z);

	Ogre::Entity* planeEnt = m_SceneMgr->createEntity("WORLD_PLANE", "world_plane_mesh");
  planeEnt->getMesh()->prepare(true);
  planeEnt->getMesh()->buildTangentVectors();
  planeEnt->getMesh()->buildEdgeList();
	planeEnt->setMaterialName("world_plane");
	planeEnt->setCastShadows(false);
	m_WorldNode->createChildSceneNode()->attachObject(planeEnt);
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

void SystemWorld::createEntityBBS()
{
  bbs_Basic = m_SceneMgr->createBillboardSet("BBS_ENTITY_BASIC");
  bbs_Basic->setMaterialName("ent_basic");
  bbs_Basic->setDefaultWidth(0.5f);
  bbs_Basic->setDefaultHeight(0.5f);

  bbs_Cameras = m_SceneMgr->createBillboardSet("BBS_ENTITY_CAMERAS");
  bbs_Cameras->setMaterialName("ent_camera");
  bbs_Cameras->setDefaultWidth(0.5f);
  bbs_Cameras->setDefaultHeight(0.5f);

  bbs_Lights = m_SceneMgr->createBillboardSet("BBS_ENTITY_LIGHTS");
  bbs_Lights->setMaterialName("ent_light");
  bbs_Lights->setDefaultWidth(0.5f);
  bbs_Lights->setDefaultHeight(0.5f);

  m_WorldNode->attachObject(bbs_Basic);
  m_WorldNode->attachObject(bbs_Cameras);
  m_WorldNode->attachObject(bbs_Lights);
}

void SystemWorld::toggleEntityBillboards()
{
  b_EntityBillboardsOn = !b_EntityBillboardsOn;

  bbs_Basic->setVisible(b_EntityBillboardsOn);
  bbs_Cameras->setVisible(b_EntityBillboardsOn);
  bbs_Lights->setVisible(b_EntityBillboardsOn);
}

/*****************************************************************************
*****************************************************************************/

EntityCamera* SystemWorld::addEntityCamera(string name, Vector3 position)
{
  EntityCamera* entCamera = new EntityCamera(name, position, 
    bbs_Cameras, m_SceneMgr);

  return entCamera;
}

//EntityCamera* SystemWorld::addEntityCamera(string name, 
//  Vector3 position, Vector3 direction)
//{
//  EntityCamera* entCamera = new EntityCamera(name, position, direction,
//    bbs_Cameras, m_SceneMgr);
//
//  return entCamera;
//}

/*****************************************************************************
*****************************************************************************/

EntityLight* SystemWorld::addEntityLight(string name, Vector3 position)
{
  EntityLight* entLight = new EntityLight(name, position,
    bbs_Lights, m_SceneMgr);

  return entLight;
}

/*****************************************************************************
*****************************************************************************/

//EntityMesh* SystemWorld::addMesh(string name, string mesh, float scale)
//{
//  EntityMesh* entMesh = new EntityMesh(name, mesh, scale, m_SceneMgr);
//  vec_Entities.push_back(dynamic_cast<Entity*>(entMesh));
//  i_EntityCount++;
//
//  return entMesh;
//}

/*****************************************************************************
*****************************************************************************/

//EntityPhysicsStatic* SystemWorld::addStatic(string name, string mesh, 
//  int maxAge, Vector3 pos)
//{
//  EntityPhysicsStatic* entStatic = new EntityPhysicsStatic(
//    name, mesh, maxAge * f_WorldTimeRate, ent_Pulse, pos);
//
//  vec_Entities.push_back(dynamic_cast<Entity*>(entStatic));
//  i_EntityCount++;
//
//  return entStatic;
//}

/*****************************************************************************
*****************************************************************************/

//EntityPhysicsDynamic* SystemWorld::addDynamic(string name, string mesh, 
//  int maxAge, Vector3 pos)
//{
//  EntityPhysicsDynamic* entDynamic = new EntityPhysicsDynamic(
//    name, mesh, 1.0f, maxAge * f_WorldTimeRate, ent_Pulse, pos);
//
//  vec_Entities.push_back(dynamic_cast<Entity*>(entDynamic));
//  i_EntityCount++;
//
//  return entDynamic;
//}

/*****************************************************************************
*****************************************************************************/

//EntityParticleEmitter* SystemWorld::addParticleEmitter(string name)
//{
//  EntityParticleEmitter* entEmitter = new EntityParticleEmitter(name, m_SceneMgr);
//
//  vec_Entities.push_back(dynamic_cast<Entity*>(entEmitter));
//  i_EntityCount++;
//
//  vec_Emitters.push_back(entEmitter);
//  i_EmitterCount++;
//
//  return entEmitter;
//}

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