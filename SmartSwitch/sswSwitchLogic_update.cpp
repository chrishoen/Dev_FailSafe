/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "sswSwitchParms.h"
#include "sswSwitchLogic.h"

namespace SSW
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SwitchLogic::SwitchLogic()
{
   mClassA = cClass_None;
   mClassB = cClass_None;
   mClassChangeFlagA = false;
   mClassChangeFlagB = false;
   mClassChangeFlag = false;
   mPathChangeFlag = false;

   mFirstFlag = true;
   mCount = 0;
   mValueA = 0.0;
   mValueB = 0.0;

   mNextPath = 0;
   mCurrentPath = 0;
   mRequestedPath = 0;

   mClassifierA.initialize();
   mClassifierB.initialize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SwitchLogic::initialize()
{
   mClassifierA.initialize();
   mClassifierB.initialize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SwitchLogic::doRequestPathA()
{
   mRequestedPath = cPath_A;
}

void SwitchLogic::doRequestPathB()
{
   mRequestedPath = cPath_B;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************

void SwitchLogic::doUpdateA(float aValue)
{
   mValueA = aValue;
   mClassifierA.doClassify(mValueA, mClassA, mClassChangeFlagA);
   mFuzzyConfidence = mClassifierA.mFuzzyConfidence && mClassifierB.mFuzzyConfidence;
   mClassChangeFlag = mClassChangeFlagA || mClassChangeFlagB;
}

void SwitchLogic::doUpdateB(float aValue)
{
   mValueB = aValue;
   mClassifierB.doClassify(mValueB, mClassB, mClassChangeFlagB);
   mFuzzyConfidence = mClassifierA.mFuzzyConfidence && mClassifierB.mFuzzyConfidence;
   mClassChangeFlag = mClassChangeFlagA || mClassChangeFlagB;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a string that can be used for a show.

char* SwitchLogic::asShowString(char* aBuffer)
{
   sprintf(aBuffer, "%4d    R %1d   F %1d %1d    V %6.4f %6.4f    FL %6.4f %6.4f     CS %2d %2d     P  %1d " ,
      mCount,
      mRequestedPath,
      mAmpFailedA,
      mAmpFailedB,
      mValueA,
      mValueB,
      mClassifierA.mFuzzyConfidence.mX,
      mClassifierB.mFuzzyConfidence.mX,
      mClassA,
      mClassB,
      mCurrentPath);

   if (mAmpFailedA && mAmpFailedPrintCatchA == 0)
   {
      strcat(aBuffer, " AMP A FAILURE");
      mAmpFailedPrintCatchA++;
   }

   if (mAmpFailedB && mAmpFailedPrintCatchB == 0)
   {
      strcat(aBuffer, " AMP B FAILURE");
      mAmpFailedPrintCatchB++;
   }

   if (mClassChangeFlag)
   {
      strcat(aBuffer, " CLASS CHANGE");
   }
   
   if (mPathChangeFlag)
   {
      strcat(aBuffer, " PATH CHANGE");
   }
   mCount++;

   // Done.
   return aBuffer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace