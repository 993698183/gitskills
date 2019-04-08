// LogDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "LogDll.h"


// This is an example of an exported variable
LOGDLL_API int nLogDll=0;

// This is an example of an exported function.
LOGDLL_API int fnLogDll(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see LogDll.h for the class definition
CLogDll::CLogDll()
{
    return;
}
