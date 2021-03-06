#pragma once

/*==============================================================================
Slow classifier example class
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "sswSlowClassifier.h"

namespace SSW
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that implments a slow classifier. It addresses the problem
// of threshold classification of a noisy variable that varies over time.
// 
//

class SwitchLogic
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   // Alarm classifications.
   static const int cClass_None       = -99;
   static const int cClass_CriticalLo = -2;
   static const int cClass_AlarmLo    = -1;
   static const int cClass_Nominal    =  0;
   static const int cClass_AlarmHi    =  1;
   static const int cClass_CriticalHi =  2;

   // Amplifier path selections.
   static const int cPath_A      = 0;
   static const int cPath_B      = 1;
   static const int cPath_Bypass = 2;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Input values.
   float mValueA;
   float mValueB;

   // Slow classifiers.
   SlowClassifier mClassifierA;
   SlowClassifier mClassifierB;

   // Classifications. Class. This is one of -2,-1,0,1,2.
   int mClassA;
   int mClassB;

   // Classifier change flags
   bool mClassChangeFlagA;
   bool mClassChangeFlagB;
   bool mClassChangeFlag;
   bool mPathChangeFlag;

   // Failed Amplifier Flags (Latched in logic rules)
   bool mAmpFailedA = 0;
   bool mAmpFailedB = 0;

   // variables used to print once upon amp failure
   bool mAmpFailedPrintCatchA = 0;
   bool mAmpFailedPrintCatchB = 0;

   // Fuzzy boolean variable. this is the AND of the fuzzy confidence
   // vararables for all of the thresholders.
   // the measurements.
   Dsp::FuzzyBoolFloat mFuzzyConfidence;

   // True if first update after initialization.
   bool mFirstFlag;

   // Update counter.
   int mCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Path variables.
   int mCurrentPath;
   int mNextPath;
   int mRequestedPath;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SwitchLogic();
   void initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   void doRequestPathA();
   void doRequestPathB();

   void doUpdateA(float aValue);
   void doUpdateB(float aValue);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.
   void checkAmpFail();
   void doEvaluateRules();
   void doEvaluateSwitch();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Return a string that can be used for a show.
   char* asShowString(char* aBuffer);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


