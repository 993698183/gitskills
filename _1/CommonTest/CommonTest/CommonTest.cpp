// CommonTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//����boost�߳�ʹ�÷�ʽ
#include "boost/thread.hpp"
#include <iostream>
void mythread()
{
	std::cout << "hello thread" << std::endl;
}
//����boost�߳�ʹ�÷�ʽ

//����C++������Dump�ļ�
//#include <imagehlp.h>
//#include <Windows.h>
//LONG WINAPI UnhandledExceptionFilter2(struct _EXCEPTION_POINTERS* ExceptionInfo)
//{
//	string strDumpFile = "exception.dmp ";
//	HANDLE hFile = CreateFile(strDumpFile.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//	if (hFile != INVALID_HANDLE_VALUE)
//	{
//		MINIDUMP_EXCEPTION_INFORMATION ExInfo;
//		ExInfo.ThreadId = ::GetCurrentThreadId();
//		ExInfo.ExceptionPointers = ExceptionInfo;
//		ExInfo.ClientPointers = NULL;
//		// write the dump
//		BOOL bOK = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithFullMemory, &ExInfo, NULL, NULL);
//		CloseHandle(hFile);
//	}
//	return EXCEPTION_EXECUTE_HANDLER;
//}
//����C++������Dump�ļ�

//VC��ȡ�ַ����ȵķ���
#include "string"
#include "comutil.h"
#pragma comment(lib, "comsuppw.lib")
//VC��ȡ�ַ����ȵķ���

//�ж�ָ��Ŀ¼�Ƿ�Ϊ��
#include <boost/system/error_code.hpp>
#include <boost/filesystem.hpp>
bool IsFileExistent(const boost::filesystem::path& path) 
{

	boost::system::error_code error;
	auto file_status = boost::filesystem::status(path, error);
	//if (error) 
	//{
	//	return false;
	//}

	if (!boost::filesystem::exists(file_status))
	{
		return false;
	}

	//if (boost::filesystem::is_directory(file_status)) 
	//{
	//	return false;
	//}

	return true;
}
//�ж�ָ��Ŀ¼�Ƿ�Ϊ��

//boost�߳�
#include <boost/thread.hpp>
void hello()
{
	while (true)
	{
		std::cout << "hello world, i am a thread" << std::endl;
		//Sleep(1000);
		boost::this_thread::sleep(boost::posix_time::seconds(1));
	}
}
//boost�߳�

//boost�ļ�Ŀ¼����
#include <boost/filesystem.hpp>
//boost�ļ�Ŀ¼����

//my_reverse_copy example
#include <iostream>
#include <algorithm>
#include <vector>
void my_reverse_copy()
{
	int myints[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> myvector;
	myvector.resize(9);//����ռ�
	std::reverse_copy(myints, myints + 9, myvector.begin());

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
	{
		std::cout << ' ' << *it;
	}

	std::cout << '\n';
}
//my_reverse_copy example

//my_copy example 
#include <iostream>
#include <algorithm>
#include <vector>
void my_cppy()
{
	int myints[] = { 10, 20, 30, 40, 50, 60, 70 };
	std::vector<int> myvector(7);

	std::copy(myints, myints + 7, myvector.begin());
	std::cout << "myvector contains";

	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
	{
		std::cout << ' ' << *it;
	}
	std::cout << "\n";
}

//my_copy example 

//��֤���ڿ��ַ���ʹ�� boostȥ��ǰ��ո��Ƿ񱨴�����
#include <boost/algorithm/string.hpp>
//��֤���ڿ��ַ���ʹ�� boostȥ��ǰ��ո��Ƿ񱨴�����

//���Թ۲���ģʽ
#include "ObserverPattern.h"
//���Թ۲���ģʽ

//ʱ���ʽ���
void SplitSpring(const std::string &src, const char &csplit, std::vector<std::string> &vResult)
{
	std::string sTemp = "";
	for (unsigned int iIndex = 0; iIndex < src.length(); iIndex++)
	{
		if (src[iIndex] == csplit)
		{
			vResult.push_back(sTemp);
			sTemp = "";
			continue;
		}
		sTemp += src[iIndex];
	}

	if ("" != sTemp)
	{
		vResult.push_back(sTemp);
	}
}

std::string IntToTheString(int &iValue)
{
	char cTemp[100] = {0};
	sprintf_s(cTemp, "%02d", iValue);
	std::string sTemp(cTemp);
	return sTemp;
}
std::string GetAbsolulyTime(const std::string &sLastTime, const int &iAddSeconds)
{
	std::vector<std::string> vResult;
	SplitSpring(sLastTime, ':', vResult);
	if (vResult.size() < 3)
	{
		return sLastTime;
	}
	int iHour = atoi(vResult[0].c_str());
	int iMinite = atoi(vResult[1].c_str());
	int iSecond = atoi(vResult[2].c_str());
	int iAddTime = 0;
	iSecond += iAddSeconds;

	if (iSecond >= 60)
	{
		iAddTime = iSecond / 60;
		iSecond = iSecond % 60;
		iMinite += iAddTime;
		if (iMinite >= 60)
		{
			iAddTime = iMinite / 60;
			iMinite = iMinite % 60;
			iHour += iAddTime;
		}
	}

	std::string sHour = IntToTheString(iHour);
	std::string sMinite = IntToTheString(iMinite);
	std::string sSecond = IntToTheString(iSecond);
	return sHour + ":" + sMinite + ":" + sSecond;
}
//ʱ���ʽ���

//����log��־��̬��
typedef  void(*LOGFUN)(const std::string &sFile, const std::string &sFunc, const long &lLine, const std::string &sMessage);
LOGFUN MYLOG;
//typedef void (*LOGFUN)(const string &sFunc,const string &sMessage);
//extern LOGFUN MYLOG;
void FuncB()
{
	MYLOG(__FILE__, __FUNCTION__, __LINE__, "It is in FuncB");
}
//����log��־��̬��

//Windows��Event���
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
//ͨ���¼���֪��һ���̵߳�״̬
//���磺�߳���������״̬���𴲡��Է����ϰ�
HANDLE g_getupHandle;
HANDLE g_breakfastHandle;
HANDLE g_workHandle;

std::vector<std::string> stateTexts;
DWORD WINAPI Worker(LPVOID n)
{
	stateTexts.push_back("GetUp");
	SetEvent(g_getupHandle);
	stateTexts.push_back("Breakfast");
	SetEvent(g_breakfastHandle);
	stateTexts.push_back("Work");
	SetEvent(g_workHandle);

	return 0;
}
//Windows��Event���

//�����⣺��������ַ���������ͬ���ַ�
#include <iostream>
void FindCommonChar(char a[], int lena, char b[], int lenb)
{
	int hasha[256] = { 0 };
	int hashb[256] = { 0 };
	for (int i = 0; i < lena; i++)
	{
		hasha[(int)a[i]] = 1;
	}

	for (int j = 0; j < lena; j++)
	{
		hashb[(int)b[j]] = 1;
	}

	for (int i = 0; i < 256; i++)
	{
		if (hasha[i] ==1 && hashb[i] == 1)
		{
			std::cout << (char)i << std::endl;
		}
	}
}
//�����⣺��������ַ���������ͬ���ַ�

//C++���ú궨��
#include <stdio.h>
//C++���ú궨��

//boost::filesystem::is_directory�쳣����
#include <iostream>
#include <boost/filesystem.hpp>
//boost::filesystem::is_directory�쳣����

//mystringToi��mystringTofloat
bool isNumericChar(char x)
{
	return (x >= '0' && x <= '9') ? true : false;
}
int string2i(char *str)
{
	if (*str == NULL)
	{
		return 0;
	}

	int res = 0;
	int sign = 1;
	int i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}

	for (; str[i] != '\0'; ++i)
	{
		if (isNumericChar(str[i]) == false)
		{
			return 0;
		}
		res = res * 10 + str[i] - '0';
	}

	return sign*res;
}

float string2float(const char* s) 
{
	float rez = 0, fact = 1;
	if (*s == '-') 
	{
		s++;
		fact = -1;
	}
	for (int point_seen = 0; *s; s++) 
	{
		if (*s == '.') 
		{
			point_seen = 1;
			continue;
		}
		int d = *s - '0';
		if (d >= 0 && d <= 9) 
		{
			if (point_seen) fact /= 10.0f;
			rez = rez * 10.0f + (float)d;
		}
	}
	return rez * fact;
};
//mystringToi��mystringTofloat

//string��c_str()������data()����
#include <iostream>
#include <string>
//string��c_str()������data()����

//�Լ���log��־����
#include <iostream>
#include <string>
#include <vector>
#define DEBUG_LOG(...) debug_log("DEBUG", __TIME__, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
void debug_log(
	const char *loglevel,
	const char *time,
	const char *file,
	const char *func,
	const int iline,
	const char *format,...
)
{
	static char output[10240] = { 0 };
	va_list arglist;
	va_start(arglist, format);
	vsnprintf(output, sizeof(output), format, arglist);
	printf("[%s][%s][%s][%s][%d]:%s\n", time, loglevel, file, func, iline, output);
	//�˴���Ƶ�����ļ�
	FILE *fp = NULL;
	fopen_s(&fp, "d:\\logfile.txt", "a+");//
	fprintf_s(fp, "[%s][%s][%s][%s][%d]:%s\n", time, loglevel, file, func, iline, output);
	fclose(fp);
	va_end(arglist);
}
//�Լ���log��־����
int main()
{
	//�Լ���log��־����
	if (1)
	{
		DEBUG_LOG("%s, ranking NO.%d", "You are so smart", 1);
		system("pause");
	}
	//�Լ���log��־����

	//string��c_str()������data()����
	//1. c_str()������һ��const char*ָ�룬ָ���Կ��ַ���ֹ�����顣
	//2. data():��c_str()���ƣ����Ƿ��ص����鲻�Կ��ַ���ֹ��
	if (0)
	{
		std::string s = "12345";
		char test[10] = { 0 };
		strncpy_s(test, s.c_str(), 6);
		char test1[10] = { 0 };
		strncpy_s(test1, s.data(), 6);
		system("pause");
	}
	//string��c_str()������data()����

	//mystringToi��mystringTofloat
	if (1)
	{
		char* p1 = "123";
		std::cout << string2i(p1) << std::endl;
		char* p2 = "123.333";
		std::cout << string2float(p2) << std::endl;
	}
	//mystringToi��mystringTofloat

	//boost::filesystem::is_directory�쳣����
	if (0)
	{
		/*boost::filesystem::path p("C:\OneDriveTemp\S-1-5-21-3878404667-799272800-635255798-1001");
		try
		{
			boost::filesystem::is_directory(p);
		}
		catch (const boost::filesystem::filesystem_error& e)
		{
			if (e.code() == boost::system::errc::permission_denied)
			{
				std::cout << "Search permission is denied for one of the directories "
					<< "in the path prefix of " << p << "\n";
			}
			else
			{
				std::cout << "is_directory(" << p << ") failed with "
					<< e.code().message() << '\n';
			}
		}*/
	}
	//boost::filesystem::is_directory�쳣����

	//C++���ú궨��
	if (0)
	{
		printf("��ǰԴ���뺯������__FUNCTION__==%s\n", __FUNCTION__);
		printf("��ǰԴ�����кţ�__LINE__==%d\n", __LINE__);
		printf("��ǰԴ�����ļ�����__FILE__==%s\n", __FILE__);
		printf("��ǰ�������ڡ�ע��͵�ǰϵͳ������������:__DATE__==%s\n", __DATE__);
		printf("��ǰ����ʱ�䡲ע��͵�ǰϵͳ������������:__TIME__==%s\n", __TIME__);
		printf("��ǰϵͳʱ�����__TIMESTAMP__==%s\n", __TIMESTAMP__);
		//printf("��Ҫ������ϸ���ѭANSIC��׼ʱ�ñ�ʶ������ֵΪ1:__STDC__==%d\n", __STDC__);
		printf("����C++����������ʱ����ʶ��__cplusplus�ͻᱻ����:__cplusplus==%d\n", __cplusplus);
		system("pause");
	}
	//C++���ú궨��

	//�����⣺��������ַ���������ͬ���ַ�
	if (0)
	{
		char a[5] = { '1', 'b', 'C', 'f', 'f' };
		char b[6] = { '1', 'b', 'd', 'e', 'C','d' };
		FindCommonChar(a, _countof(a), b, _countof(b));
		system("pause");
	}
	//�����⣺��������ַ���������ͬ���ַ�

	//Windows��Event���
	if (0)
	{
		stateTexts.reserve(3);//����Ԥ���ռ�
		g_getupHandle = CreateEventA(NULL, true, false, NULL);//�ֶ������ź�
		g_breakfastHandle = CreateEventA(NULL, true, false, NULL);//�ֶ������ź�
		g_workHandle = CreateEventA(NULL, true, false, NULL);//�ֶ������ź�

		DWORD threadId;
		HANDLE theadHandle = CreateThread(NULL,
			0,
			Worker,
			0,
			0,
			&threadId
			);

		WaitForSingleObject(g_getupHandle, INFINITE);
		std::cout << stateTexts[0] << std::endl;

		WaitForSingleObject(g_breakfastHandle, 3000);
		std::cout << stateTexts[1] << std::endl;

		WaitForSingleObject(g_workHandle, INFINITE);
		std::cout << stateTexts[2] << std::endl;

		CloseHandle(theadHandle);
		CloseHandle(g_getupHandle);
		CloseHandle(g_breakfastHandle);
		CloseHandle(g_workHandle);

		system("pause");
	}
	//Windows��Event���

	//����log��־��̬��
	if (0)
	{
		char c;
		HINSTANCE hInput;
		hInput = LoadLibrary(_T("LogDll.dll"));
		if (NULL == hInput)
		{
			std::cout << "load failed" << std::endl;
			c = getchar();
			return -1;
		}
		typedef bool(*FUNC)(const std::string &sFilePath);
		FUNC fun = (FUNC)GetProcAddress(hInput, "LogPath");
		if (NULL == fun)
		{
			std::cout << "load function failed" << std::endl;
			c = getchar();
			return -1;
		}
		bool iResult = fun("D://");
		std::cout << "result is" << iResult << std::endl;

		MYLOG = (LOGFUN)GetProcAddress(hInput, "WRITELOG");
		if (NULL == MYLOG)
		{
			std::cout << "load function failed" << std::endl;
			c = getchar();
			return -1;
		}
		while (true)
		{
			std::cout << "wrtite..." << std::endl;
			MYLOG(__FILE__, __FUNCTION__, __LINE__, "This is a test");
			FuncB();
			Sleep(5000);
		}
		c = getchar();
	}
	//����log��־��̬��

	if (0)
	{
		std::string sTest = "00:00:00";
		std::string sResult;
		while (true)
		{
			sTest = GetAbsolulyTime(sTest, 80);
			Sleep(1000);
			std::cout << "Time is" << sTest << std::endl;
		}
	}

	if (0)
	{
		std::string str("1111�½��ļ���");
		std::size_t nlength = strlen(str.c_str());
		std::size_t nlength2 = str.length();

		char cztmp[MAX_PATH] = {0};
		memcpy(cztmp, str.c_str(), nlength2);
		system("Pause");
	}
	if (0)
	{
		testObserverPattern();
	}
	if (0)
	{
		std::string str1(" 11111 ");
		boost::trim(str1);
		std::string str2("");
		boost::trim(str2);
		getchar();
	}
	if (0)
	{
		int i = 0;
		i = 1 << i;
	}
	if (0)
	{
		my_cppy();
		getchar();
	}
	if (0)
	{
		my_reverse_copy();
		getchar();
	}
	if (0)
	{
		TCHAR szCurPath[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, szCurPath, MAX_PATH);
		std::wstring wstrpath(szCurPath);
		boost::filesystem::path path_send(wstrpath);
		boost::filesystem::path path_send_monitor(path_send.parent_path().wstring() + _T("\\send"));
		path_send = path_send.filename();
		path_send_monitor /= path_send;
	}

	if (0)
	{
		std::string str("11111_sql.xml");
		int pos = str.find("_sql_");
		if (0 == pos)
		{
			int i = 0;
		}
	}
	//std::string��compar������ʹ��
	if (0)
	{
		std::string str("0");
		std::string str2("1");
		int nret = str.compare(std::string("1").c_str());
		if (nret)
		{
			int a = 0;
		}
	}
	if (0)
	{
		//boost�߳�
		boost::thread thrd(&hello);
		thrd.join();
		getchar();
	}
	if (0)
	{
		//�ж�ָ��Ŀ¼�Ƿ�Ϊ��
		std::string str(("C:\\Users\\waction\\Desktop\\1\\*.*"));
		bool ret = IsFileExistent(str.c_str());
	}
	if (0)
	{
		//VC��ȡ�ַ����ȵķ���
		char s1[] = "����ABC";
		wchar_t s2[] = L"����ABC";

		//ʹ��sizeof��ȡ�ַ�������
		printf("sizeof s1: %d\r\n", sizeof(s1));
		printf("sizeof s2: %d\r\n", sizeof(s2));

		//ʹ��strlen��ȡ�ַ�������
		printf("strlen(s1): %d\r\n", strlen(s1));
		printf("wcslen(s2): %d\r\n", wcslen(s2));

		//ʹ��CString::GetLength()��ȡ�ַ�������
		//CStringA sa = s1;
		//CStringW sw = s2;
		//printf("sa.GetLength(): %d\r\n", sa.GetLength());
		//printf("sw.GetLength(): %d\r\n", sw.GetLength());
		//ʹ��string::size()��ȡ�ַ�������
		std::string ss1 = s1;
		std::wstring ss2 = s2;printf("ss1.size(): %d\r\n", ss1.size());
		printf("ss2.size(): %d\r\n", ss2.size());
		//ʹ��_bstr_t::length()��ȡ�ַ�������
		_bstr_t bs1(s1);
		_bstr_t bs2(s2);
		printf("bs1.length(): %d\r\n", bs1.length());
		printf("bs2.length(): %d\r\n", bs2.length());
		getchar();
	}
	if (0)
	{
		//����C++������Dump�ļ�
		//SetUnhandledExceptionFilter(UnhandledExceptionFilter2);
	}
	if (0)
	{
		//����boost�߳�ʹ�÷�ʽ
		boost::function<void()>f(mythread);
		boost::thread t(f);
		t.join();
		std::cout << "thread is over" << std::endl;
		getchar();
	}

    return 0;
}

