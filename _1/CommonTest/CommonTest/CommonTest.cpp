// CommonTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//测试boost线程使用方式
#include "boost/thread.hpp"
#include <iostream>
void mythread()
{
	std::cout << "hello thread" << std::endl;
}
//测试boost线程使用方式

//测试C++下生成Dump文件
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
//测试C++下生成Dump文件

//VC获取字符长度的方法
#include "string"
#include "comutil.h"
#pragma comment(lib, "comsuppw.lib")
//VC获取字符长度的方法

//判断指定目录是否为空
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
//判断指定目录是否为空

//boost线程
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
//boost线程

//boost文件目录操作
#include <boost/filesystem.hpp>
//boost文件目录操作

//my_reverse_copy example
#include <iostream>
#include <algorithm>
#include <vector>
void my_reverse_copy()
{
	int myints[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> myvector;
	myvector.resize(9);//申请空间
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

//验证对于空字符串使用 boost去掉前后空格是否报错问题
#include <boost/algorithm/string.hpp>
//验证对于空字符串使用 boost去掉前后空格是否报错问题

//测试观察者模式
#include "ObserverPattern.h"
//测试观察者模式

//时间格式输出
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
//时间格式输出

//调用log日志动态库
typedef  void(*LOGFUN)(const std::string &sFile, const std::string &sFunc, const long &lLine, const std::string &sMessage);
LOGFUN MYLOG;
//typedef void (*LOGFUN)(const string &sFunc,const string &sMessage);
//extern LOGFUN MYLOG;
void FuncB()
{
	MYLOG(__FILE__, __FUNCTION__, __LINE__, "It is in FuncB");
}
//调用log日志动态库

//Windows的Event编程
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
//通过事件得知另一个线程的状态
//例如：线程中有三种状态：起床、吃饭、上班
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
//Windows的Event编程

//面试题：输出两个字符数组中相同的字符
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
//面试题：输出两个字符数组中相同的字符

//C++常用宏定义
#include <stdio.h>
//C++常用宏定义

//boost::filesystem::is_directory异常捕获
#include <iostream>
#include <boost/filesystem.hpp>
//boost::filesystem::is_directory异常捕获

//mystringToi和mystringTofloat
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
//mystringToi和mystringTofloat

//string的c_str()函数和data()函数
#include <iostream>
#include <string>
//string的c_str()函数和data()函数

//自己的log日志功能
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
	//此处会频繁打开文件
	FILE *fp = NULL;
	fopen_s(&fp, "d:\\logfile.txt", "a+");//
	fprintf_s(fp, "[%s][%s][%s][%s][%d]:%s\n", time, loglevel, file, func, iline, output);
	fclose(fp);
	va_end(arglist);
}
//自己的log日志功能
int main()
{
	//自己的log日志功能
	if (1)
	{
		DEBUG_LOG("%s, ranking NO.%d", "You are so smart", 1);
		system("pause");
	}
	//自己的log日志功能

	//string的c_str()函数和data()函数
	//1. c_str()：生成一个const char*指针，指向以空字符终止的数组。
	//2. data():与c_str()类似，但是返回的数组不以空字符终止。
	if (0)
	{
		std::string s = "12345";
		char test[10] = { 0 };
		strncpy_s(test, s.c_str(), 6);
		char test1[10] = { 0 };
		strncpy_s(test1, s.data(), 6);
		system("pause");
	}
	//string的c_str()函数和data()函数

	//mystringToi和mystringTofloat
	if (1)
	{
		char* p1 = "123";
		std::cout << string2i(p1) << std::endl;
		char* p2 = "123.333";
		std::cout << string2float(p2) << std::endl;
	}
	//mystringToi和mystringTofloat

	//boost::filesystem::is_directory异常捕获
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
	//boost::filesystem::is_directory异常捕获

	//C++常用宏定义
	if (0)
	{
		printf("当前源代码函数名：__FUNCTION__==%s\n", __FUNCTION__);
		printf("当前源代码行号：__LINE__==%d\n", __LINE__);
		printf("当前源代码文件名：__FILE__==%s\n", __FILE__);
		printf("当前编译日期〔注意和当前系统日期区别开来〕:__DATE__==%s\n", __DATE__);
		printf("当前编译时间〔注意和当前系统日期区别开来〕:__TIME__==%s\n", __TIME__);
		printf("当前系统时间戳：__TIMESTAMP__==%s\n", __TIMESTAMP__);
		//printf("当要求程序严格遵循ANSIC标准时该标识符被赋值为1:__STDC__==%d\n", __STDC__);
		printf("当用C++编译程序编译时，标识符__cplusplus就会被定义:__cplusplus==%d\n", __cplusplus);
		system("pause");
	}
	//C++常用宏定义

	//面试题：输出两个字符数组中相同的字符
	if (0)
	{
		char a[5] = { '1', 'b', 'C', 'f', 'f' };
		char b[6] = { '1', 'b', 'd', 'e', 'C','d' };
		FindCommonChar(a, _countof(a), b, _countof(b));
		system("pause");
	}
	//面试题：输出两个字符数组中相同的字符

	//Windows的Event编程
	if (0)
	{
		stateTexts.reserve(3);//容器预留空间
		g_getupHandle = CreateEventA(NULL, true, false, NULL);//手动，无信号
		g_breakfastHandle = CreateEventA(NULL, true, false, NULL);//手动，无信号
		g_workHandle = CreateEventA(NULL, true, false, NULL);//手动，无信号

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
	//Windows的Event编程

	//调用log日志动态库
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
	//调用log日志动态库

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
		std::string str("1111新建文件夹");
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
	//std::string的compar函数的使用
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
		//boost线程
		boost::thread thrd(&hello);
		thrd.join();
		getchar();
	}
	if (0)
	{
		//判断指定目录是否为空
		std::string str(("C:\\Users\\waction\\Desktop\\1\\*.*"));
		bool ret = IsFileExistent(str.c_str());
	}
	if (0)
	{
		//VC获取字符长度的方法
		char s1[] = "中文ABC";
		wchar_t s2[] = L"中文ABC";

		//使用sizeof获取字符串长度
		printf("sizeof s1: %d\r\n", sizeof(s1));
		printf("sizeof s2: %d\r\n", sizeof(s2));

		//使用strlen获取字符串长度
		printf("strlen(s1): %d\r\n", strlen(s1));
		printf("wcslen(s2): %d\r\n", wcslen(s2));

		//使用CString::GetLength()获取字符串长度
		//CStringA sa = s1;
		//CStringW sw = s2;
		//printf("sa.GetLength(): %d\r\n", sa.GetLength());
		//printf("sw.GetLength(): %d\r\n", sw.GetLength());
		//使用string::size()获取字符串长度
		std::string ss1 = s1;
		std::wstring ss2 = s2;printf("ss1.size(): %d\r\n", ss1.size());
		printf("ss2.size(): %d\r\n", ss2.size());
		//使用_bstr_t::length()获取字符串长度
		_bstr_t bs1(s1);
		_bstr_t bs2(s2);
		printf("bs1.length(): %d\r\n", bs1.length());
		printf("bs2.length(): %d\r\n", bs2.length());
		getchar();
	}
	if (0)
	{
		//测试C++下生成Dump文件
		//SetUnhandledExceptionFilter(UnhandledExceptionFilter2);
	}
	if (0)
	{
		//测试boost线程使用方式
		boost::function<void()>f(mythread);
		boost::thread t(f);
		t.join();
		std::cout << "thread is over" << std::endl;
		getchar();
	}

    return 0;
}

