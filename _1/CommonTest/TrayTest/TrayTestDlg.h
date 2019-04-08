
// TrayTestDlg.h : header file
//

#pragma once

#define  WM_SHOWTASK  WM_USER+10

// CTrayTestDlg dialog
class CTrayTestDlg : public CDialogEx
{
// Construction
public:
	CTrayTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRAYTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	void ToTray(void);
	LRESULT onShowTask(WPARAM wParam, LPARAM lParam);
	void GetCurrentUserName();

	NOTIFYICONDATA m_nid;
	int m_num;

};
