/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "sswSwitchParmsFile.h"
#include "sswSwitchParms.h"

#define  _AUTOTIMERTHREAD_CPP_
#include "sswTimerThread.h"


namespace SSW
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

TimerThread::TimerThread()
{
   // Set base class variables.
   BaseClass::setThreadName("Timer");
   BaseClass::setThreadPrintLevel(0);

   // Set base class variables.
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mTimerTest);

   // Set timer period.
   BaseClass::mTimerPeriod = SSW::gSwitchParmsFile.mTimerPeriod;

   // Initialize variables.
   mSuspendFlag = false;
   mValueA = SSW::gSwitchParmsFile.mInitialValueA;
   mValueB = SSW::gSwitchParmsFile.mInitialValueB;
   mValueAPN = mValueA;
   mValueBPN = mValueB;
   mDeltaA = 0.0;
   mDeltaB = 0.0;
   mNoiseRequestFlag = false;
   mNoiseSigma = 0.0;
   mNoise = 0.0;
   mRequestedPath = 0;

   mClassifier.initialize();
   mSwitchLogic.initialize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TimerThread::threadInitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TimerThread::executeOnTimer(int aTimeCount)
{
   // Guard.
   if (mSuspendFlag) return;

   // Update the simulated input value.
   doUpdateValue();

   // Test something.
   if (gSwitchParmsFile.mTestMode == 1)
   {
      // Update the classifier.
      int  tClass = -99;
      bool tChangeFlag = false;
      mClassifier.doClassify(mValueAPN, tClass, tChangeFlag);
      char tBuffer[200];
      Prn::print(Prn::View11, "%s", mClassifier.asShowString(tBuffer));
   }
   else // if testMode != 1
   {
      if (mRequestedPath == 0)  mSwitchLogic.doRequestPathA();
      else mSwitchLogic.doRequestPathB();
      mSwitchLogic.doUpdateA(mValueAPN);
      mSwitchLogic.doUpdateB(mValueBPN);
      mSwitchLogic.checkAmpFail(); // new latch function to catch failed amps
      mSwitchLogic.doEvaluateRules();
      mSwitchLogic.doEvaluateSwitch();
      mSwitchLogic.show();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update the simulated input value.

void TimerThread::doUpdateValue()
{
   // If there is a request for gaussian noise then initialize the gaussian
   // noise generator.
   if (mNoiseRequestFlag)
   {
      mNoiseRequestFlag = false;
      mGaussNoise.initialize(mNoiseSigma);
   }
      
   // Get from the noise generator.

   // Update the input value.
   mValueA += mDeltaA;
   mValueB += mDeltaB;

   // Add some noise.
   mNoise = (float)mGaussNoise.getNoise();
   mValueAPN = mValueA + mNoise;
   mNoise = (float)mGaussNoise.getNoise();
   mValueBPN = mValueB + mNoise;
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace