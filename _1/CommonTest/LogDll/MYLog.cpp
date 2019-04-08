#include "stdafx.h"
#include "MYLog.h"
#include <time.h>

//单例静态指针初始化
MYLog *  MYLog::m_pInstance = new MYLog();
/***********************************
此函数不会被调用
***********************************/
MYLog::MYLog(void)
{
}
/***********************************
析构单例指针
***********************************/
MYLog::~MYLog(void)
{
	if (NULL != m_pInstance)
	{
		delete m_pInstance;
	}
	m_fout.close();
}
/***********************************
获得单例实例
***********************************/
MYLog * MYLog::Log()
{
	return m_pInstance;
}
/***********************************
打开Log文件
***********************************/
bool MYLog::OpenLogFile(const std::string &sFilePath)
{
	if (true == m_fout.is_open())
	{
		m_fout.close();
	}
	m_sFileSavePath = sFilePath;
	if (m_sFileSavePath.find_last_of("\\") != m_sFileSavePath.length() - 1 
		&& m_sFileSavePath.find_last_of("/") != m_sFileSavePath.length() - 1)
	{
		m_sFileSavePath += "/";
	}
	time_t t = time(0);
	//struct tm *now_time = NULL;
	struct tm now_time;
	localtime_s(&now_time, &t);
	char tmp[64] = { 0 };
	strftime(tmp, sizeof(tmp), "%Y-%m-%d", &now_time);

	std::string sTemp = tmp;
	m_LastDate = tmp;
	m_sFilePath = m_sFileSavePath + sTemp + ".txt";
	m_fout.open(m_sFilePath.c_str(), std::ios::app);
	if (!m_fout)
	{
		return false;
	}
	return true;
}
/**********************************
获取当前时间
**********************************/
void  MYLog::GetNowTime()
{
	time_t t = time(0);
	struct tm now_time;
	localtime_s(&now_time, &t);

	char tmp[64] = {0};
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X ", &now_time);
	m_sNowTiem = tmp;
	localtime_s(&now_time, &t);
	strftime(tmp, sizeof(tmp), "%Y-%m-%d", &now_time);
	std::string sData = tmp;
	if (sData != m_LastDate)
	{
		OpenLogFile(m_sFileSavePath);
	}
}

/***********************************
将信息写入Log文件
***********************************/
void MYLog::Message(const std::string &sFile, const std::string &sFunc, const long &lLine, const std::string &sMessage)
{
	GetNowTime();

	std::string sFileName = sFile;
	sFileName = sFileName.substr(sFileName.find_last_of("\\") + 1, 
		sFileName.length() - sFileName.find_last_of("\\") - 1);

	m_fout << m_sNowTiem.c_str() << " FILE: " << sFileName.c_str() << "   FUNC: " << sFunc.c_str() << "  LINE: " << lLine << "   MES: " << sMessage.c_str() << std::endl;
	m_fout.flush();
}