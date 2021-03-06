
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持


#include <afxsock.h>            // MFC 套接字扩展







#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
#pragma comment(lib,"ForceAlphaX.lib")
#pragma comment(lib,"X_Injector_Ex.lib")
#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <future>
#include <sstream>
#include <thread>
#include <fstream>
#include <cstring>
using namespace std;
struct On_RGB
{
	unsigned char RED;
	unsigned char GREEN;
	unsigned char BLUE;
	On_RGB(unsigned char r, unsigned g, unsigned char b) :RED(r), GREEN(g), BLUE(b)
	{
		return;
	}
};
extern "C" _declspec (dllimport) BOOL __stdcall Auto_Inject(const char* Name, const char* dllPath);
extern "C" _declspec (dllimport) BOOL __stdcall Inject_Only(const char* Name, const char* dllPath);
extern "C" _declspec (dllimport) BOOL __stdcall Free_Only(const char* Name, const char* dllPath);
_declspec (dllimport) BOOL __stdcall Handle_Alpha(unsigned char byDw, HANDLE WinH);
_declspec (dllimport) BOOL __stdcall Window_Alpha(unsigned char byDw, HWND WinH);
_declspec (dllimport) BOOL __stdcall On_Pcs_All(unsigned char byDw);
_declspec (dllimport) BOOL __stdcall On_Res_All();
_declspec (dllimport) BOOL __stdcall Handle_Alpha(unsigned char byDw, HANDLE WinH, On_RGB FullColor);
_declspec (dllimport) BOOL __stdcall Window_Alpha(unsigned char byDw, HWND WinH, On_RGB FullColor);