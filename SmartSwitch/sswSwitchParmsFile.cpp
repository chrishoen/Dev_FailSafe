//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "sswSwitchParms.h"

#define  _SSWSWITCHPARMSFILE_CPP_
#include "sswSwitchParmsFile.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SSW
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SwitchParmsFile::SwitchParmsFile()
{
   reset();
}

void SwitchParmsFile::reset()
{
   BaseClass::reset();

   BaseClass::reset();
   if (Ris::portableIsWindows())
   {
      BaseClass::setFilePath("C:/aaa_prime/Switch/Switch_Parms.txt");
   }
   else
   {
      BaseClass::setFilePath_RelativeToBaseDir("files/Switch_Parms.txt");
   }

   mThresholderParmsM2Wrapper.initialize(&gSwitchParms.mThresholderParmsM2);
   mThresholderParmsM1Wrapper.initialize(&gSwitchParms.mThresholderParmsM1);
   mThresholderParmsP1Wrapper.initialize(&gSwitchParms.mThresholderParmsP1);
   mThresholderParmsP2Wrapper.initialize(&gSwitchParms.mThresholderParmsP2);

   mTimerPeriod = 0;
   mTestMode = 0;
   mInitialValueA = 0.0;
   mInitialValueB = 0.0;
   mAlphaFilterTs = 0.0;
   mAlphaFilterTc = 0.0;
   mFuzzyToCrispThreshLo = 0.0;
   mFuzzyToCrispThreshHi = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void SwitchParmsFile::expand()
{
   // Copy file parms to parms.
   gSwitchParms.mAlphaFilterTs = mAlphaFilterTs;
   gSwitchParms.mAlphaFilterTc = mAlphaFilterTc;
   gSwitchParms.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   gSwitchParms.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;

   // Expand.
   gSwitchParms.expand();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SwitchParmsFile::show()
{
   printf("\n");
   printf("SwitchParmsFile************************************************ %s\n", mTargetSection);
   printf("TimerPeriod            %10d\n",   mTimerPeriod);
   printf("TestMode               %10d\n",   mTestMode);
   printf("InitialValueA          %10.4f\n", mInitialValueA);
   printf("InitialValueB          %10.4f\n", mInitialValueB);

   printf("\n");
   mThresholderParmsM2Wrapper.show("M2");
   mThresholderParmsM1Wrapper.show("M1");
   mThresholderParmsP1Wrapper.show("P1");
   mThresholderParmsP2Wrapper.show("P2");
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void SwitchParmsFile::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TimerPeriod"))           mTimerPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("TestMode"))              mTestMode = aCmd->argInt(1);
   if (aCmd->isCmd("InitialValueA"))         mInitialValueA = aCmd->argFloat(1);
   if (aCmd->isCmd("InitialValueB"))         mInitialValueB = aCmd->argFloat(1);

   if (aCmd->isCmd("AlphaFilterTs"))         mAlphaFilterTs = aCmd->argFloat(1);
   if (aCmd->isCmd("AlphaFilterTc"))         mAlphaFilterTc = aCmd->argFloat(1);
   if (aCmd->isCmd("FuzzyToCrispThreshLo"))  mFuzzyToCrispThreshLo = aCmd->argFloat(1);
   if (aCmd->isCmd("FuzzyToCrispThreshHi"))  mFuzzyToCrispThreshHi = aCmd->argFloat(1);

   if (aCmd->isCmd("ThresholderM2"))     nestedPush(aCmd, &mThresholderParmsM2Wrapper);
   if (aCmd->isCmd("ThresholderM1"))     nestedPush(aCmd, &mThresholderParmsM1Wrapper);
   if (aCmd->isCmd("ThresholderP1"))     nestedPush(aCmd, &mThresholderParmsP1Wrapper);
   if (aCmd->isCmd("ThresholderP2"))     nestedPush(aCmd, &mThresholderParmsP2Wrapper);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace