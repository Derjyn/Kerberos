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
* @file   krbSystemSound.cpp
* @author Nathan Harris
* @date   26 December 2014
* @brief  Sound system
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemSound.h"

/*****************************************************************************
*****************************************************************************/

template<> Kerberos::SystemSound* Ogre::Singleton<Kerberos::SystemSound>::msSingleton = 0;

namespace Kerberos {
  
/*****************************************************************************
*****************************************************************************/

SystemSound::SystemSound(Config* config, Logger* log)
{
  str_Name  = "Sound";
  m_Config  = config;
  m_Log     = log;
  m_FMOD    = nullptr;

  f_DistanceFactor = 1.0f; // IN METERS PER SECOND

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Watch the volume...");
}

SystemSound::~SystemSound()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Holler if you need me.");
}

SystemSound* SystemSound::getSingletonPtr(void)
{
    return msSingleton;
}
SystemSound& SystemSound::getSingleton(void)
{  
    return (*msSingleton);  
}

/*****************************************************************************
*****************************************************************************/

void SystemSound::init()
{
  // INIT FMOD SYSTEM
  m_Result = FMOD::System_Create(&m_FMOD);
  //mResult = FMOD::Memory_Initialize(malloc(32 * 1024 * 1024), 32 * 1024 * 1024, 0, 0, 0);

  // DETECT AND SET SPEAKER MODE
  FMOD_SPEAKERMODE speakermode;
  m_Result = m_FMOD->getDriverCaps(0, 0, 0, &speakermode);
  m_Result = m_FMOD->setSpeakerMode(speakermode);

  //mResult = pFMOD->setSoftwareChannels(64);
  //mResult = pFMOD->setHardwareChannels(64);
  m_Result = m_FMOD->set3DSettings(1.0f, f_DistanceFactor, 1.0f);

  // SETUP SOME ADVANCED SETTINGS
  FMOD_ADVANCEDSETTINGS advSettings;
  memset(&advSettings, 0, sizeof(FMOD_ADVANCEDSETTINGS));
  advSettings.cbsize = sizeof(FMOD_ADVANCEDSETTINGS);
  advSettings.debugLogFilename = "debug/FMOD.log";
  m_FMOD->setAdvancedSettings(&advSettings);

  // SET MAX CHANNELS TO SOMETHING SANE (TESTING NEEDED)
  // ALDO CHANGE TO RIGHT-HANDED ORIENTATION
  m_Result = m_FMOD->init(128,
    FMOD_INIT_NORMAL |
    FMOD_INIT_3D_RIGHTHANDED |
    FMOD_INIT_VOL0_BECOMES_VIRTUAL,
    0);

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Initialized :)");
}

void SystemSound::cycle()
{
  m_FMOD->update();
}

void SystemSound::halt()
{
  m_Result = m_FMOD->close();
  m_Result = m_FMOD->release();

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Halted :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemSound::parseConfig()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

/*****************************************************************************
*****************************************************************************/

void SystemSound::Play2DSound(FMOD::Sound* sound, FMOD::Channel** channel)
{
  m_Result = m_FMOD->playSound(FMOD_CHANNEL_FREE, sound, false, &*channel);
}

bool SystemSound::Load2DSound(const string& filepath, FMOD::Sound** sound)
{
  m_Result = m_FMOD->createSound(
    filepath.c_str(), FMOD_2D, 0, &*sound);

  m_Result = (*sound)->setMode(FMOD_LOOP_OFF);

  return true;
}

/*****************************************************************************
*****************************************************************************/

bool SystemSound::Load3DSound(const string& filepath, FMOD::Sound** sound)
{
  m_Result = m_FMOD->createSound(
    filepath.c_str(), FMOD_3D | FMOD_LOOP_OFF, 0, &*sound);

  return true;
}

void SystemSound::Play3DSound (FMOD::Sound* sound,
  const FMOD_VECTOR& position, FMOD::Channel** channel)
{
  m_Result = m_FMOD->playSound (FMOD_CHANNEL_FREE, sound, false, &*channel);
  m_Result = (*channel)->set3DAttributes (&position, 0);
}

/*****************************************************************************
*****************************************************************************/

void SystemSound::PlayStreamingSound(FMOD::Sound* sound, FMOD::Channel** channel)
{
  m_Result = m_FMOD->playSound(FMOD_CHANNEL_FREE, sound, false, &*channel);
}
bool SystemSound::LoadSoundFromStream (
  const string& filepath, FMOD::Sound** sound)
{
  m_Result = m_FMOD->createStream (filepath.c_str (), FMOD_2D, 0, &*sound);

  return true;
}

/*****************************************************************************
*****************************************************************************/

void SystemSound::StopSound(FMOD::Sound* sound)
{
}

void SystemSound::StopMusic(FMOD::Sound* sound)
{
}

/*****************************************************************************
*****************************************************************************/

void SystemSound::PauseSound(FMOD::Sound* sound, FMOD::Channel** channel)
{
  bool pause = false;
  (*channel)->getPaused(&pause);
  (*channel)->setPaused(!pause);
}

void SystemSound::PauseMusic(FMOD::Sound* sound, FMOD::Channel** channel)
{
  bool pause = false;
  (*channel)->getPaused(&pause);
  (*channel)->setPaused(!pause);
}

void SystemSound::SetLoop(FMOD::Sound* sound, bool value)
{
  int loop = 0;

  if (value)
  {
    loop = FMOD_LOOP_NORMAL;
  }
  else 
  {
    loop = FMOD_LOOP_OFF;
  }

  sound->setMode(loop);
}

/*****************************************************************************
*****************************************************************************/

void SystemSound::updateEars(Vector3 position, Vector3 velocity,
  Vector3 forward, Vector3 upward)
{
  fmv_EarsPosition.x = position.x;
  fmv_EarsPosition.y = position.y;
  fmv_EarsPosition.z = position.z;

  fmv_EarsVecloity.x = velocity.x;
  fmv_EarsVecloity.y = velocity.y;
  fmv_EarsVecloity.z = velocity.z;

  fmv_EarsForward.x = forward.x;
  fmv_EarsForward.y = forward.y;
  fmv_EarsForward.z = forward.z;

  fmv_EarsUpward.x = upward.x;
  fmv_EarsUpward.y = upward.y;
  fmv_EarsUpward.z = upward.z;

  m_Result = m_FMOD->set3DListenerAttributes(0, 
    &fmv_EarsPosition, &fmv_EarsVecloity,
    &fmv_EarsForward, &fmv_EarsUpward);
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/