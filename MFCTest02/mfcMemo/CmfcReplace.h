#pragma once
#include "afxdialogex.h"


// CmfcReplace 대화 상자

class CmfcReplace : public CDialogEx
{
	DECLARE_DYNAMIC(CmfcReplace)

	CString mStrFind, mStrReplace;

public:
	CmfcReplace(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CmfcReplace();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REPLACE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonEnd();
};
