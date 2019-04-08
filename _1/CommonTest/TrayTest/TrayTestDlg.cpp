
// TrayTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrayTest.h"
#include "TrayTestDlg.h"
#include "afxdialogex.h"

#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void hello_thread()
{
	while (true)
	{
		//m_num++;
		//ʹ�õ�ǰlocal������numpunctʹ��ȱʡ����˲����������ʱ�������ǧ�ֺŷָ���
		//std::locale::global(std::locale("").combine<std::numpunct<char>>(std::locale::classic()));
		//std::string strNum = boost::lexical_cast<std::string>(m_num);
		//boost::this_thread::sleep(boost::posix_time::milliseconds(100));

		//TRACE(strNum.c_str());
	}
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CTrayTestDlg dialog



CTrayTestDlg::CTrayTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRAYTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_num = 0;
}

void CTrayTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTrayTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SHOWTASK, onShowTask)
END_MESSAGE_MAP()


// CTrayTestDlg message handlers

BOOL CTrayTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//ToTray();
	//GetCurrentUserName();
	boost::thread thrd(&hello_thread);
	thrd.join();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTrayTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrayTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrayTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTrayTestDlg::ToTray(void)
{
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;
	//�Զ������Ϣ���� WM_SHOWTASK ͷ�����ж���ΪWM_USER+10
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	StrCpyW(m_nid.szTip, L"����ͼ��");//������������ʱ������ʾ������ 
	Shell_NotifyIcon(NIM_ADD, &m_nid);//�����������ͼ�� 
}


LRESULT CTrayTestDlg::onShowTask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP://�Ҽ�����ʱ������ݲ˵�������ֻ��һ�����رա� 
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//�õ����λ�� 
		CMenu menu;
		menu.CreatePopupMenu();//����һ������ʽ�˵� 
							   //���Ӳ˵���رա������������ϢWM_DESTROY�������ڣ��� 
							   //���أ�������������� 
		menu.AppendMenu(MF_STRING, WM_DESTROY, L"�˳�");
		//ȷ������ʽ�˵���λ�� 
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		//��Դ���� 
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	}
	break;
	case WM_LBUTTONDBLCLK://˫������Ĵ��� 
	{
		this->ShowWindow(SW_SHOWNORMAL);//�򵥵���ʾ������
	}
	break;
	}
	return 0;
}

void CTrayTestDlg::GetCurrentUserName()
{
	BOOL bAdminPrivilege = FALSE;
	TCHAR strUserName[80 + 1];
	DWORD nUserNameLength = 80;
	GetUserName(strUserName, &nUserNameLength);
	AfxMessageBox(strUserName);
}

