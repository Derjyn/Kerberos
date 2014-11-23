#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Kerberos.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

class krbCore : public Ogre::Singleton<krbCore>
{
public:
    krbCore();
	static krbCore& getInstance(void);
    static krbCore* getPointer(void);
 
	void Init(float logicRate, bool capFPS, float fpsCap);
	void Cycle();
	void LogicCycle();
	void RenderCycle();
	void Halt();

	Ogre::Real getMilliseconds() { return mTimer->getMilliseconds(); }
	
	krbInputSystem* pInputSys;
	krbRenderSystem* pRenderSys;

	Ogre::Root* mRoot;

	// CORE TIME
	Ogre::Real fTotalTime;
	Ogre::String strTotalTime;

	// LOGIC CYCLE
	Ogre::Real fLogicTimePassed;
	int iLogicTicks;

	// STRINGS FOR TICK COUNT
	Ogre::Real fTimePerLogicTick;
	Ogre::String strTotalLogicTicks;
	Ogre::String strTotalRenderTicks;

	// DEMO STUFF
	float fRanR, fRanG, fRanB;

protected:
	Ogre::Timer* mTimer;
};

// EOF ////////////////////////////////////////////////////////////////////////////////////////////