
// mfcMemoDlg.h: 헤더 파일
//

#pragma once


// CmfcMemoDlg 대화 상자
class CmfcMemoDlg : public CDialogEx	//class안에 class변수 선언
{
	CString sFind, sReplace;
	int pos = 0;
	int mEncoding = 0;	// 0일 때 ANSI 1일 때 UTF-8
// 생성입니다.
public:
	CmfcMemoDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;
	HACCEL mAccel;
	CEdit mEditMemo;
	CStatusBarCtrl mStatusBar;
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuAbout2();
	afx_msg void OnMenuFnd();
	void AddText(CString s);
	afx_msg void OnMenuNextfind();

	static CString findString;
	static int findPosition;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMenuUtf8();
	afx_msg void OnMenuAnsi();
	afx_msg void OnMenuReplace();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
