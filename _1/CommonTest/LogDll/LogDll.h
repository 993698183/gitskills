// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LOGDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LOGDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LOGDLL_EXPORTS
#define LOGDLL_API __declspec(dllexport)
#else
#define LOGDLL_API __declspec(dllimport)
#endif

#include "MYLog.h"
// This class is exported from the LogDll.dll
class LOGDLL_API CLogDll {
public:
	CLogDll(void);
	// TODO: add your methods here.
};

extern "C" _declspec(dllexport) bool LogPath(const std::string &sFilePath)
{
	bool isSucess = MYLog::Log()->OpenLogFile(sFilePath);
	return isSucess;
}
extern "C" _declspec(dllexport) void WRITELOG(const std::string &sFile, 
	const std::string &sFunc, 
	const long &lLine, const std::string &sMessage)
{
	MYLog::Log()->Message(sFile, sFunc, lLine, sMessage);
}

extern LOGDLL_API int nLogDll;

LOGDLL_API int fnLogDll(void);
