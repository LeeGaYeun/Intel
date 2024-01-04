#pragma once
#include <afxdialogex.h>
class CmfcFindDlg : public CDialogEx
{
public:
    CString mStr = "";
    CString mStr2 = "";

    CmfcFindDlg();

#ifdef  AFX_DESIGN_TIME
    enum{ IDD = IDD_FND_DIALOG };
#endif //  AFX_DESIGN_TIME

    virtual void DoDataExchange(CDataExchange* pDX);

    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnBnClickedButton1();
    afx_msg void OnClickedButtonChange();
};
