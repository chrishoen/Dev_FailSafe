#include "stdafx.h"

#include "risThreadsProcess.h"

#include "risBaseDir.h"
#include "risPortableCalls.h"
#include "sswSwitchParmsFile.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("SmartSwitch Program********************************************BEGIN\n");
   printf("SmartSwitch Program********************************************BEGIN\n");
   printf("SmartSwitch Program********************************************BEGIN\n\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Set program directory.

   // Set the base directory global variable to the directory path.
   if (Ris::portableIsWindows())
   {
      Ris::setBaseDirectory("c:/aaa_prime/SmartSwitch");
   }
   else
   {
      Ris::setBaseDirectory("/opt/prime");
   }

   // Set the program working directory to the cproc directory path.
   Ris::chdirToBaseDirectory();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Enter process.

   // Set program process for high priority.
   Ris::Threads::enterProcessHigh();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize thread services.

   TS::reset();
   TS::setProgramName("SmartSwitch");
   TS::setProgramPrintLevel(0);
   TS::initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize print facility.

   // Initialize print.
   Prn::resetPrint();
   Prn::useConsole(1);
   Prn::initializePrint();

   // Initialize print filters.
   Prn::setFilter(Prn::View11, true,  1);
   Prn::setFilter(Prn::View12, false, 1);
   Prn::setFilter(Prn::View13, false, 1);
   Prn::setFilter(Prn::View14, false, 1);

   Prn::setFilter(Prn::Show1, true);
   Prn::setFilter(Prn::Show2, true);
   Prn::setFilter(Prn::Show3, false);
   Prn::setFilter(Prn::Show4, false);
   Prn::setFilter(Prn::Show5, false);
   Prn::setFilter(Prn::Show6, false);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   // Read parameters files.
   SSW::gSwitchParmsFile.reset();
   SSW::gSwitchParmsFile.readSection("default");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize program resources.

   Prn::print(Prn::View11,"SmartSwitch Program********************************************BEGIN");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize program resourcs.

void main_finalize()
{
   // Finalize print facility.
   Prn::finalizePrint();

   // Exit process.
   Ris::Threads::exitProcess();

   // Finalize thread services.
   TS::finalize();

   // Done.
   printf("\n");
   printf("SmartSwitch Program********************************************END\n\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
