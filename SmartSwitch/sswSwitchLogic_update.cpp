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
}//namespace