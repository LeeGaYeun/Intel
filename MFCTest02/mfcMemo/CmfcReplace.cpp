// CmfcReplace.cpp: 구현 파일
//

#include "pch.h"
#include "mfcMemo.h"
#include "afxdialogex.h"
#include "CmfcReplace.h"


// CmfcReplace 대화 상자

IMPLEMENT_DYNAMIC(CmfcReplace, CDialogEx)

CmfcReplace::CmfcReplace(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REPLACE_DIALOG, pParent)
{
	mStrFind = "";
	mStrReplace = "";
}

BOOL CmfcReplace::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

CmfcReplace::~CmfcReplace()
{
}

void CmfcReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CmfcReplace, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_END, &CmfcReplace::OnBnClickedButtonEnd)
END_MESSAGE_MAP()


// CmfcReplace 메시지 처리기


BOOL CmfcReplace::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
			EndDialog(IDCANCEL);	//종료 예약이라서 break 필요
			break;
		case VK_RETURN:
			OnBnClickedButtonEnd();
			/*GetDlgItem(IDC_EDIT_FIND1)->GetWindowText(mStrFind);
			GetDlgItem(ID_EDIT_REPLACE)->GetWindowText(mStrReplace);
			EndDialog(IDOK);*/
			break;
		}
	default:
		break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CmfcReplace::OnBnClickedButtonEnd()
{
	GetDlgItem(IDC_EDIT_FIND1)->GetWindowText(mStrFind);
	GetDlgItem(IDC_EDIT_REPLACE1)->GetWindowText(mStrReplace);
	EndDialog(IDOK);
}
