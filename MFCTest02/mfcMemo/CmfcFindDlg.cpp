#include "pch.h"
#include "framework.h"
#include "mfcMemo.h"
#include "mfcMemoDlg.h"
#include "afxdialogex.h"
#include "CmfcFindDlg.h"

BEGIN_MESSAGE_MAP(CmfcFindDlg, CDialogEx)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CmfcFindDlg::CmfcFindDlg() : CDialogEx(IDD_FND_DIALOG) //"mfcMemo.h"에 resource.h이 있음 / IDD_FND_DIALOG(resource.h)필요
{

}

void CmfcFindDlg::DoDataExchange(CDataExchange* pDX) //관례적으로 생성됨
{
	CDialogEx::DoDataExchange(pDX);
}

void CmfcFindDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) //엔터키 누르면 입력 종료
{
	switch (nChar) 
	{
	case VK_RETURN:
		GetDlgItem(ID_EDIT_FIND)->GetWindowText(mStr); //찾는 것을 입력 후 엔터를 쳤을 때 mstr에 저장
		GetDlgItem(ID_EDIT_REPLACE)->GetWindowText(mStr2);
		break; //switch문 종료

	case VK_ESCAPE:
		mStr = "";
		mStr2 = "";
		break;

	default:
		break;
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CmfcFindDlg::OnInitDialog() //초기화 함수
{
	CDialogEx::OnInitDialog();

	mStr = "";
	mStr2 = "";

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CmfcFindDlg::PreTranslateMessage(MSG* pMsg) //모든 메시지 전달됨 
{
	switch (pMsg->message) {

	case WM_KEYDOWN: //OnKeyDown과 같이 구성
		switch (pMsg->wParam) {
		case VK_RETURN: //엔터키
			GetDlgItem(ID_EDIT_FIND)->GetWindowText(mStr);
			GetDlgItem(ID_EDIT_REPLACE)->GetWindowText(mStr2);
			EndDialog(IDOK); //dialog의 return 값 지정(IDOK)로
			break;

		case VK_ESCAPE:
			mStr = ""; //모든 문자열 지우고
			mStr2 = "";
			EndDialog(IDCANCEL);
			break;

		default:
			break;

		}
		break;

	default: //keydown 말곤 노관심
		break;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
