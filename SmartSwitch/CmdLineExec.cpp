#include "stdafx.h"


#include "CmdLineExec.h"

#include "risThreadsThreads.h"
#include "risTimeMarker.h"

#include "sswSwitchParmsFile.h"

#include "sswTimerThread.h"
using namespace SSW;

//******************************************************************************
//******************************************************************************
//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("S"))     gTimerThread->mSuspendFlag = true;
   if (aCmd->isCmd("R"))     gTimerThread->mSuspendFlag = false;
   if (aCmd->isCmd("VALA"))  executeValueA(aCmd);
   if (aCmd->isCmd("DELA"))  executeDeltaA(aCmd);
   if (aCmd->isCmd("VALB"))  executeValueB(aCmd);
   if (aCmd->isCmd("DELB"))  executeDeltaB(aCmd);
   if (aCmd->isCmd("Noise")) executeNoise(aCmd);
   if (aCmd->isCmd("GO1"))   executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))   executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))   executeGo3(aCmd);
   if (aCmd->isCmd("PARMS")) executeParms(aCmd);
   if (aCmd->isCmd("REQA"))  executeReqA(aCmd);
   if (aCmd->isCmd("REQB"))  executeReqB(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeValueA(Ris::CmdLineCmd* aCmd)
{
   gTimerThread->mValueA = aCmd->argFloat(1);
   gTimerThread->mDeltaA = aCmd->argFloat(2);
}

void CmdLineExec::executeValueB(Ris::CmdLineCmd* aCmd)
{
   gTimerThread->mValueB = aCmd->argFloat(1);
   gTimerThread->mDeltaB = aCmd->argFloat(2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDeltaA(Ris::CmdLineCmd* aCmd)
{
   gTimerThread->mDeltaA = aCmd->argFloat(1);
}

void CmdLineExec::executeDeltaB(Ris::CmdLineCmd* aCmd)
{
   gTimerThread->mDeltaB = aCmd->argFloat(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeNoise(Ris::CmdLineCmd* aCmd)
{
   gTimerThread->mNoiseSigma = aCmd->argFloat(1);
   gTimerThread->mNoiseRequestFlag = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1 (Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2 (Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3 (Ris::CmdLineCmd* aCmd)
{
}


void CmdLineExec::executeReqA(Ris::CmdLineCmd* aCmd)
{
   // Set requested path to A.
   gTimerThread->mRequestedPath = 0;

}

void CmdLineExec::executeReqB(Ris::CmdLineCmd* aCmd)
{
   // Set requested path to B.
   gTimerThread->mRequestedPath = 1;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************


void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   SSW::gSwitchParmsFile.reset();
   SSW::gSwitchParmsFile.readSection("default");
   SSW::gSwitchParmsFile.show();
}