#include "pch.h"
#include "CmfcFindDlg.h"


BOOL CmfcFindDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
BEGIN_MESSAGE_MAP(CmfcFindDlg, CDialogEx)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


void CmfcFindDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) //엔터키 누르면 입력 종료
{
	switch (nChar) {
	case VK_RETURN:
		GetDlgItem(ID_EDIT_FIND)->GetWindowText(mStr); //엔터를 쳤을 때 mstr에 저장
		break;
	
	case VK_ESCAPE:
		mStr = "";
		break;
	
	default:
		break;
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
