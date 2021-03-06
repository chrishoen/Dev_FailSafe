/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "sswSwitchParms.h"
#include "sswSlowClassifier.h"

namespace SSW
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SlowClassifier::SlowClassifier()
{
   mValue = 0.0;
   mClass = -99;
   mAboveFlagM2 = false;
   mAboveFlagM1 = false;
   mAboveFlagP1 = false;
   mAboveFlagP2 = false;
   mChangeFlagM2 = false;
   mChangeFlagM1 = false;
   mChangeFlagP1 = false;
   mChangeFlagP2 = false;
   mChangeFlag = false;
   mFirstFlag = true;
   mCount = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SlowClassifier::initialize()
{
   mValue = 0.0;
   mClass = -99;
   mLastClass = 0;
   mAboveFlagM2 = false;
   mAboveFlagM1 = false;
   mAboveFlagP1 = false;
   mAboveFlagP2 = false;
   mChangeFlagM2 = false;
   mChangeFlagM1 = false;
   mChangeFlagP1 = false;
   mChangeFlagP2 = false;
   mFirstFlag = true;
   mCount = 0;

   mThresholderM2.initialize(&SSW::gSwitchParms.mThresholderParmsM2);
   mThresholderM1.initialize(&SSW::gSwitchParms.mThresholderParmsM1);
   mThresholderP1.initialize(&SSW::gSwitchParms.mThresholderParmsP1);
   mThresholderP2.initialize(&SSW::gSwitchParms.mThresholderParmsP2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Classify the input variable according to the thresholder bank.
// The change flag is true if the output above flag is different
// from its previous value.

void SlowClassifier::doClassify(
   float  aValue,          // Input
   int&   aClass,          // Output
   bool&  aChangeFlag)     // Output
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Do this first.

   mValue = aValue;
   mLastClass = mClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Thresholder tests.

   // Update the thresholder bank with the input value.
   mThresholderM2.doUpdate(mValue, mAboveFlagM2, mChangeFlagM2);
   mThresholderM1.doUpdate(mValue, mAboveFlagM1, mChangeFlagM1);
   mThresholderP1.doUpdate(mValue, mAboveFlagP1, mChangeFlagP1);
   mThresholderP2.doUpdate(mValue, mAboveFlagP2, mChangeFlagP2);

   // Update the change flag.
   mChangeFlag = mChangeFlagM2 || mChangeFlagM1 || mChangeFlagP1 || mChangeFlagP2;

   // Update the fuzzy confidence.
   mFuzzyConfidence = (
      mThresholderM2.mFuzzyConfidence &&
      mThresholderM1.mFuzzyConfidence &&
      mThresholderP1.mFuzzyConfidence &&
      mThresholderP2.mFuzzyConfidence);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Classify.

   // Classify the input according to the threshold bank test results.
   if (!mAboveFlagM2)
   {
      mClass = -2;
   }
   else if (mAboveFlagM2 && !mAboveFlagM1)
   {
      mClass = -1;
   }
   else if (mAboveFlagM1 && !mAboveFlagP1)
   {
      mClass = 0;
   }
   else if (mAboveFlagP1 && !mAboveFlagP2)
   {
      mClass = 1;
   }
   else if (mAboveFlagP2)
   {
      mClass = 2;
   }
   else
   {
      mClass = -99;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write to output variables.

   mCount++;
   mChangeFlag = mClass != mLastClass;

   aClass = mClass;
   aChangeFlag = mChangeFlag;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a string that can be used for a show.

char* SlowClassifier::asShowString(char* aBuffer)
{
   sprintf(aBuffer, "%4d $ %8.4f $ %6.4f %6.4f %6.4f %6.4f A %6.4f $ %1d %1d %1d %1d $ %1d" ,
      mCount,
      mValue,
      mThresholderM2.mFuzzyConfidence.mX,
      mThresholderM1.mFuzzyConfidence.mX,
      mThresholderP1.mFuzzyConfidence.mX,
      mThresholderP2.mFuzzyConfidence.mX,
      mFuzzyConfidence.mX,
      mAboveFlagM2,
      mAboveFlagM1,
      mAboveFlagP1,
      mAboveFlagP2,
      mClass);

   if (mChangeFlag)
   {
      strcat(aBuffer, " CHANGE");
   }
   
   return aBuffer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace