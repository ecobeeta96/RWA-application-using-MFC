
// FINALDlg.h : header file
//

#pragma once


// CFINALDlg dialog
class CFINALDlg : public CDialogEx
{
// Construction
public:
	CFINALDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FINAL_DIALOG };
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
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedbtnrunalgo();
	afx_msg void OnBnClickedbtnrunagain();
	afx_msg void OnBnClickedbtnexit();
};
