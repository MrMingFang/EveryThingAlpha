
// EveryThingAlphaDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "EveryThingAlpha.h"
#include "EveryThingAlphaDlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma warning (disable : 4996)
#define LIMITED



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEveryThingAlphaDlg 对话框



CEveryThingAlphaDlg::CEveryThingAlphaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_EVERYTHINGALPHA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CEveryThingAlphaDlg::MSGBOX(const char * MSG)
{
	MessageBox(MSG, "EveryThingAlpha Ex", MB_OK);
	return;
}

void CEveryThingAlphaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CEveryThingAlphaDlg::PreTranslateMessage(MSG * pMsg)
{
	//屏蔽ESC关闭窗体/
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	//屏蔽回车关闭窗体,但会导致回车在窗体上失效.
	//if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN && pMsg->wParam) return TRUE;
	else
		return CDialog::PreTranslateMessage(pMsg);
}

void CEveryThingAlphaDlg::LogFile(string ToLog)
{
	ofstream Ep("evtAlpha.log", ios::out | ios::app);
	if (!Ep)
	{
		Ep.close();
		Ep.clear();
		return;
	}
	else
	{
	}
	auto tt = std::chrono::system_clock::to_time_t
	(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	Ep << "::Log from Program On Time: " << ptm->tm_year + 1900 << " Years " << ptm->tm_mon + 1 << " Month " << ptm->tm_mday << " Days " << ptm->tm_hour << ":" << ptm->tm_min << endl;
	Ep << "Program Log-> " << ToLog << endl;
	Ep.close();
	Ep.clear();
	return;
}

HANDLE CEveryThingAlphaDlg::GetProcessByName(string namex)
{
	EnableDebugPriv();
	DWORD pid = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);
	if (Process32First(snapshot, &process))
	{
		do
		{
			if (_stricmp(process.szExeFile, namex.c_str()) == 0)
			{
				pid = process.th32ProcessID;
				break;
			}
		} while (Process32Next(snapshot, &process));
	}
	CloseHandle(snapshot);
	if (pid != 0)
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		return hProcess;
	}
	return NULL;
}

BOOL CEveryThingAlphaDlg::IsWow64ProcessEx(HANDLE hProcess)
{
	// 如果系统是x86的，那么进程就不可能有x64  
	LogFile("Checking Program bit features");
	bool isX86 = false;
#ifndef _WIN64  
	isX86 = GetProcAddress(GetModuleHandle(TEXT("ntdll")), "NtWow64DebuggerCall") == nullptr ? TRUE : FALSE;
#endif  
	if (isX86)
		return FALSE;
	// 进程架构未知，系统是x64的，可以利用IsWow64Process函数判断  
	typedef BOOL(WINAPI *ISWOW64PROCESS)(HANDLE, PBOOL);
	ISWOW64PROCESS fnIsWow64Process;
	BOOL isWow64 = TRUE;
	fnIsWow64Process = (ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");
	if (fnIsWow64Process != nullptr)
		fnIsWow64Process(hProcess, &isWow64);
	return !isWow64;
}

void CEveryThingAlphaDlg::EnableDebugPriv()
{
	LogFile("Get permission.");
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkp;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = luid;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, false, &tkp, sizeof(tkp), NULL, NULL);
	CloseHandle(hToken);
}

BEGIN_MESSAGE_MAP(CEveryThingAlphaDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_OPTIONS_EXIT, &CEveryThingAlphaDlg::OnOptionsExit)
	ON_COMMAND(ID_OPTIONS_SETTINGS, &CEveryThingAlphaDlg::OnOptionsSettings)
	ON_COMMAND(ID_ABOUT_EVERYTHINGALP, &CEveryThingAlphaDlg::OnAboutEverythingalp)
	ON_COMMAND(ID_ABOUT_SAURIK, &CEveryThingAlphaDlg::OnAboutSaurik)
	ON_COMMAND(ID_ABOUT_32775, &CEveryThingAlphaDlg::OnAbout32775)
	ON_BN_CLICKED(IDC_BUTTON1, &CEveryThingAlphaDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CEveryThingAlphaDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CEveryThingAlphaDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CEveryThingAlphaDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CEveryThingAlphaDlg::OnBnClickedButton5)
	ON_COMMAND(ID_OPTIONS_TOPMOST, &CEveryThingAlphaDlg::OnOptionsTopmost)
	ON_COMMAND(ID_CLICKANDTRANSPARENT_CLICKSOMEWHEREANDTRANSPARENTIT, &CEveryThingAlphaDlg::OnClickandtransparentClicksomewhereandtransparentit)
END_MESSAGE_MAP()


// CEveryThingAlphaDlg 消息处理程序

BOOL CEveryThingAlphaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ofstream Ep("evtAlpha.log", ios::out);
	Ep.close();
	Ep.clear();
	LogFile("Program start!");

	// 是否有时间限制。
#ifdef LIMITED
	auto tt = std::chrono::system_clock::to_time_t
	(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	if (((int)ptm->tm_year + 1900) >= 2019 && ((int)ptm->tm_mon + 1) > 6)
	{
		MessageBoxA("Out of date", "Sorfware Error", MB_OK);
		ExitProcess(-1);
	}
#endif


	CMenu TheMENUX;
	TheMENUX.LoadMenu(IDR_MENU1);
	SetMenu(&TheMENUX);

	SetDlgItemTextA(IDC_EDIT1, "128");
	SetDlgItemTextA(IDC_EDIT3, "chrome.exe");
	SetDlgItemTextA(IDC_EDIT2, "255");
	SetDlgItemTextA(IDC_EDIT4, "255");
	SetDlgItemTextA(IDC_EDIT5, "255");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEveryThingAlphaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEveryThingAlphaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEveryThingAlphaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEveryThingAlphaDlg::OnOptionsExit()
{
	// TODO: 在此添加命令处理程序代码
	CEveryThingAlphaDlg::OnOK();
}


void CEveryThingAlphaDlg::OnOptionsSettings()
{
	// TODO: 在此添加命令处理程序代码
	LogFile("User clicked settings...");
	shared_ptr<CEveryThingAlphaDlg> NxDlg(new CEveryThingAlphaDlg);
	thread(&CEveryThingAlphaDlg::MSGBOX, NxDlg, "The Coming...").detach();
	return;
}


void CEveryThingAlphaDlg::OnAboutEverythingalp()
{
	// TODO: 在此添加命令处理程序代码
	LogFile("User clicked about");
	shared_ptr<CAboutDlg> NxDlg(new CAboutDlg);
	thread(&CAboutDlg::DoModal, NxDlg).detach();
	return;
}


void CEveryThingAlphaDlg::OnAboutSaurik()
{
	// TODO: 在此添加命令处理程序代码
	LogFile("User clicked my website");
	shared_ptr<FILE> NxBuffer (_popen("start https://www.myocean.net/", "r"));
	return;
}


void CEveryThingAlphaDlg::OnAbout32775()
{
	// TODO: 在此添加命令处理程序代码
	LogFile("User clicked my zhihu page.");
	//shared_ptr<FILE> NxBuffer(_popen("start https://www.zhihu.com/people/yu-xin-bo-10/", "r"));
	MessageBox("没有找到任何东西", "Operation blocked.", 0U);
	return;
}


typedef unsigned char byte;

byte get_Num(CEveryThingAlphaDlg* icim)
{
	char neotext[MAX_PATH];
	icim->GetDlgItemTextA(IDC_EDIT1, neotext, MAX_PATH);
	string bufitem(neotext);
	stringstream ritem;
	ritem << bufitem;
	unsigned naz;
	ritem >> naz;
	if (naz > (unsigned char)255)return move((unsigned char)255);
	if (naz < (unsigned char)0)return move((unsigned char)255);
	return move(naz);
}

byte get_Num(CEveryThingAlphaDlg* icim,int BSF)
{
	char neotext[MAX_PATH];
	icim->GetDlgItemTextA(BSF, neotext, MAX_PATH);
	string bufitem(neotext);
	stringstream ritem;
	ritem << bufitem;
	unsigned naz;
	ritem >> naz;
	if (naz > (unsigned char)255)return move((unsigned char)255);
	if (naz < (unsigned char)0)return move((unsigned char)255);
	return move(naz);
}


void CEveryThingAlphaDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	LogFile("User try to modify a program...");
	string NativeHall;
	HANDLE p_HANELD = NULL;
	CString S_Buffer;
	char X_Path[MAX_PATH];
	GetDlgItemTextA(IDC_EDIT3, X_Path, MAX_PATH);
	string bufitem(X_Path);
	p_HANELD = GetProcessByName(bufitem);
	if (!p_HANELD)
	{
		LogFile("Can not find HANDLE...");
		shared_ptr<CEveryThingAlphaDlg> NxDlg(new CEveryThingAlphaDlg);
		thread(&CEveryThingAlphaDlg::MSGBOX, NxDlg, "Process not found.\nCheck your input and try again.").detach();
		return;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		Handle_Alpha(move(get_Num(this)), p_HANELD,move(On_RGB(get_Num(this, IDC_EDIT2), get_Num(this, IDC_EDIT4), get_Num(this, IDC_EDIT5))));
	}
	else
		Handle_Alpha(move(get_Num(this)), p_HANELD);
	return;
}


void CEveryThingAlphaDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	LogFile("User try to restore a program's status.");
	HANDLE p_HANELD = NULL;
	char X_Path[MAX_PATH];
	GetDlgItemTextA(IDC_EDIT3, X_Path, MAX_PATH);
	string bufitem(X_Path);
	p_HANELD = GetProcessByName(bufitem);
	if (!p_HANELD)
	{
		shared_ptr<CEveryThingAlphaDlg> NxDlg(new CEveryThingAlphaDlg);
		thread(&CEveryThingAlphaDlg::MSGBOX, NxDlg, "Process not found.\nCheck your input and try again.").detach();
		return;
	}
	Handle_Alpha(move((unsigned char)255), p_HANELD);
	return;
}


void CEveryThingAlphaDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBoxA("Some program may crash after this operation!\nTHIS IS A DANGEROUS OPERATION!\nProgram will force load config data and some Anti-Virus Software may block this handle."
		, "WARNING! Saurik King@ithot.top", MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}
	LogFile("Getting path of this program...");
	char pBuf[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pBuf);
	string sBuf(pBuf);
	HANDLE p_HANELD = NULL;
	char X_Path[MAX_PATH];
	GetDlgItemTextA(IDC_EDIT3, X_Path, MAX_PATH);
	string bufitem(X_Path);
	p_HANELD = GetProcessByName(bufitem);
	if (!p_HANELD)
	{
		LogFile("HANDLE Not found.");
		shared_ptr<CEveryThingAlphaDlg> NxDlg(new CEveryThingAlphaDlg);
		thread(&CEveryThingAlphaDlg::MSGBOX, NxDlg, "Process not found.\nCheck your input and try again.").detach();
		return;
	}
	if (IsWow64ProcessEx(p_HANELD))
	{
		LogFile("X64 Injection");
		sBuf += "\\ForceAlphaX.dll";
	}
	else
	{
		// x86处理器。
		LogFile("X86 Injection");
		sBuf += "\\x86\\ForceAlphaX.dll";
	}
	if (!Auto_Inject(bufitem.c_str(), sBuf.c_str()))
	{
		LogFile("Failed of injection");
		shared_ptr<CEveryThingAlphaDlg> NxDlg(new CEveryThingAlphaDlg);
		thread(&CEveryThingAlphaDlg::MSGBOX, NxDlg, "Failed to process this operation.\nPlease check your input.").detach();
		return;
	}
	return;
}


void CEveryThingAlphaDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	LogFile("All program modifing");
	On_Pcs_All(move(get_Num(this)));
	LogFile("All program modified.");
	return;
}


void CEveryThingAlphaDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	LogFile("All program recovering");
	On_Res_All();
	LogFile("All program recoveried;");
	return;
}


void CEveryThingAlphaDlg::OnOptionsTopmost()
{
	// TODO: 在此添加命令处理程序代码
	LogFile("Top most operation.");
	if (is_win_toped)
	{
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		is_win_toped = FALSE;
	}
	else
	{
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		is_win_toped = TRUE;
	}
}


void CEveryThingAlphaDlg::OnClickandtransparentClicksomewhereandtransparentit()
{
	// TODO: 在此添加命令处理程序代码
	SetCapture();
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	is_win_toped = TRUE;
	LogFile("User try to clicked and modify a program.");
	
}

CEveryThingAlphaDlg::~CEveryThingAlphaDlg()
{
	LogFile("Program Exiting...Destructor Functios CallBack Ready...");
	CDialog::~CDialog();
	return;
}

LRESULT CEveryThingAlphaDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	//POINT point;
	//CRect rect;
	switch (message)
	{
	case WM_LBUTTONDOWN:
		;
	case WM_LBUTTONDBLCLK:
		;
	case WM_RBUTTONDOWN:
		;
	case WM_RBUTTONDBLCLK:
		;
	case WM_MBUTTONDOWN:
		;
	case WM_MBUTTONDBLCLK:
	{
		POINT pNow = { 0,0 };
		if (GetCursorPos(&pNow))  // 获取鼠标当前位置
		{
			HWND hwndPointNow = NULL;
			hwndPointNow = ::WindowFromPoint(pNow);  // 获取鼠标所在窗口的句柄
			if (hwndPointNow)
			{
				if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
					Window_Alpha(move(get_Num(this)), hwndPointNow, move(On_RGB(get_Num(this, IDC_EDIT2), get_Num(this, IDC_EDIT4), get_Num(this, IDC_EDIT5))));
				else
					Window_Alpha(move(get_Num(this)), hwndPointNow);
			}
			else
				return CDialog::WindowProc(message, wParam, lParam);
		}
		else
			return CDialog::WindowProc(message, wParam, lParam);
		ReleaseCapture();
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		is_win_toped = FALSE;
		LogFile("User clicked a program and modified.");
	}
	}
	return CDialog::WindowProc(message, wParam, lParam);
}
