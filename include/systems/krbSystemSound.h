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
* @file   krbSystemSound.h
* @author Nathan Harris
* @date   31 December 2014
* @brief  Sound system
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbSystemSound_h
#define krbSystemSound_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "systems/krbSystem.h"
#include "utility/krbMath.h"

#include "FMOD/fmod.hpp"

#include <string>
using namespace std;

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

//
//! \brief Sound system, utilizing FMOD
//
class SystemSound final : 
  public System, 
  public Ogre::Singleton<SystemSound>
{
public:
  SystemSound(Config* config, Logger* log);
  ~SystemSound();

  static SystemSound& getSingleton();
  static SystemSound* getSingletonPtr();

  void init();
  void cycle();
  void halt();

  bool Load2DSound(const string& filepath, FMOD::Sound** sound);
  void Play2DSound(FMOD::Sound* sound, FMOD::Channel** channel);
  
  bool Load3DSound(const string& filepath, FMOD::Sound** sound);
  void Play3DSound(FMOD::Sound* sound, 
    const FMOD_VECTOR& position, FMOD::Channel** channel);

  bool LoadSoundFromStream(const string& filepath, FMOD::Sound** sound);
  void PlayStreamingSound(FMOD::Sound* sound, FMOD::Channel** channel);

  void StopSound(FMOD::Sound* sound);
  void StopMusic(FMOD::Sound* sound);

  void PauseSound(FMOD::Sound* sound, FMOD::Channel** channel);
  void PauseMusic(FMOD::Sound* sound, FMOD::Channel** channel);
  void SetLoop(FMOD::Sound* sound, bool value);

  void updateEars(Vector3 position, Vector3 velocity, 
    Vector3 forward, Vector3 upward);

  FMOD::System* getFMOD() { return m_FMOD; }

protected:
  FMOD_RESULT       result;  

  FMOD::System*     m_FMOD;
  FMOD_RESULT       m_Result;
  int               i_DriverCount;
  FMOD_SPEAKERMODE  m_SpeakerMode;
  FMOD_CAPS         m_Caps;

  float             f_DistanceFactor;
  FMOD_VECTOR       fmv_EarsPosition;
  FMOD_VECTOR       fmv_EarsVecloity;
  FMOD_VECTOR       fmv_EarsForward;
  FMOD_VECTOR       fmv_EarsUpward;
  void parseConfig();
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbSystemSound_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\