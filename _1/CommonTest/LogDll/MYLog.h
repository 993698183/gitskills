#pragma once
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
class MYLog
{
public:
	//MYLog();
	//~MYLog();
	~MYLog(void);
	static MYLog * Log();
	bool OpenLogFile(const std::string &sFilePath);
	void Message(const std::string &sFileName, 
		const std::string &sFunc, 
		const long &lLine, 
		const std::string &sMessage);

private:
	static MYLog *m_pInstance;
	MYLog(void);
	void GetNowTime();
	std::ofstream m_fout;
	std::string m_sFilePath;
	std::string m_sNowTiem;
	std::string m_sFileSavePath;
	std::string m_LastDate;
};

