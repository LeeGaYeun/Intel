#include "pch.h"
#include "CmfcFindDlg.h"


BOOL CmfcFindDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
BEGIN_MESSAGE_MAP(CmfcFindDlg, CDialogEx)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


void CmfcFindDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) //����Ű ������ �Է� ����
{
	switch (nChar) {
	case VK_RETURN:
		GetDlgItem(ID_EDIT_FIND)->GetWindowText(mStr); //���͸� ���� �� mstr�� ����
		break;
	
	case VK_ESCAPE:
		mStr = "";
		break;
	
	default:
		break;
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
